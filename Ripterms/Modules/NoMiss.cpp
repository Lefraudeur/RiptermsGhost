#include "Modules.h"
#include "../Hook/JavaHook.h"

void Ripterms::Modules::NoMiss::renderGUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("NoMiss", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void Ripterms::Modules::NoMiss::onClickMouse(JNIEnv* env, Minecraft& theMinecraft, bool* cancel)
{
	if (!enabled) return;
	if (theMinecraft.getObjectMouseOver().getType().isEqualTo(MovingObjectType::getType("MISS", env)))
	{
		Ripterms::JavaHook::set_return_value<uint64_t>(cancel, 0);
		*cancel = true;
	}
}