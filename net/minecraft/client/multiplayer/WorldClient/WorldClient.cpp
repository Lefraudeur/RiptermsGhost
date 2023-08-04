#include "WorldClient.h"
#include "../../../../java/util/List/List.h"

std::vector<EntityPlayer> WorldClient::getPlayerEntities()
{
	if (!instance) return {};
	if (Ripterms::version == Ripterms::Version::LUNAR_1_8_9) return World::getPlayerEntities();
	List playerEntities(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->WorldClientClass.fields["players"]));
	return playerEntities.toVector<EntityPlayer>();
}
