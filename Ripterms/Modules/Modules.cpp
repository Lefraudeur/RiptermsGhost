#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>
#include "../../net/minecraft/network/play/client/C03PacketPlayer/C03PacketPlayer.h"
#include "../Hook/JavaHook.h"

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

void Ripterms::Modules::IModule::onGetMouseOver(JNIEnv* env, float partialTicks, bool* cancel)
{
}

void Ripterms::Modules::IModule::onShouldSideBeRendered(JNIEnv* env, Block& block, bool* cancel)
{
}

void Ripterms::Modules::IModule::onGetClientModName(JNIEnv* env, bool* cancel)
{
}

static void addToSendQueue_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	if (Ripterms::Modules::IModule::onAddToSendQueueNoEvent) return;
	JNIEnv* env = thread->get_env();

	NetHandlerPlayClient sendQueue(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env);
	Packet packet(Ripterms::JavaHook::get_jobject_param_at(frame, 1), env);

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onAddToSendQueue(env, sendQueue, packet, cancel);
		}
	}

	return;
}

static void getMouseOver_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();

	float f = Ripterms::JavaHook::get_primitive_param_at<float>(frame, 1);
	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onGetMouseOver(env, f, cancel);
		}
	}
	return;
}

static void attackTargetEntityWithCurrentItem_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();

	EntityPlayer this_player(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env);
	Entity entity(Ripterms::JavaHook::get_jobject_param_at(frame, 1), env);

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onAttackTargetEntityWithCurrentItem(env, this_player, entity, cancel);
		}
	}

	return;
}

static void onUpdateWalkingPlayer_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();

	EntityPlayerSP this_player(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env);

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onUpdateWalkingPlayer(env, this_player, cancel);
		}
	}

	return;
}

static void shouldSideBeRendered_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();
	Block block(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env);

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onShouldSideBeRendered(env, block, cancel);
		}
	}

	return;
}

static void getClientModName_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onGetClientModName(env, cancel);
		}
	}
	return;
}

void Ripterms::Modules::setupEventHooks()
{
	Ripterms::JavaClassV2 NetHandlerPlayClient("net/minecraft/client/network/NetHandlerPlayClient");
	jmethodID addToSendQueue = NetHandlerPlayClient.getMethodID("addToSendQueue");
	Ripterms::JavaHook::hook(addToSendQueue, addToSendQueue_callback);

	Ripterms::JavaClassV2 EntityRenderer("net/minecraft/client/renderer/EntityRenderer");
	jmethodID getMouseOver = EntityRenderer.getMethodID("getMouseOver");
	Ripterms::JavaHook::hook(getMouseOver, getMouseOver_callback);

	Ripterms::JavaClassV2 EntityPlayer("net/minecraft/entity/player/EntityPlayer");
	jmethodID attackTargetEntityWithCurrentItem = EntityPlayer.getMethodID("attackTargetEntityWithCurrentItem");
	Ripterms::JavaHook::hook(attackTargetEntityWithCurrentItem, attackTargetEntityWithCurrentItem_callback);

	Ripterms::JavaClassV2 EntityPlayerSP
	(
		(Ripterms::version.type == Ripterms::Version::MAJOR_1_7_10 ? "net/minecraft/client/entity/EntityClientPlayerMP" 
			: "net/minecraft/client/entity/EntityPlayerSP")
	);
	jmethodID onUpdateWalkingPlayer = EntityPlayerSP.getMethodID("onUpdateWalkingPlayer");
	Ripterms::JavaHook::hook(onUpdateWalkingPlayer, onUpdateWalkingPlayer_callback);

	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_7_10 ||
		Ripterms::version.type == Ripterms::Version::MAJOR_1_8_9)
	{
		Ripterms::JavaClassV2 Block("net/minecraft/block/Block");
		jmethodID shouldSideBeRendered = Block.getMethodID("shouldSideBeRendered");
		Ripterms::JavaHook::hook(shouldSideBeRendered, shouldSideBeRendered_callback);
	}

	Ripterms::JavaClassV2 ClientBrandRetriever("net/minecraft/client/ClientBrandRetriever");
	jmethodID getClientModName = ClientBrandRetriever.getMethodID("getClientModName");
	Ripterms::JavaHook::hook(getClientModName, getClientModName_callback);
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
