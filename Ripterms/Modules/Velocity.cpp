#include "Modules.h"

void Ripterms::Modules::Velocity::run()
{
	if (!enabled) return;
	if (Ripterms::cache->thePlayer.getHurtResistantTime() != 20 - tickDelay) return;

	Maths::Vector3d thePlayer_position = cache->thePlayer.getPosition();
	Maths::Vector2d thePlayer_rotation = cache->thePlayer.getRotation();
	float cropped_thePlayer_yaw = Ripterms::Maths::cropAngle180(thePlayer_rotation.x);

	for (EntityPlayer& target : Ripterms::cache->playerEntities.toVector<EntityPlayer>())
	{
		if (target.isEqualTo(Ripterms::cache->thePlayer)) 
			continue;

		Maths::Vector3d target_position = target.getPosition();

		if (only_facing && (target_position - thePlayer_position).distance() >= 10.0f)
			continue;

		Maths::Vector2d target_required_rotation = Maths::getYawPitch(thePlayer_position, target_position);

		float yawToAdd = target_required_rotation.x - cropped_thePlayer_yaw;
		yawToAdd = Ripterms::Maths::cropAngle180(yawToAdd);

		if (!only_facing || std::abs(yawToAdd) <= 60.0f)
		{
			Ripterms::Maths::Vector3d motion = Ripterms::cache->thePlayer.getMotion();
			motion.x *= motionX;
			motion.y *= motionY;
			motion.z *= motionZ;
			Ripterms::cache->thePlayer.setMotion(motion);
			return;
		}
	}
}

void Ripterms::Modules::Velocity::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Velocity", &enabled);
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("velopt", ImGuiDir_Down)) display_options = !display_options;
	if (display_options)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		{
			ImGui::SliderFloat("Motion X", &motionX, 0.0f, 1.0f, "%.1f");
			ImGui::SliderFloat("Motion Y", &motionY, 0.0f, 1.0f, "%.1f");
			ImGui::SliderFloat("Motion Z", &motionZ, 0.0f, 1.0f, "%.1f");
			ImGui::SliderInt("Tick Delay", &tickDelay, 0, 20);
			ImGui::Checkbox("Only Facing Enemy", &only_facing);
		}
		ImGui::EndGroup();
	}
	ImGui::PopStyleVar();
}
