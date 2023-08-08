#include "Modules.h"

namespace
{
	bool enabled = false;
	float max_distance = 6.0f;
	float max_angle = 120.0f;
}

void Ripterms::Modules::AimAssist::run()
{
	static EntityPlayer prev_selected_target{};
	if (!enabled || !(GetKeyState(VK_LBUTTON) & 0x8000) || GUI::draw) {
		prev_selected_target.clear();
		return;
	}
	static Timer timer(std::chrono::milliseconds(5));
	if (!timer.isElapsed()) return;

	Maths::Vector3d thePlayer_position = cache->thePlayer.getPosition();
	Maths::Vector2d thePlayer_rotation = cache->thePlayer.getRotation();
	float cropped_thePlayer_yaw = Ripterms::Maths::cropAngle180(thePlayer_rotation.x);
	
	EntityPlayer selected_target{};
	float selected_target_YawToAdd = 0.0f;

	for (EntityPlayer& target : Ripterms::cache->playerEntities.toVector<EntityPlayer>()) {
		if (target.isEqualTo(cache->thePlayer)) continue;
		Maths::Vector3d target_position = target.getPosition();
		Maths::Vector2d target_required_rotation = Maths::getYawPitch(thePlayer_position, target_position);
		float yawToAdd = target_required_rotation.x - cropped_thePlayer_yaw;
		yawToAdd = Ripterms::Maths::cropAngle180(yawToAdd);
		float target_distance = (target_position - thePlayer_position).distance();
		if (target_distance <= max_distance && std::abs(yawToAdd) <= max_angle) {
			if (prev_selected_target.isValid() && prev_selected_target.isEqualTo(target)) {
				selected_target = target;
				selected_target_YawToAdd = yawToAdd;
				break;
			}
			if (!selected_target || std::abs(yawToAdd) < std::abs(selected_target_YawToAdd)) {
				selected_target = target;
				selected_target_YawToAdd = yawToAdd;
			}
		}
		else if (prev_selected_target.isValid() && prev_selected_target.isEqualTo(target)) {
			prev_selected_target.clear();
		}
	}

	if (selected_target.isValid()) {
		prev_selected_target = selected_target;
		if (std::abs(selected_target_YawToAdd) > 4.0f) {
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> range_yaw(-8, 198);
			thePlayer_rotation.x += (selected_target_YawToAdd > 0.0f ? range_yaw(gen) / 100.0f : -range_yaw(gen) / 100.0f);
			cache->thePlayer.setRotation(thePlayer_rotation);
		}
	}
}

void Ripterms::Modules::AimAssist::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Aim Assist", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if(ImGui::ArrowButton("test", ImGuiDir_Down)) display_options = !display_options;
	if (display_options) {
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		ImGui::SliderFloat("Max Distance", &max_distance, 1.0f, 12.0f, "%.1f");
		ImGui::SliderFloat("Max Angle", &max_angle, 10.0f, 180.0f, "%.1f");
		ImGui::EndGroup();
	}
}
