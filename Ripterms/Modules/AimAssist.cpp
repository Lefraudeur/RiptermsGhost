#include "Modules.h"

void Ripterms::Modules::AimAssist::run()
{
	static EntityPlayer prev_selected_target{};
	if (!enabled || !(GetKeyState(VK_LBUTTON) & 0x8000) || GUI::draw)
	{
		prev_selected_target.clear();
		return;
	}

	static Ripterms::CTimer timer = std::chrono::milliseconds(10);
	if (!timer.isElapsed())
		return;

	Maths::Vector3d thePlayer_position = cache->thePlayer.getPosition();
	thePlayer_position.y += cache->thePlayer.getEyeHeight();

	Maths::Vector2d thePlayer_rotation = cache->thePlayer.getRotation();
	float cropped_thePlayer_yaw = Ripterms::Maths::cropAngle180(thePlayer_rotation.x);
	float cropped_thePlayer_pitch = thePlayer_rotation.y;

	EntityPlayer selected_target{};
	float selected_target_YawToAdd = 0.0f;
	float selected_target_PitchToAdd = 0.0f;

	for (EntityPlayer& target : Ripterms::cache->playerEntities.toVector<EntityPlayer>())
	{
		if (target.isEqualTo(cache->thePlayer))
			continue;

		AxisAlignedBB targetBB = target.getBoundingBox();
		Maths::Vector3d target_position
		(
			targetBB.getMinX() + (targetBB.getMaxX() - targetBB.getMinX()) / 2.0f,
			targetBB.getMinY() + (targetBB.getMaxY() - targetBB.getMinY()) / 2.0f,
			targetBB.getMinZ() + (targetBB.getMaxZ() - targetBB.getMinZ()) / 2.0f
		);
		target_position = target_position + target.getMovementVector(cache->timer.getRenderPartialTicks());

		Maths::Vector2d target_required_rotation = Maths::getYawPitch(thePlayer_position, target_position);
		float yawToAdd = target_required_rotation.x - cropped_thePlayer_yaw;
		float pitchToAdd = target_required_rotation.y - cropped_thePlayer_pitch;
		yawToAdd = Ripterms::Maths::cropAngle180(yawToAdd);
		float target_distance = (target_position - thePlayer_position).distance();
		if (target_distance <= max_distance && target_distance > 0.5 && std::abs(yawToAdd) <= max_angle)
		{
			if (prev_selected_target.isValid() && prev_selected_target.isEqualTo(target))
			{
				selected_target = target;
				selected_target_YawToAdd = yawToAdd;
				selected_target_PitchToAdd = pitchToAdd;
				break;
			}
			if (!selected_target.isValid() || std::abs(yawToAdd) < std::abs(selected_target_YawToAdd))
			{
				selected_target = target;
				selected_target_YawToAdd = yawToAdd;
				selected_target_PitchToAdd = pitchToAdd;
			}
		}
		else if (prev_selected_target.isValid() && prev_selected_target.isEqualTo(target))
		{
			prev_selected_target.clear();
		}
	}

	if (selected_target.isValid())
	{
		prev_selected_target = selected_target;
		Ripterms::Maths::Vector3d selected_target_mvmt_vec = selected_target.getMovementVector(cache->timer.getRenderPartialTicks());
		AxisAlignedBB selected_target_bb = selected_target.getBoundingBox();
		Ripterms::Maths::Vector3d positionsToCheck[] =
		{
			Ripterms::Maths::Vector3d(selected_target_bb.getMinX(), selected_target_bb.getMinY(), selected_target_bb.getMaxZ()) + selected_target_mvmt_vec,
			Ripterms::Maths::Vector3d(selected_target_bb.getMaxX(), selected_target_bb.getMinY(), selected_target_bb.getMinZ()) + selected_target_mvmt_vec,
			Ripterms::Maths::Vector3d(selected_target_bb.getMaxX(), selected_target_bb.getMinY(), selected_target_bb.getMaxZ()) + selected_target_mvmt_vec,
			Ripterms::Maths::Vector3d(selected_target_bb.getMinX(), selected_target_bb.getMinY(), selected_target_bb.getMinZ()) + selected_target_mvmt_vec
		};
		float minYaw = 361.0f, maxYaw = -1.0f;
		float minPitch = 0.0f, maxPitch = 0.0f;
		for (const Ripterms::Maths::Vector3d& position : positionsToCheck)
		{
			Ripterms::Maths::Vector2d YawPitch = Maths::getYawPitch(thePlayer_position, position);
			float Yaw = YawPitch.x;
			if (Yaw < 0.0f) Yaw += 360.0f;
			if (Yaw < minYaw) minYaw = Yaw;
			if (Yaw > maxYaw) maxYaw = Yaw;
			maxPitch = YawPitch.y;
		}

		if (minYaw > 180.0f) minYaw -= 360.0f;
		if (maxYaw > 180.0f) maxYaw -= 360.0f;

		Ripterms::Maths::Vector2d YawPitch = Maths::getYawPitch
		(
			thePlayer_position,
			Ripterms::Maths::Vector3d(selected_target_bb.getMaxX(), selected_target_bb.getMaxY(), selected_target_bb.getMaxZ()) + selected_target_mvmt_vec
		);
		minPitch = YawPitch.y;

		//don't even ask, some random calculations that sometimes bypass anticheats
		float maxDelta = std::abs(Ripterms::Maths::cropAngle180((maxYaw - minYaw))) / 2.0f;
		float difference = std::abs(selected_target_YawToAdd) - maxDelta;
		if (std::abs(selected_target_YawToAdd) > maxDelta)
		{
			if (difference < 2.0f)
			{
				thePlayer_rotation.x += difference * (selected_target_YawToAdd > 0.0f ? 1.0f : -1.0f);
			}
			else if (difference >= 16.0f)
			{
				std::uniform_int_distribution<> distr(int(400.0f * multiplier), int(800.0f * multiplier));
				thePlayer_rotation.x += (float(distr(gen)) / 100.0f) * (selected_target_YawToAdd > 0.0f ? 1.0f : -1.0f);
			}
			else if (difference >= 8.0f)
			{
				std::uniform_int_distribution<> distr(int(250.0f * multiplier), int(400.0f * multiplier));
				thePlayer_rotation.x += (float(distr(gen)) / 100.0f) * (selected_target_YawToAdd > 0.0f ? 1.0f : -1.0f);
			}
			else if (difference >= 4.0f)
			{
				std::uniform_int_distribution<> distr(int(100.0f * multiplier), int(200.0f * multiplier));
				thePlayer_rotation.x += (float(distr(gen)) / 100.0f) * (selected_target_YawToAdd > 0.0f ? 1.0f : -1.0f);
			}
			else
			{
				std::uniform_int_distribution<> distr(int(25.0f * multiplier), int(100.0f * multiplier));
				thePlayer_rotation.x += (float(distr(gen)) / 100.0f) * (selected_target_YawToAdd > 0.0f ? 1.0f : -1.0f);
			}
		}

		float maxPitchDelta = std::abs(maxPitch - minPitch) / 2.0f;
		difference = std::abs(selected_target_PitchToAdd) - maxPitchDelta;
		if (std::abs(selected_target_PitchToAdd) > maxPitchDelta)
		{
			if (difference < 2.0f)
			{
				thePlayer_rotation.y += difference * (selected_target_PitchToAdd > 0.0f ? 1.0f : -1.0f);
			}
			else if (difference >= 16.0f)
			{
				std::uniform_int_distribution<> distr(int(400.0f * multiplierPitch), int(800.0f * multiplierPitch));
				thePlayer_rotation.y += (float(distr(gen)) / 100.0f) * (selected_target_PitchToAdd > 0.0f ? 1.0f : -1.0f);
			}
			else if (difference >= 8.0f)
			{
				std::uniform_int_distribution<> distr(int(250.0f * multiplierPitch), int(400.0f * multiplierPitch));
				thePlayer_rotation.y += (float(distr(gen)) / 100.0f) * (selected_target_PitchToAdd > 0.0f ? 1.0f : -1.0f);
			}
			else if (difference >= 4.0f)
			{
				std::uniform_int_distribution<> distr(int(100.0f * multiplierPitch), int(200.0f * multiplierPitch));
				thePlayer_rotation.y += (float(distr(gen)) / 100.0f) * (selected_target_PitchToAdd > 0.0f ? 1.0f : -1.0f);
			}
			else
			{
				std::uniform_int_distribution<> distr(int(25.0f * multiplierPitch), int(100.0f * multiplierPitch));
				thePlayer_rotation.y += (float(distr(gen)) / 100.0f) * (selected_target_PitchToAdd > 0.0f ? 1.0f : -1.0f);
			}
		}
		cache->thePlayer.setRotation(thePlayer_rotation);
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
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) 
		display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if(ImGui::ArrowButton("aimopt", ImGuiDir_Down)) 
		display_options = !display_options;
	if (display_options)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		ImGui::SliderFloat("Max Distance", &max_distance, 1.0f, 6.0f, "%.1f");
		ImGui::SliderFloat("Max Angle", &max_angle, 10.0f, 180.0f, "%.1f");
		ImGui::SliderFloat("Multiplier Yaw", &multiplier, 0.1f, 2.0f, "%.1f");
		ImGui::SliderFloat("Multiplier Pitch", &multiplierPitch, 0.1f, 2.0f, "%.1f");
		ImGui::EndGroup();
	}
}