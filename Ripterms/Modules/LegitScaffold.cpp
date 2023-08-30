#include "Modules.h"

void Ripterms::Modules::LegitScaffold::onEvent(Ripterms::Event* event)
{
	if (event->type == Ripterms::Event::PRE_MOTION)
	{
	}
}

void Ripterms::Modules::LegitScaffold::renderGUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Legit Scaffold", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}