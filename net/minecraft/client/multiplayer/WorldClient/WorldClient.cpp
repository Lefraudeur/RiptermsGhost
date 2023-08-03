#include "WorldClient.h"

bool WorldClient::init()
{
	WorldClientClass = new Ripterms::JavaClass("net/minecraft/client/multiplayer/WorldClient");
	Ripterms::classes.push_back(WorldClientClass);
	return WorldClientClass->isSuccess;
}
