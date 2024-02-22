#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>

void Ripterms::Modules::FullBright::run()
{
	if (!enabled)
	{
		disable();
		return;
	}
	double gamma = Ripterms::cache->gameSettings.getGammaSetting();
	if ( gamma != 50.0)
	{
		Ripterms::cache->gameSettings.setGammaSetting(50.0);
		old_gamma = gamma;
	}
}

void Ripterms::Modules::FullBright::renderGUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Full Bright", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void Ripterms::Modules::FullBright::disable()
{
	if (!Ripterms::p_env) return;
	if (old_gamma >= 0.0)
	{
		Ripterms::cache->gameSettings.setGammaSetting(old_gamma);
		old_gamma = -1.0;
	}
}
