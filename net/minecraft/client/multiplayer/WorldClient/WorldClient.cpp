#include "WorldClient.h"
#include "../../../../java/util/List/List.h"

List WorldClient::getPlayerEntities()
{
	if (!instance) return List(nullptr, env);
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5)
		return List(env->GetObjectField(instance, WorldClientClass.getFieldID("players")), env);
	return World::getPlayerEntities();
}
