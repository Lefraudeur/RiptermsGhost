#include "Modules.h"
#include <ImGui/imgui.h>
#include <iostream>
#include "../../net/minecraft/network/Packet/Packet.h"
#include "../../net/minecraft/network/play/client/C03PacketPlayer/C03PacketPlayer.h"


static void callback(void* sp, void* j_rarg0, void* j_rarg1, void* j_rarg2, void* j_rarg3, void* j_rarg4, void* j_rarg5, bool* should_return) //j_rarg0 is this object in non static methods
{
	//set should_return to true to cancel the call
	std::cout << "a";
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
		//Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/client/gui/GuiScreen"));
		//jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "mouseClicked", "(III)V");

		Ripterms::JavaClassV2 lol2("net/minecraft/network/NetworkManager");
		jmethodID mid = lol2.getMethodID("sendPacket");
		Ripterms::JavaHook::add_to_java_hook(mid, callback);
	}
}