#include "Modules.h"
#include <ImGui/imgui.h>
#include <iostream>

static void callback(uint64_t sp, uint64_t j_rarg0, uint64_t j_rarg1, uint64_t j_rarg2)
{
	if (!sp && !j_rarg0 && !j_rarg1 && !j_rarg2) //some garbage code, so that the compiler doesn't  fuck up everything
		return;
	int y = (int)j_rarg2;
	int x = (int)j_rarg1;
	if (y != 0 || x != 0)
		std::cout << std::to_string(x) << '\n';
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
		Ripterms::JavaHook::add_to_java_hook(mid, callback);
	}
}