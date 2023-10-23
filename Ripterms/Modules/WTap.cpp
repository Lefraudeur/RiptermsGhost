#include "Modules.h"
#include "../../net/minecraft/client/Minecraft/Minecraft.h"
#include <imgui.h>

void Ripterms::Modules::WTap::onEvent(Ripterms::Event* event)
{
	static int ticks = 10;

	if (!enabled)
		return;

	if (event->type == Ripterms::Event::Type::PRE_ATTACK)
	{
		ticks = 0;
	}
	else if (event->type == Event::Type::PRE_MOTION)
	{
		++ticks;
		EntityPlayerSP thePlayer = Minecraft::getTheMinecraft(event->env).getThePlayer();
		if (thePlayer.isSprinting())
		{
			if (ticks == 2) thePlayer.setSprinting(false);
			if (ticks == 3) thePlayer.setSprinting(true);
		}
	}
}

void Ripterms::Modules::WTap::renderGUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("WTap", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}