#include "EntityPlayerSP.h"

bool EntityPlayerSP::init()
{
	return EntityPlayerSPClass.fill("net/minecraft/client/entity/EntityPlayerSP");
}
