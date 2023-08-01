#include "WorldClient.h"

bool WorldClient::init()
{
	return WorldClientClass.fill("net/minecraft/client/multiplayer/WorldClient");
}
