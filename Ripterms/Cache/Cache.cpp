#include "Cache.h"
#include <iostream>
#include "../../net/minecraft/client/renderer/ActiveRenderInfo/ActiveRenderInfo.h"

Ripterms::Cache::Cache()
{
}

Ripterms::Cache::~Cache()
{
	prev_thePlayer.clear();
}

bool Ripterms::Cache::fillCache()
{
	theMinecraft = Minecraft::getTheMinecraft();
	if (!theMinecraft.isValid()) return false;
	thePlayer = theMinecraft.getThePlayer();
	if (!thePlayer.isValid()) return false;
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
		//MODELVIEW = ActiveRenderInfo::getMODELVIEW();
		//PROJECTION = ActiveRenderInfo::getPROJECTION();
		//VIEWPORT = ActiveRenderInfo::getVIEWPORT();
	}
	return true;
}
