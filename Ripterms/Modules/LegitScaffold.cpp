#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>



void Ripterms::Modules::LegitScaffold::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
	if (!enabled)
		return;
	static bool sneaked = false;
	static int elapsedTicks = 0;

	if (sneaked)
		elapsedTicks++;
	else
		elapsedTicks = 0;

	Minecraft theMinecraft = Minecraft::getTheMinecraft(env);
	EntityPlayerSP thePlayer = theMinecraft.getThePlayer();
	WorldClient theWorld = theMinecraft.getTheWorld();
	GameSettings gameSettings = theMinecraft.getGameSettings();
	KeyBinding keyBindSneak = gameSettings.getKeyBindSneak();

	if ((GetKeyState(0x53) & 0x8000) && thePlayer.isOnGround())
	{
		AxisAlignedBB thePlayerbb = thePlayer.getBoundingBox();
		Ripterms::Maths::Vector3d playerPosition
		(
			thePlayerbb.getMinX() + (thePlayerbb.getMaxX() - thePlayerbb.getMinX()) / 2.0,
			thePlayerbb.getMinY(),
			thePlayerbb.getMinZ() + (thePlayerbb.getMaxZ() - thePlayerbb.getMinZ()) / 2.0
		);
		playerPosition.y -= 0.1;
		Block playerBlock = theWorld.getBlock(playerPosition);
		if (playerBlock.instanceOf(JavaClassV2("net/minecraft/block/BlockAir").get_jclass(env)))
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

void Ripterms::Modules::LegitScaffold::renderGUI()
{
	ImGui::CustomSliderInt("delay", &tickDelay, 0, 10, 0, 0);
}