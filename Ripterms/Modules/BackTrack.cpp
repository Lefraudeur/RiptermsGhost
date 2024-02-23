#include "Modules.h"
#include "../Cache/Cache.h"

void Ripterms::Modules::BackTrack::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("BackTrack", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("BackTrackopt", ImGuiDir_Down))
		display_options = !display_options;
	if (display_options)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		ImGui::SliderFloat("PartialTicks in advance", &partialTicks, 0.01f, 2.0f, "%.2f");
		ImGui::EndGroup();
	}
}

void Ripterms::Modules::BackTrack::run()
{
	if (!enabled) return;
	static Ripterms::CTimer timer = std::chrono::milliseconds(10);
	if (!timer.isElapsed())
		return;

	for (EntityPlayer& player : Ripterms::cache->playerEntities.toVector<EntityPlayer>())
	{
		if (player.isEqualTo(Ripterms::cache->thePlayer)) continue;
		Ripterms::Maths::Vector3d vector = player.getMovementVector(partialTicks);
		AxisAlignedBB bb = player.getBoundingBox();
		Ripterms::Maths::Vector3d minbb(bb.getMinX(), bb.getMinY(), bb.getMinZ());
		Ripterms::Maths::Vector3d maxbb(bb.getMaxX(), bb.getMaxY(), bb.getMaxZ());
		minbb = minbb - vector;
		maxbb = maxbb - vector;

		bb.setMinX(min(minbb.x, bb.getMinX())); bb.setMinY(min(minbb.y, bb.getMinY())); bb.setMinZ(min(minbb.z, bb.getMinZ()));
		bb.setMaxX(max(maxbb.x, bb.getMaxX())); bb.setMaxY(max(maxbb.y, bb.getMaxY())); bb.setMaxZ(max(maxbb.z, bb.getMaxZ()));
	}
}