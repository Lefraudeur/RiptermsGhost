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
}

void Ripterms::Modules::IModule::onAddToSendQueue(JNIEnv* env, NetHandlerPlayClient& sendQueue, Packet& packet, bool* cancel)
{
}

void Ripterms::Modules::IModule::onUpdateWalkingPlayer(JNIEnv* env, bool* cancel)
{
}

void Ripterms::Modules::IModule::onAttackTargetEntityWithCurrentItem(JNIEnv* env, Entity& entity, bool* cancel)
{
}

void Ripterms::Modules::IModule::onGetMouseOver(JNIEnv* env, float* partialTicks, bool* cancel)
{
}

void Ripterms::Modules::IModule::onShouldSideBeRendered(Object& blockAccess, BlockPos& blockPos, Object& enumFacing)
{
}

void Ripterms::Modules::IModule::onSetEntityBoundingBox(JNIEnv* env, Entity& this_entity, AxisAlignedBB& boundingBox, bool* cancel)
{
}

static void addToSendQueue_callback(void* sp, bool* should_return, void* rbx, void* thread)
{
	if (Ripterms::Modules::IModule::onAddToSendQueueNoEvent) return;
	JNIEnv* env = Ripterms::JavaHook::get_env_for_thread(thread);

	env->PushLocalFrame(20);

	NetHandlerPlayClient sendQueue(Ripterms::JavaHook::get_jobject_arg_at(sp, 1, thread), env);
	Packet packet(Ripterms::JavaHook::get_jobject_arg_at(sp, 0, thread), env);

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onAddToSendQueue(env, sendQueue, packet, should_return);
		}
	}
	env->PopLocalFrame(nullptr);
	return;
}

static void getMouseOver_callback(void* sp, bool* should_return, void* rbx, void* thread)
{
	JNIEnv* env = Ripterms::JavaHook::get_env_for_thread(thread);	
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
	JNIEnv* env = Ripterms::JavaHook::get_env_for_thread(thread);
	env->PushLocalFrame(20);
	Entity entity(Ripterms::JavaHook::get_jobject_arg_at(sp, 0, thread), env);
	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onAttackTargetEntityWithCurrentItem(env, entity, should_return);
		}
	}
	env->PopLocalFrame(nullptr);
	return;
}

static void onUpdateWalkingPlayer_callback(void* sp, bool* should_return, void* rbx, void* thread)
{
	JNIEnv* env = Ripterms::JavaHook::get_env_for_thread(thread);
	env->PushLocalFrame(20);
	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onUpdateWalkingPlayer(env, should_return);
		}
	}
	env->PopLocalFrame(nullptr);
	return;
}

static void setEntityBoundingBox_callback(void* sp, bool* should_return, void* rbx, void* thread)
{
	JNIEnv* env = Ripterms::JavaHook::get_env_for_thread(thread);
	env->PushLocalFrame(20);

	AxisAlignedBB boundingBox(Ripterms::JavaHook::get_jobject_arg_at(sp, 0, thread), env);
	Entity this_entity(Ripterms::JavaHook::get_jobject_arg_at(sp, 1, thread), env);
	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onSetEntityBoundingBox(env, this_entity, boundingBox, should_return);
		}
	}
	env->PopLocalFrame(nullptr);
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

	Ripterms::JavaClassV2 EntityPlayerSP("net/minecraft/client/entity/EntityPlayerSP");
	jmethodID onUpdateWalkingPlayer = EntityPlayerSP.getMethodID("onUpdateWalkingPlayer");
	Ripterms::JavaHook::add_to_java_hook(onUpdateWalkingPlayer, onUpdateWalkingPlayer_callback);

	Ripterms::JavaClassV2 Entity("net/minecraft/entity/Entity");
	jmethodID setEntityBoundingBox = Entity.getMethodID("setEntityBoundingBox");
	Ripterms::JavaHook::add_to_java_hook(setEntityBoundingBox, setEntityBoundingBox_callback);
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
