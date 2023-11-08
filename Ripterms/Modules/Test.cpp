#include "Modules.h"
#include <ImGui/imgui.h>
#include "../Cache/Cache.h"
#include <iostream>

static void callback(const Ripterms::JavaHook::JavaParameters& params)
{
	std::cout << "ha" << std::endl;
	std::cout << params.r8 << std::endl;
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
		Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/client/gui/GuiChat"));
		jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "mouseClicked", "(III)V");
		Ripterms::JavaHook::add_to_java_hook(mid, callback);
	}
}