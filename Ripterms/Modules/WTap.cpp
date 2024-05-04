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