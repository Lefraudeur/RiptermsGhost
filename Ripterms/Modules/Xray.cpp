#include "Modules.h"
#include <imgui.h>
#include "../Hook/JavaHook.h"
#include "../Cache/Cache.h"
#include "../../net/minecraft/client/renderer/ActiveRenderInfo/ActiveRenderInfo.h"
#include "../GUI/GUI.h"

void Ripterms::Modules::Xray::renderGUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Xray (crash)", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void Ripterms::Modules::Xray::render()
{
	if (!enabled) return;

	ImVec2 screenSize = ImGui::GetWindowSize();

	Ripterms::Maths::Vector3d a{ 0, 74, 0 };
	Ripterms::Maths::Vector3d p = a - (Ripterms::cache->thePlayer.getLastTickPosition() + Ripterms::cache->thePlayer.getMovementVector(Ripterms::cache->timer.getRenderPartialTicks()));

	Ripterms::Maths::Vector2d sp{};
	if(!Ripterms::Maths::worldToScreen(p, ActiveRenderInfo::get_cached_MODELVIEW(), ActiveRenderInfo::get_cached_PROJECTION(), screenSize.x, screenSize.y, sp))
		return;

	ImGui::GetWindowDrawList()->AddCircle(ImVec2(sp.x, sp.y), 10, ImColor(255, 0, 0), 100, 2);
}

void Ripterms::Modules::Xray::onShouldSideBeRendered(JNIEnv* env, Block& block, bool* cancel)
{
	if (!enabled) return;
	if (!block.instanceOf(Ripterms::JavaClassV2("net/minecraft/block/BlockOre").get_jclass(env)))
		Ripterms::JavaHook::set_return_value<uint64_t>(cancel, 0);
	else
		Ripterms::JavaHook::set_return_value<uint64_t>(cancel, 1);
	*cancel = true;
}
