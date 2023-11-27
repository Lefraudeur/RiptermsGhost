#include "Modules.h"
#include <ImGui/imgui.h>
#include <iostream>
#include "../../net/minecraft/network/Packet/Packet.h"
#include "../../net/minecraft/network/play/client/C03PacketPlayer/C03PacketPlayer.h"


static void callback(void* sp, void* j_rarg0, void* j_rarg1, void* j_rarg2, void* j_rarg3, void* j_rarg4, void* j_rarg5, bool* should_return, void* rbx, void* reserved, void* r13) //j_rarg0 is this object in non static methods
{
	static unsigned long long i = 0U;
	std::cout << "_i2i_entry: " << i << '\n';
	i++;
	if (i == 999999999U)
		i = 0U;
	std::cout << "this:" << *(void**)((uint64_t*)sp + 4) << '\n';
	std::cout << "x:" << *(int*)((uint64_t*)sp + 3) << '\n';
	std::cout << "y:" << *(int*)((uint64_t*)sp + 2) << '\n';
	std::cout << "button:" << *(int*)((uint64_t*)sp +1) << '\n';
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
		Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/client/gui/GuiScreen"));
		jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "mouseClicked", "(III)V");

		//Ripterms::JavaClassV2 lol2("net/minecraft/network/NetworkManager");
		//jmethodID mid = lol2.getMethodID("sendPacket");


		Ripterms::JavaHook::add_to_java_hook(mid, callback);
	}
}