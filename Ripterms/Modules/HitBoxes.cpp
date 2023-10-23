#include "Modules.h"
#include <ImGui/imgui.h>
#include "../../net/minecraft/client/entity/AbstractClientPlayer/AbstractClientPlayer.h"
#include "../Cache/Cache.h"

void Ripterms::Modules::HitBoxes::run()
{
	static Ripterms::CTimer timer(std::chrono::milliseconds(15));
	if (!enabled || !timer.isElapsed())
		return;

	Ripterms::Maths::Vector3d thePlayer_position = cache->thePlayer.getPosition();

	for (EntityPlayer& target : cache->playerEntities.toVector<EntityPlayer>())
	{
		if
		(
			target.isEqualTo(cache->thePlayer) ||
			(target.getPosition() - thePlayer_position).distance() > 9.0f
		)
			continue;

		AxisAlignedBB target_bb = target.getBoundingBox();
		if 
		(
			(target_bb.getMaxX() - target_bb.getMinX()) > 0.61f ||
			(target_bb.getMaxY() - target_bb.getMinY()) > 1.81f
		)
			continue;

		target_bb.setMinX(target_bb.getMinX() - x_expand);
		target_bb.setMaxX(target_bb.getMaxX() + x_expand);
		target_bb.setMinZ(target_bb.getMinZ() - x_expand);
		target_bb.setMaxZ(target_bb.getMaxZ() + x_expand);

		target_bb.setMinY(target_bb.getMinY() - y_expand);
		target_bb.setMaxY(target_bb.getMaxY() + y_expand);
	}
}

void Ripterms::Modules::HitBoxes::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("HitBoxes", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("hbopt", ImGuiDir_Down)) display_options = !display_options;
	if (display_options) {
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		ImGui::SliderFloat("X Expand", &x_expand, 0.01f, 2.0f, "%.01f");
		ImGui::SliderFloat("Y Expand", &y_expand, 0.01f, 2.0f, "%.01f");
		ImGui::EndGroup();
	}
}
