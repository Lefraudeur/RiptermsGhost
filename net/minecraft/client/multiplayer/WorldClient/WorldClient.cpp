#include "WorldClient.h"
#include "../../../../java/util/List/List.h"

std::vector<EntityPlayer> WorldClient::getPlayerEntities()
{
	if (!instance) return {};
	if (Ripterms::majorVersion == Ripterms::Version::MAJOR_1_8_9 || Ripterms::version == Ripterms::Version::MAJOR_1_7_10) return World::getPlayerEntities();
	List playerEntities(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->WorldClientClass.fields["players"]));
	return playerEntities.toVector<EntityPlayer>();
}
