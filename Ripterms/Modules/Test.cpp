#include "Modules.h"
#include <ImGui/imgui.h>
#include <iostream>


static void callback(uint64_t sp, uint64_t j_rarg0, uint64_t j_rarg1, uint64_t j_rarg2)
{
	std::cout << j_rarg1 << '\n';
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

		Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/network/NetworkManager"));
		jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "sendPacket", "(Lnet/minecraft/network/Packet;)V");
		Ripterms::JavaHook::add_to_java_hook(mid, callback);
	}
}