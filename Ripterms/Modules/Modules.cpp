#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>

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

void Ripterms::Modules::IModule::onEvent(Event* event)
{
}

void Ripterms::Modules::IModule::onPacketSend(JNIEnv* env, Packet& packet, bool* cancel)
{
}

static void sendPacket_callback(void* sp, void* j_rarg0, void* j_rarg1, void* j_rarg2, void* j_rarg3, void* j_rarg4, void* j_rarg5, bool* should_return) //j_rarg0 is this object in non static methods
{
	JNIEnv* env = Ripterms::get_current_thread_env();
	if (!env)
		return;
	jobject packet_o = Ripterms::JavaHook::j_rarg_to_jobject(j_rarg1);
	if (!packet_o)
		return;
	Packet packet(packet_o, env);
	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onPacketSend(env, packet, should_return);
		}
	}
	return;
}

void Ripterms::Modules::setupEventHooks()
{
	Ripterms::JavaClassV2 NetworkManager("net/minecraft/network/NetworkManager");
	jmethodID sendPacket = NetworkManager.getMethodID("sendPacket");
	Ripterms::JavaHook::add_to_java_hook(sendPacket, sendPacket_callback);
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
			if (should_disable)m->disable();
			delete m;
		}
	}
}


void Ripterms::Modules::ESP::render()
{
}
