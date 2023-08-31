#include "Modules.h"

void Ripterms::Modules::LeftClicker::run()
{
	static CTimer timer(std::chrono::milliseconds(1000/min_cps));
	if (!enabled || Ripterms::GUI::draw || !(GetKeyState(VK_LBUTTON) & 0x8000)) 
		return;
	if (!timer.isElapsed()) 
		return;
	if (Ripterms::cache->theMinecraft.getObjectMouseOver().getType().isEqualTo(MovingObjectType::getType("BLOCK")))
		return;
	POINT cursorPos{};
	GetCursorPos(&cursorPos);
	SendMessageA(Ripterms::window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
	SendMessageA(Ripterms::window, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
	std::uniform_int_distribution<> distr(min_cps, max_cps);
	timer.setEvery(std::chrono::milliseconds(1000 / distr(gen)));
}

void Ripterms::Modules::LeftClicker::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(220.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Left Clicker", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) 
		display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("lc", ImGuiDir_Down)) 
		display_options = !display_options;
	if (display_options)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		ImGui::SliderInt("Min CPS", &min_cps, 1, 150);
		ImGui::SliderInt("Max CPS", &max_cps, 1, 150);
		ImGui::EndGroup();
	}
}
