#include "World.h"
#include "../../../../java/util/List/List.h"

bool World::init()
{
	WorldClass = new Ripterms::JavaClass("net/minecraft/world/World");
	Ripterms::classes.push_back(WorldClass);
	return WorldClass->isSuccess;
}

std::vector<EntityPlayer> World::getPlayerEntities()
{
	if (!instance) return {};
	List playerEntities(Ripterms::p_env->GetObjectField(instance, WorldClass->fields["playerEntities"]));
	return playerEntities.toVector<EntityPlayer>();
}
