#include "Entity.h"

bool Entity::init()
{
	return EntityClass.fill("net/minecraft/entity/Entity");
}
