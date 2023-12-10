#include "Cache.h"
#include <iostream>

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
	if (!theMinecraft.isValid())
	{
		is_valid = false;
		return false;
	}
	thePlayer = theMinecraft.getThePlayer();
	if (!thePlayer.isValid())
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
