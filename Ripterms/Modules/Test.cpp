#include "Modules.h"
#include <ImGui/imgui.h>
#include <iostream>
#include "../../net/minecraft/network/Packet/Packet.h"
#include "../../net/minecraft/network/play/client/C03PacketPlayer/C03PacketPlayer.h"


static void callback(void* sp, void* j_rarg0, void* j_rarg1, void* j_rarg2, void* j_rarg3, void* j_rarg4, void* j_rarg5, bool* should_return, void* rbx, void* reserved) //j_rarg0 is this object in non static methods
{
	static unsigned long long i = 0U;
	std::cout << "from _code->verified_entry_point: " << i << '\n';
	i++;
	if (i == 999999999U)
		i = 0U;
	std::cout << rbx << '\n';
	*should_return = true;
	return;
}

static uint8_t* method = nullptr;

static void callback2(void* sp, void* j_rarg0, void* j_rarg1, void* j_rarg2, void* j_rarg3, void* j_rarg4, void* j_rarg5, bool* should_return, void* rbx, void* reserved) //j_rarg0 is this object in non static methods
{
	static unsigned long long i = 0U;
	if (rbx != method)
		return;
	std::cout << "from _i2i_entry: " << i << '\n';
	i++;
	if (i == 999999999U)
		i = 0U;
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
		Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/entity/EntityLivingBase"));
		jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "swingItem", "()V");

		//Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/entity/EntityLivingBase"));
		//jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "func_71038_i", "()V");

		//Ripterms::JavaClassV2 lol2("net/minecraft/network/NetworkManager");
		//jmethodID mid = lol2.getMethodID("sendPacket");

		method = *((uint8_t**)mid);
		//new Hook(0, *((void**)(method + 0x38)), callback2, nullptr, Ripterms::Hook::JAVA_ENTRY_HOOK);
		Ripterms::JavaHook::add_to_java_hook(mid, callback);
	}
}