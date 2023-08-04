#include "World.h"
#include "../../../../java/util/List/List.h"

std::vector<EntityPlayer> World::getPlayerEntities()
{
	if (!instance) return {};
	List playerEntities(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->WorldClass.fields["playerEntities"]));
	return playerEntities.toVector<EntityPlayer>();
}
