#include "Modules.h"

void Ripterms::Modules::Glide::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Glide", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void Ripterms::Modules::Glide::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
	if (!enabled || this_player.getMotion().y > -0.1) return;
	Ripterms::Maths::Vector3d motion = this_player.getMotion();
	motion.y = (this_player.getTicksExisted() % 2 == 0 ? -0.1 : -0.16);
	this_player.setMotion(motion);
}