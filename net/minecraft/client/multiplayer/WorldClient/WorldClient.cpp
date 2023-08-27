#include "WorldClient.h"
#include "../../../../java/util/List/List.h"

List WorldClient::getPlayerEntities()
{
	if (!instance) return {};
	if (Ripterms::majorVersion == Ripterms::Version::MAJOR_1_8_9) return World::getPlayerEntities();
	return List(env->GetObjectField(instance, WorldClientClass.getFieldID("players")), env);
}
