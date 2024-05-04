#include "Modules.h"
#include <imgui.h>
#include "../Cache/Cache.h"

void Ripterms::Modules::FastPlace::run()
{
	if (!enabled || !GetAsyncKeyState(VK_RBUTTON)) return;
	if (Ripterms::cache->theMinecraft.getRightClickDelayTimer() == 4)
	{
		Ripterms::cache->theMinecraft.setRightClickDelayTimer(tickDelay);
	}
}

void Ripterms::Modules::FastPlace::renderGUI()
{
	ImGui::CustomSliderInt("Tick Delay", &tickDelay, 0, 3, "%", 0);
}