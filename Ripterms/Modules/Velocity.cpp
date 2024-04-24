#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>

void Ripterms::Modules::Velocity::run()
{
	if (!enabled) return;
	if (Ripterms::cache->thePlayer.getHurtResistantTime() != 20 - tickDelay) return;

	Ripterms::Maths::Vector3d motion = Ripterms::cache->thePlayer.getMotion();
	motion.x *= motionX;
	motion.y *= motionY;
	motion.z *= motionZ;
	Ripterms::cache->thePlayer.setMotion(motion);
}

void Ripterms::Modules::Velocity::renderGUI()
{
	ImGui::IOSToggle ("Velocity", &enabled);
	if (enabled)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 15.0f);
		ImGui::BeginGroup();
		ImGui::CustomSliderFloat ("Motion X", &motionX, -2.0f, 2.0f, "%.1f", 0);
		ImGui::CustomSliderFloat ("Motion Y", &motionY, -2.0f, 2.0f, "%.1f", 0);
		ImGui::CustomSliderFloat ("Motion Z", &motionZ, -2.0f, 2.0f, "%.1f", 0);
		ImGui::CustomSliderInt("Tick Delay", &tickDelay, 0, 20, 0, 0);
		ImGui::EndGroup();
	}
}
