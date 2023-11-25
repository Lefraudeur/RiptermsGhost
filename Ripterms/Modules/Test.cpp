#include "Modules.h"
#include <ImGui/imgui.h>
#include <iostream>
#include "../../net/minecraft/network/Packet/Packet.h"
#include "../../net/minecraft/network/play/client/C03PacketPlayer/C03PacketPlayer.h"


static void callback(void* sp, void* j_rarg0, void* j_rarg1, void* j_rarg2, void* j_rarg3, void* j_rarg4, void* j_rarg5, bool* should_return) //j_rarg0 is this object in non static methods
{
	static unsigned long long i = 0U;
	std::cout << i << '\n';
	i++;
	if (i == 999999999U)
		i = 0U;
	//*should_return = true;
	//set should_return to true to cancel the call
	/*
	static JNIEnv* env = nullptr;
	if (!env)
		Ripterms::p_jvm->GetEnv((void**)&env, JNI_VERSION_1_8);
	Packet packet(Ripterms::JavaHook::j_rarg_to_jobject(j_rarg1), env);
	if (packet.instanceOf(Ripterms::JavaClassV2("net/minecraft/network/play/client/C03PacketPlayer").getJClass(env)))
	{
		C03PacketPlayer playerPacket(packet, env);
		if (playerPacket.getRotating() == true)
		{
			playerPacket.setYawPitch({ 0.0f, 0.0f });
		}
	}
	*/
	return;
}

void Ripterms::Modules::Test::renderGUI()
{
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	if (ImGui::Button("Run Test"))
	{
		Ripterms::JavaClassV2::JClass lol(Ripterms::JavaClassV2::findClass("io/github/lefraudeur/ClassPatcher"));
		if (lol.isValid())
		{
			std::cout << "found" << std::endl;
		}
		else 
		{
			std::cout << "not found" << std::endl;
		}
		//Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/client/entity/EntityPlayerSP"));
		//jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "swingItem", "()V");

		//Ripterms::JavaClassV2 minecraftClass("net/minecraft/client/Minecraft");
		//jmethodID caller = minecraftClass.getMethodID("clickMouse");

		//Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/client/entity/EntityPlayerSP"));
		//jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "func_71038_i", "()V");

		Ripterms::JavaClassV2 lol2("net/minecraft/network/NetworkManager");
		jmethodID mid = lol2.getMethodID("sendPacket");
		//Ripterms::JavaHook::add_to_java_hook(caller, nullptr);
		Ripterms::JavaHook::add_to_java_hook(mid, callback);
	}
}