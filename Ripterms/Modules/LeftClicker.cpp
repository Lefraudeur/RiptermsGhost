#include "Modules.h"
#include "../GUI/GUI.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>

void Ripterms::Modules::LeftClicker::run()
{
	static CTimer timer(std::chrono::milliseconds(1000/min_cps));
	if (!enabled || Ripterms::GUI::draw || !(GetKeyState(VK_LBUTTON) & 0x8000) || cache->theMinecraft.getCurrentScreen().isValid())
		return;
	if (!timer.isElapsed()) 
		return;
	if (Ripterms::cache->theMinecraft.getObjectMouseOver().getType().isEqualTo(MovingObjectType::getType("BLOCK")))
		return;
	POINT cursorPos{};
	GetCursorPos(&cursorPos);
	PostMessageA(Ripterms::window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
	PostMessageA(Ripterms::window, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
	std::uniform_int_distribution<> distr(min_cps, max_cps);
	timer.setEvery(std::chrono::milliseconds(1000 / distr(gen)));
}

void Ripterms::Modules::LeftClicker::renderGUI()
{
	ImGui::CustomSliderInt("Min CPS", &min_cps, 1, 150, 0, 0);
	ImGui::CustomSliderInt("Max CPS", &max_cps, 1, 150, 0, 0);
}
