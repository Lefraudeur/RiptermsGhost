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

void Ripterms::Modules::IModule::onSendPacket(JNIEnv* env, Packet& packet, bool* cancel)
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

static void sendPacket_callback(void* sp, void* j_rarg0, void* j_rarg1, void* j_rarg2, void* j_rarg3, void* j_rarg4, void* j_rarg5, bool* should_return, void* rbx, void* thread, void* r13)
{
	if (Ripterms::Modules::IModule::onSendPacketNoEvent)
		return;
	JNIEnv* env = Ripterms::get_current_thread_env();
	if (!env) return;
	env->PushLocalFrame(50);
	jobject packet_o = Ripterms::JavaHook::get_jobject_arg_at(sp, 0, thread);
	Packet packet(packet_o, env);
	if (!packet.isValid()) return;
	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onSendPacket(env, packet, should_return);
		}
	}
	env->PopLocalFrame(nullptr);
	return;
}

static void getMouseOver_callback(void* sp, void* j_rarg0, void* j_rarg1, void* j_rarg2, void* j_rarg3, void* j_rarg4, void* j_rarg5, bool* should_return, void* rbx, void* thread, void* r13)
{
	JNIEnv* env = Ripterms::get_current_thread_env();
	if (!env) return;
	env->PushLocalFrame(50);
	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onGetMouseOver(env, (float*)((uint64_t*)sp + 1), should_return);
		}
	}
	env->PopLocalFrame(nullptr);
	return;
}

static void attackTargetEntityWithCurrentItem_callback(void* sp, void* j_rarg0, void* j_rarg1, void* j_rarg2, void* j_rarg3, void* j_rarg4, void* j_rarg5, bool* should_return, void* rbx, void* thread, void* r13)
{
	JNIEnv* env = Ripterms::get_current_thread_env();
	if (!env) return;
	env->PushLocalFrame(50);
	jobject entity_o = Ripterms::JavaHook::get_jobject_arg_at(sp, 0, thread);
	Entity entity(entity_o, env);
	if (!entity.isValid()) return;
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

static void onUpdateWalkingPlayer_callback(void* sp, void* j_rarg0, void* j_rarg1, void* j_rarg2, void* j_rarg3, void* j_rarg4, void* j_rarg5, bool* should_return, void* rbx, void* thread, void* r13)
{
	JNIEnv* env = Ripterms::get_current_thread_env();
	if (!env) return;
	env->PushLocalFrame(50);
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

void Ripterms::Modules::setupEventHooks()
{
	Ripterms::JavaClassV2 NetworkManager("net/minecraft/network/NetworkManager");
	jmethodID sendPacket = NetworkManager.getMethodID("sendPacket");
	Ripterms::JavaHook::add_to_java_hook(sendPacket, sendPacket_callback);

	Ripterms::JavaClassV2 EntityRenderer("net/minecraft/client/renderer/EntityRenderer");
	jmethodID getMouseOver = EntityRenderer.getMethodID("getMouseOver");
	Ripterms::JavaHook::add_to_java_hook(getMouseOver, getMouseOver_callback);

	Ripterms::JavaClassV2 EntityPlayer("net/minecraft/entity/player/EntityPlayer");
	jmethodID attackTargetEntityWithCurrentItem = EntityPlayer.getMethodID("attackTargetEntityWithCurrentItem");
	Ripterms::JavaHook::add_to_java_hook(attackTargetEntityWithCurrentItem, attackTargetEntityWithCurrentItem_callback);

	Ripterms::JavaClassV2 EntityPlayerSP("net/minecraft/client/entity/EntityPlayerSP");
	jmethodID onUpdateWalkingPlayer = EntityPlayerSP.getMethodID("onUpdateWalkingPlayer");
	Ripterms::JavaHook::add_to_java_hook(onUpdateWalkingPlayer, onUpdateWalkingPlayer_callback);
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
