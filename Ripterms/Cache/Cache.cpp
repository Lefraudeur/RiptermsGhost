#include "Cache.h"
#include "../../net/minecraft/client/renderer/ActiveRenderInfo/ActiveRenderInfo.h"
#include <iostream>

bool Ripterms::Cache::fillCache()
{
	Ripterms::JNIFrame jni_frame(Ripterms::p_env, 20);

	theMinecraft = Minecraft::getTheMinecraft();
	if (!theMinecraft.isValid())
	{
		is_valid = false;
		return false;
	}
	thePlayer = theMinecraft.getThePlayer();
	if (!thePlayer.isValid() || thePlayer.getTicksExisted() < 10)
	{
		is_valid = false;
		return false;
	}
	if (!prev_thePlayer.isEqualTo(thePlayer))
	{
		std::clog << "object updated" << std::endl;
		prev_thePlayer = thePlayer;
		theWorld = theMinecraft.getTheWorld();
		playerEntities = theWorld.getPlayerEntities();
		gameSettings = theMinecraft.getGameSettings();
		timer = theMinecraft.getTimer();
		playerController = theMinecraft.getPlayerController();
		sendQueue = thePlayer.getSendQueue();
	}
	is_valid = true;
	return true;
}
