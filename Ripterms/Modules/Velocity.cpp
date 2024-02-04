#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>

void Ripterms::Modules::Velocity::run()
{
	if (!enabled) return;
	if (Ripterms::cache->thePlayer.getHurtResistantTime() != 20 - tickDelay) return;

	Ripterms::Maths::Vector3d motion = Ripterms::cache->thePlayer.getMotion();
	motion.x *= motionX;
	motion.y *= motionY;
	motion.z *= motionZ;
	Ripterms::cache->thePlayer.setMotion(motion);
}

void Ripterms::Modules::Velocity::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Velocity", &enabled);
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("velopt", ImGuiDir_Down)) display_options = !display_options;
	if (display_options)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		{
			ImGui::SliderFloat("Motion X", &motionX, -2.0f, 2.0f, "%.1f");
			ImGui::SliderFloat("Motion Y", &motionY, -2.0f, 2.0f, "%.1f");
			ImGui::SliderFloat("Motion Z", &motionZ, -2.0f, 2.0f, "%.1f");
			ImGui::SliderInt("Tick Delay", &tickDelay, 0, 20);
		}
		ImGui::EndGroup();
	}
	ImGui::PopStyleVar();
}
