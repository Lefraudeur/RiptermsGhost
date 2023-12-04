#include "Modules.h"
#include <ImGui/imgui.h>
#include "../../net/minecraft/client/Minecraft/Minecraft.h"

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

void Ripterms::Modules::HitBoxes::onSetEntityBoundingBox(JNIEnv* env, Entity& this_entity, AxisAlignedBB& boundingBox, bool* cancel)
{
	if (!enabled) return;
	if (!this_entity.instanceOf(Ripterms::JavaClassV2("net/minecraft/entity/player/EntityPlayer").getJClass(env))) return;
	if (this_entity.isEqualTo(Minecraft::getTheMinecraft(env).getThePlayer())) return;
	boundingBox.setMaxX(boundingBox.getMaxX() + x_expand);
	boundingBox.setMinX(boundingBox.getMinX() - x_expand);
	boundingBox.setMaxZ(boundingBox.getMaxZ() + x_expand);
	boundingBox.setMinZ(boundingBox.getMinZ() - x_expand);
	boundingBox.setMinY(boundingBox.getMinY() - y_expand);
	boundingBox.setMaxY(boundingBox.getMaxY() + y_expand);
}
