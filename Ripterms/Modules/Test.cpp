#include "Modules.h"
#include <ImGui/imgui.h>
#include <iostream>

static void callback(uint64_t sp, uint64_t j_rarg0, uint64_t j_rarg1, uint64_t j_rarg2)
{

	std::cout << std::to_string(sp) << std::endl;
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
		Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/client/Minecraft"));
		jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "runTick", "()V");
		Ripterms::JavaHook::add_to_java_hook(mid, callback);
	}
}