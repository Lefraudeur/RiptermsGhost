#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>
#include "../../net/minecraft/network/play/client/C03PacketPlayer/C03PacketPlayer.h"

void Ripterms::Modules::IModule::run()
{
}

void Ripterms::Modules::IModule::renderGUI()
{
}

void Ripterms::Modules::IModule::render()
{
}

void Ripterms::Modules::IModule::disable()
{
	enabled = false;
}

void Ripterms::Modules::IModule::onAddToSendQueue(JNIEnv* env, NetHandlerPlayClient& sendQueue, Packet& packet, bool* cancel)
{
}

void Ripterms::Modules::IModule::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
}

void Ripterms::Modules::IModule::onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel)
{
}

void Ripterms::Modules::IModule::onGetMouseOver(JNIEnv* env, float* partialTicks, bool* cancel)
{
}

void Ripterms::Modules::IModule::onShouldSideBeRendered(JNIEnv* env, Block& block, bool* cancel)
{
}

void Ripterms::Modules::IModule::onGetClientModName(JNIEnv* env, bool* cancel)
{
}

static void addToSendQueue_callback(void* sp, bool* should_return, void* rbx, void* thread)
{
	if (!Ripterms::p_env) return;
	if (Ripterms::Modules::IModule::onAddToSendQueueNoEvent) return;
	JNIEnv* env = Ripterms::get_current_thread_env();

	//env->PushLocalFrame(5); this is supposed to deletelocal refs but it somehow crashes
	NetHandlerPlayClient sendQueue(Ripterms::JavaHook::get_jobject_arg_at(sp, 1, thread), env);
	Packet packet(Ripterms::JavaHook::get_jobject_arg_at(sp, 0, thread), env);

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onAddToSendQueue(env, sendQueue, packet, should_return);
		}
	}
	//env->PopLocalFrame(nullptr);
	return;
}

static void getMouseOver_callback(void* sp, bool* should_return, void* rbx, void* thread)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = Ripterms::get_current_thread_env();
	float* f = (float*)((uint64_t*)sp + 1);
	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onGetMouseOver(env, f, should_return);
		}
	}
	return;
}

static void attackTargetEntityWithCurrentItem_callback(void* sp, bool* should_return, void* rbx, void* thread)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = Ripterms::get_current_thread_env();

	//env->PushLocalFrame(5);
	Entity entity(Ripterms::JavaHook::get_jobject_arg_at(sp, 0, thread), env);
	EntityPlayer this_player(Ripterms::JavaHook::get_jobject_arg_at(sp, 1, thread), env);
	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onAttackTargetEntityWithCurrentItem(env, this_player, entity, should_return);
		}
	}
	//env->PopLocalFrame(nullptr);
	return;
}

static void onUpdateWalkingPlayer_callback(void* sp, bool* should_return, void* rbx, void* thread)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = Ripterms::get_current_thread_env();

	//env->PushLocalFrame(20);
	EntityPlayerSP this_player(Ripterms::JavaHook::get_jobject_arg_at(sp, 0, thread), env);
	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onUpdateWalkingPlayer(env, this_player, should_return);
		}
	}
	//env->PopLocalFrame(nullptr);
	return;
}

static void shouldSideBeRendered_callback(void* sp, bool* should_return, void* rbx, void* thread)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = Ripterms::get_current_thread_env();

	Block block(env);
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5)
		block = IBlockState(Ripterms::JavaHook::get_jobject_arg_at(sp, 3, thread), env).getBlock();
	else
	{
		int index = (Ripterms::version.type == Ripterms::Version::MAJOR_1_7_10 ? 5 : 3);
		block.setInstance(Ripterms::JavaHook::get_jobject_arg_at(sp, index, thread));
	}
	if (!block.isValid()) return;
	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onShouldSideBeRendered(env, block, should_return);
		}
	}
	return;
}

static void getClientModName_callback(void* sp, bool* should_return, void* rbx, void* thread)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = Ripterms::get_current_thread_env();

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onGetClientModName(env, should_return);
		}
	}
	return;
}

void Ripterms::Modules::setupEventHooks()
{
	Ripterms::JavaClassV2 NetHandlerPlayClient("net/minecraft/client/network/NetHandlerPlayClient");
	jmethodID addToSendQueue = NetHandlerPlayClient.getMethodID("addToSendQueue");
	Ripterms::JavaHook::add_to_java_hook(addToSendQueue, addToSendQueue_callback);

	Ripterms::JavaClassV2 EntityRenderer("net/minecraft/client/renderer/EntityRenderer");
	jmethodID getMouseOver = EntityRenderer.getMethodID("getMouseOver");
	Ripterms::JavaHook::add_to_java_hook(getMouseOver, getMouseOver_callback);

	Ripterms::JavaClassV2 EntityPlayer("net/minecraft/entity/player/EntityPlayer");
	jmethodID attackTargetEntityWithCurrentItem = EntityPlayer.getMethodID("attackTargetEntityWithCurrentItem");
	Ripterms::JavaHook::add_to_java_hook(attackTargetEntityWithCurrentItem, attackTargetEntityWithCurrentItem_callback);

	Ripterms::JavaClassV2 EntityPlayerSP
	(
		(Ripterms::version.type == Ripterms::Version::MAJOR_1_7_10 ? "net/minecraft/client/entity/EntityClientPlayerMP" 
			: "net/minecraft/client/entity/EntityPlayerSP")
	);
	jmethodID onUpdateWalkingPlayer = EntityPlayerSP.getMethodID("onUpdateWalkingPlayer");
	Ripterms::JavaHook::add_to_java_hook(onUpdateWalkingPlayer, onUpdateWalkingPlayer_callback);

	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_7_10
		|| Ripterms::version.type == Ripterms::Version::MAJOR_1_8_9)
	{
		Ripterms::JavaClassV2 Block("net/minecraft/block/Block");
		jmethodID shouldSideBeRendered = Block.getMethodID("shouldSideBeRendered");
		Ripterms::JavaHook::add_to_java_hook(shouldSideBeRendered, shouldSideBeRendered_callback);
	}

	Ripterms::JavaClassV2 ClientBrandRetriever("net/minecraft/client/ClientBrandRetriever");
	jmethodID getClientModName = ClientBrandRetriever.getMethodID("getClientModName");
	Ripterms::JavaHook::add_to_java_hook(getClientModName, getClientModName_callback);
}

void Ripterms::Modules::runAll()
{
	for (const std::pair<std::string, std::vector<IModule*>>& category : categories)
	{
		for (IModule* m : category.second)
		{
			m->run();
		}
	}
}

void Ripterms::Modules::cleanAll()
{
	bool should_disable = Ripterms::p_env != nullptr;
	for (const std::pair<std::string, std::vector<IModule*>>& category : categories)
	{
		for (IModule* m : category.second)
		{
			if (should_disable) m->disable();
			delete m;
		}
	}
}


void Ripterms::Modules::ESP::render()
{
}
