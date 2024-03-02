#include "Modules.h"

void Ripterms::Modules::Speed::renderGUI()
{
	ImGui::Checkbox("Speed", &enabled);
	if (enabled)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 15.0f);
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