#include "Modules.h"
#include <ImGui/imgui.h>
#include "../Cache/Cache.h"

void Ripterms::Modules::Sprint::run()
{
	if (!enabled)
		return;
	cache->gameSettings.getKeyBindSprint().setPressed(true);
}

void Ripterms::Modules::Sprint::renderGUI()
{
	ImGui::Checkbox("Sprint", &enabled);
}