#include "Cache.h"
#include <iostream>

bool Ripterms::Cache::fillCache()
{
	static EntityPlayerSP prev_thePlayer{};
	theMinecraft = Minecraft::getTheMinecraft();
	if (!theMinecraft) return false;
	thePlayer = theMinecraft.getThePlayer();
	if (!thePlayer) return false;
	if (!(prev_thePlayer.operator==(thePlayer))) {
		std::clog << "object updated" << std::endl;
		prev_thePlayer = thePlayer;
		theWorld = theMinecraft.getTheWorld();
	}
	return true;
}
