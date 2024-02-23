#include "Modules.h"

void Ripterms::Modules::Speed::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Speed", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("SpeedOpt", ImGuiDir_Down))
		display_options = !display_options;
	if (display_options)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		ImGui::SliderFloat("Speed abpt", &speed, 0.01f, 2.0f, "%.2f");
		ImGui::EndGroup();
	}
}

void Ripterms::Modules::Speed::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
	if (!enabled || !(GetKeyState(0x5A) & 0x8000) || !this_player.isOnGround()) return;
	Ripterms::Maths::Vector3d motion = this_player.getMotion();
	Ripterms::Maths::Vector3d additional = Ripterms::Maths::getCameraVector(this_player.getRotation(), speed);
	motion.x += additional.x;
	motion.z += additional.z;
	this_player.setMotion(motion);
}