#include "AbstractClientPlayer.h"

bool AbstractClientPlayer::init()
{
	AbstractClientPlayerClass = new Ripterms::JavaClass("net/minecraft/client/entity/AbstractClientPlayer");
	Ripterms::classes.push_back(AbstractClientPlayerClass);
	return AbstractClientPlayerClass->isSuccess;
}
