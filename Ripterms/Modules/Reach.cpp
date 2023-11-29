#include "Modules.h"
#include "../Cache/Cache.h"
#include "../../java/lang/String/String.h"
#include <ImGui/imgui.h>


void Ripterms::Modules::Reach::run()
{
	static float prev_reach_distance = -1.0f;
	if (!enabled)
	{
		if (prev_reach_distance != -1.0f)
		{
			//reset here
			prev_reach_distance = -1.0f;
		}
		return;
	}
	if (prev_reach_distance == reach_distance) return;
	//set here
	prev_reach_distance = reach_distance;
}

void Ripterms::Modules::Reach::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Reach", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("opt", ImGuiDir_Down)) display_options = !display_options;
	if (display_options) {
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		ImGui::SliderFloat("Reach Distance", &reach_distance, 3.0f, 4.0f, "%.1f");
		ImGui::EndGroup();
	}
}
