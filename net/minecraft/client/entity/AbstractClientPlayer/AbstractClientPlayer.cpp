#include "AbstractClientPlayer.h"

bool AbstractClientPlayer::init()
{
	return AbstractClientPlayerClass.fill("net/minecraft/client/entity/AbstractClientPlayer");
}
