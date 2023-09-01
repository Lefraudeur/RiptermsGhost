#include "Modules.h"

void Ripterms::Modules::LegitScaffold::onEvent(Ripterms::Event* event)
{
	if (!enabled)
		return;

	if (event->type == Ripterms::Event::PRE_MOTION)
	{
		static bool sneaked = false;
		static int elapsedTicks = 0;

		if (sneaked)
			elapsedTicks++;
		else
			elapsedTicks = 0;

		Minecraft theMinecraft = Minecraft::getTheMinecraft(event->env);
		EntityPlayerSP thePlayer = theMinecraft.getThePlayer();
		WorldClient theWorld = theMinecraft.getTheWorld();
		GameSettings gameSettings = theMinecraft.getGameSettings();
		KeyBinding keyBindSneak = gameSettings.getKeyBindSneak();

		if ((GetKeyState(0x53) & 0x8000) && thePlayer.isOnGround())
		{
			AxisAlignedBB thePlayerbb = thePlayer.getBoundingBox();
			Ripterms::Maths::Vector3d playerPosition
			(
				thePlayerbb.getMinX() + (thePlayerbb.getMaxX() - thePlayerbb.getMinX()) / 2.0f,
				thePlayerbb.getMinY(),
				thePlayerbb.getMinZ() + (thePlayerbb.getMaxZ() - thePlayerbb.getMinZ()) / 2.0f
			);
			playerPosition.y -= 0.1f;
			Block playerBlock = theWorld.getBlock(playerPosition);
			if (playerBlock.instanceOf(JavaClassV2("net/minecraft/block/BlockAir").getJClass(event->env)))
			{
				sneaked = true;
				keyBindSneak.setPressed(true);
				return;
			}
		}
		if (sneaked && elapsedTicks > tickDelay)
		{
			keyBindSneak.setPressed(false);
			sneaked = false;
		}
	}
}

void Ripterms::Modules::LegitScaffold::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Legit Scaffold", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("lso", ImGuiDir_Down))
		display_options = !display_options;
	if (display_options)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		ImGui::SliderInt("delay", &tickDelay, 0, 10);
		ImGui::EndGroup();
	}
}