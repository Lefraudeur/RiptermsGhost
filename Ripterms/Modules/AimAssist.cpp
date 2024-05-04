#include "Modules.h"
#include "../GUI/GUI.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>


void Ripterms::Modules::AimAssist::run()
{
	if (!enabled || !(GetKeyState(VK_LBUTTON) & 0x8000) || GUI::draw || cache->theMinecraft.getCurrentScreen().isValid())
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
	double cropped_thePlayer_yaw = Ripterms::Maths::cropAngle180(thePlayer_rotation.x);
	double cropped_thePlayer_pitch = thePlayer_rotation.y;

	EntityPlayer selected_target{};
	double selected_target_YawToAdd = 0.0;
	double selected_target_PitchToAdd = 0.0;

	for (EntityPlayer& target : Ripterms::cache->playerEntities.toVector<EntityPlayer>())
	{
		if (!target.isValid() || target.isEqualTo(cache->thePlayer) || target.getTicksExisted() < 10)
			continue;

		AxisAlignedBB targetBB = target.getBoundingBox();
		Maths::Vector3d target_position
		(
			targetBB.getMinX() + (targetBB.getMaxX() - targetBB.getMinX()) / 2.0,
			targetBB.getMinY() + (targetBB.getMaxY() - targetBB.getMinY()) / 2.0,
			targetBB.getMinZ() + (targetBB.getMaxZ() - targetBB.getMinZ()) / 2.0
		);
		target_position = target_position + target.getMovementVector(cache->timer.getRenderPartialTicks());

		Maths::Vector2d target_required_rotation = Maths::getYawPitch(thePlayer_position, target_position);
		double yawToAdd = target_required_rotation.x - cropped_thePlayer_yaw;
		double pitchToAdd = target_required_rotation.y - cropped_thePlayer_pitch;
		yawToAdd = Ripterms::Maths::cropAngle180(yawToAdd);
		double target_distance = (target_position - thePlayer_position).distance();
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
		double minYaw = 361.0, maxYaw = -1.0;
		double minPitch = 0.0, maxPitch = 0.0;
		for (const Ripterms::Maths::Vector3d& position : positionsToCheck)
		{
			Ripterms::Maths::Vector2d YawPitch = Maths::getYawPitch(thePlayer_position, position);
			double Yaw = YawPitch.x;
			if (Yaw < 0.0) Yaw += 360.0;
			if (Yaw < minYaw) minYaw = Yaw;
			if (Yaw > maxYaw) maxYaw = Yaw;
			maxPitch = YawPitch.y;
		}

		if (minYaw > 180.0) minYaw -= 360.0;
		if (maxYaw > 180.0) maxYaw -= 360.0;

		Ripterms::Maths::Vector2d YawPitch = Maths::getYawPitch
		(
			thePlayer_position,
			Ripterms::Maths::Vector3d(selected_target_bb.getMaxX(), selected_target_bb.getMaxY(), selected_target_bb.getMaxZ()) + selected_target_mvmt_vec
		);
		minPitch = YawPitch.y;

		//don't even ask, some random calculations that sometimes bypass anticheats
		double maxDelta = std::abs(Ripterms::Maths::cropAngle180((maxYaw - minYaw))) / 2.0;
		double difference = std::abs(selected_target_YawToAdd) - maxDelta;
		if (std::abs(selected_target_YawToAdd) > maxDelta)
		{
			if (difference < 2.0)
			{
				thePlayer_rotation.x += difference * (selected_target_YawToAdd > 0.0 ? 1.0 : -1.0);
			}
			else if (difference >= 16.0)
			{
				std::uniform_int_distribution<> distr(int(400.0 * multiplier), int(800.0 * multiplier));
				thePlayer_rotation.x += (double(distr(gen)) / 100.0) * (selected_target_YawToAdd > 0.0 ? 1.0 : -1.0);
			}
			else if (difference >= 8.0)
			{
				std::uniform_int_distribution<> distr(int(250.0 * multiplier), int(400.0 * multiplier));
				thePlayer_rotation.x += (double(distr(gen)) / 100.0) * (selected_target_YawToAdd > 0.0 ? 1.0 : -1.0);
			}
			else if (difference >= 4.0)
			{
				std::uniform_int_distribution<> distr(int(100.0 * multiplier), int(200.0 * multiplier));
				thePlayer_rotation.x += (double(distr(gen)) / 100.0) * (selected_target_YawToAdd > 0.0 ? 1.0 : -1.0);
			}
			else
			{
				std::uniform_int_distribution<> distr(int(25.0 * multiplier), int(100.0 * multiplier));
				thePlayer_rotation.x += (double(distr(gen)) / 100.0) * (selected_target_YawToAdd > 0.0 ? 1.0 : -1.0);
			}
		}

		double maxPitchDelta = std::abs(maxPitch - minPitch) / 2.0;
		difference = std::abs(selected_target_PitchToAdd) - maxPitchDelta;
		if (std::abs(selected_target_PitchToAdd) > maxPitchDelta)
		{
			if (difference < 2.0)
			{
				thePlayer_rotation.y += difference * (selected_target_PitchToAdd > 0.0 ? 1.0 : -1.0);
			}
			else if (difference >= 16.0)
			{
				std::uniform_int_distribution<> distr(int(400.0 * multiplierPitch), int(800.0 * multiplierPitch));
				thePlayer_rotation.y += (double(distr(gen)) / 100.0) * (selected_target_PitchToAdd > 0.0 ? 1.0 : -1.0);
			}
			else if (difference >= 8.0)
			{
				std::uniform_int_distribution<> distr(int(250.0 * multiplierPitch), int(400.0 * multiplierPitch));
				thePlayer_rotation.y += (double(distr(gen)) / 100.0) * (selected_target_PitchToAdd > 0.0 ? 1.0 : -1.0);
			}
			else if (difference >= 4.0)
			{
				std::uniform_int_distribution<> distr(int(100.0 * multiplierPitch), int(200.0 * multiplierPitch));
				thePlayer_rotation.y += (double(distr(gen)) / 100.0) * (selected_target_PitchToAdd > 0.0 ? 1.0 : -1.0);
			}
			else
			{
				std::uniform_int_distribution<> distr(int(25.0 * multiplierPitch), int(100.0 * multiplierPitch));
				thePlayer_rotation.y += (double(distr(gen)) / 100.0) * (selected_target_PitchToAdd > 0.0 ? 1.0 : -1.0);
			}
		}
		cache->thePlayer.setRotation(thePlayer_rotation);
	}
}

void Ripterms::Modules::AimAssist::renderGUI()
{
	ImGui::CustomSliderFloat ("Max Distance", &max_distance, 1.0f, 6.0f, "%.1f", 0);
	ImGui::CustomSliderFloat ("Max Angle", &max_angle, 10.0f, 180.0f, "%.1f", 0);
	ImGui::CustomSliderFloat ("Multiplier Yaw", &multiplier, 0.1f, 2.0f, "%.1f", 0);
	ImGui::CustomSliderFloat ("Multiplier Pitch", &multiplierPitch, 0.0f, 2.0f, "%.1f", 0);
}

void Ripterms::Modules::AimAssist::render()
{
}

void Ripterms::Modules::AimAssist::disable()
{
	prev_selected_target.clear();
}
