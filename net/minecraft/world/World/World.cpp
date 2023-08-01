#include "World.h"
#include "../../../../java/util/List/List.h"

bool World::init()
{
	return WorldClass.fill("net/minecraft/world/World");
}

std::vector<EntityPlayer> World::getPlayerEntities()
{
	if (!instance) return {};
	List playerEntities(Ripterms::p_env->GetObjectField(instance, WorldClass.fields["playerEntities"]));
	return playerEntities.toArray<EntityPlayer>();
}
