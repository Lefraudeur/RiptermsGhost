#include "EntityPlayer.h"

bool EntityPlayer::init()
{
	return EntityPlayerClass.fill("net/minecraft/entity/player/EntityPlayer");
}
