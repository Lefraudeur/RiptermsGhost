#include "Modules.h"
#include <ImGui/imgui.h>
#include "../Cache/Cache.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "../GUI/GUI.h"
#include "../../net/minecraft/client/renderer/ActiveRenderInfo/ActiveRenderInfo.h"

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
		Ripterms::Maths::Vector3d position = cache->thePlayer.getPosition();
		position.x += 2.0f;
	}
}