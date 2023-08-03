#include "EntityPlayerSP.h"

bool EntityPlayerSP::init()
{
	EntityPlayerSPClass = new Ripterms::JavaClass("net/minecraft/client/entity/EntityPlayerSP");
	Ripterms::classes.push_back(EntityPlayerSPClass);
	return EntityPlayerSPClass->isSuccess;
}
