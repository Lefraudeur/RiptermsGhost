#include "Modules.h"
#include "../../net/minecraft/client/Minecraft/Minecraft.h"
#include <imgui.h>


void Ripterms::Modules::WTap::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
	if (!enabled) return;
	++ticks;
	EntityPlayerSP thePlayer = Minecraft::getTheMinecraft(env).getThePlayer();
	if (thePlayer.isSprinting())
	{
		if (ticks == 2 && thePlayer.isSprinting()) 
			thePlayer.setSprinting(false);
		if (ticks == 3 && !thePlayer.isSprinting()) 
			thePlayer.setSprinting(true);
	}
}

void Ripterms::Modules::WTap::onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel)
{
	if (!enabled) return;
	ticks = 0;
}

void Ripterms::Modules::WTap::renderGUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("WTap", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}