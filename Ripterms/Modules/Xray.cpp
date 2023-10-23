#include "Modules.h"
#include <imgui.h>
#include "../Cache/Cache.h"

void Ripterms::Modules::Xray::run()
{
	static bool prev_enabled = false;
	if (!enabled)
	{
		if (prev_enabled)
		{
			disable();
			prev_enabled = false;
		}
		return;
	}
	if (!prev_enabled)
	{
		Ripterms::cache->EMPTY_MAP.put(String("xray_enabled"), String("1"));
		prev_enabled = true;
	}
}

void Ripterms::Modules::Xray::renderGUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Xray", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void Ripterms::Modules::Xray::disable()
{
	Ripterms::cache->EMPTY_MAP.put(String("xray_enabled"), String("0"));
}