#include "Modules.h"
#include <ImGui/imgui.h>
#include "../Cache/Cache.h"
#include <iostream>

static void callback(const Ripterms::JavaHook::JavaParameters& params)
{
	EntityPlayer a(params.get_jobject_at(0));
	std::cout << a.getPosition().x << std::endl;
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
		Ripterms::JavaClassV2 PlayerControllerMPClass{ "net/minecraft/client/multiplayer/PlayerControllerMP" };
		jmethodID mid = PlayerControllerMPClass.getMethodID("attackEntity");
		Ripterms::JavaHook::add_to_java_hook(mid, callback);
	}
}