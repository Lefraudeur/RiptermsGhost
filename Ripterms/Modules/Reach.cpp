#include "Modules.h"
#include "../Patcher/Patcher.h"

namespace
{
	bool enabled = false;
	float reach_distance = 5.0f;
}

void Ripterms::Modules::Reach::run()
{
	static bool prev_enabled = false;
	static double prev_reach = 0.0;
	if (!enabled) {
		if (prev_enabled) {
			Ripterms::p_tienv->RetransformClasses(1, &Ripterms::classcache->EntityRendererClass.javaClass);
		}
		prev_enabled = enabled;
		return;
	}
	prev_enabled = enabled;
	static Timer timer(std::chrono::milliseconds(3000));
	if (!timer.isElapsed() || prev_reach == reach_distance) return;
	prev_reach = reach_distance;
	Ripterms::Patcher::patchGetMouseOver(reach_distance);
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
		ImGui::SliderFloat("Reach Distance", &reach_distance, 3.0f, 5.0f, "%.1f");
		ImGui::EndGroup();
	}
}
