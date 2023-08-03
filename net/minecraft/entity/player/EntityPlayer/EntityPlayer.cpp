#include "EntityPlayer.h"

bool EntityPlayer::init()
{
	EntityPlayerClass = new Ripterms::JavaClass("net/minecraft/entity/player/EntityPlayer");
	Ripterms::classes.push_back(EntityPlayerClass);
	return EntityPlayerClass->isSuccess;
}
