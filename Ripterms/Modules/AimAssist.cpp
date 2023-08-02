#include "Modules.h"
#include <ImGui/imgui.h>

bool enabled = false;

void Ripterms::Modules::AimAssist::run()
{
	if (!enabled) return;
}

void Ripterms::Modules::AimAssist::renderGUI()
{
	ImGui::Checkbox("Aim Assist", &enabled);
}
