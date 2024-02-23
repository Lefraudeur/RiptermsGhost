#include "Modules.h"

void Ripterms::Modules::VelocityFly::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("VelocityFly", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("VelocityFlyOpt", ImGuiDir_Down))
		display_options = !display_options;
	if (display_options)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		ImGui::SliderFloat("Speed", &speed, 0.01f, 2.0f, "%.2f");
		ImGui::EndGroup();
	}
}

void Ripterms::Modules::VelocityFly::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
	if (!enabled) return;
	Ripterms::Maths::Vector3d motion = this_player.getMotion();

	if (GetKeyState(0x5A) & 0x8000)
	{
		Ripterms::Maths::Vector3d additional = Ripterms::Maths::getCameraVector(this_player.getRotation(), speed);
		motion.x += additional.x;
		motion.z += additional.z;
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
		motion.y = speed;
	else if (GetKeyState(VK_LSHIFT) & 0x8000)
		motion.y = -speed;
	else motion.y = 0.0;

	if (!this_player.isOnGround())
		this_player.setMotion(motion);
}