#include "WorldClient.h"
#include "../../../../java/util/List/List.h"

List WorldClient::getPlayerEntities()
{
	if (!instance) return {};
	if (Ripterms::majorVersion == Ripterms::Version::MAJOR_1_8_9) return World::getPlayerEntities();
	return List(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->WorldClientClass.fields["players"]));
}
