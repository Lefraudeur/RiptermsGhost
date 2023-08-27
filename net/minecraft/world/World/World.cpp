#include "World.h"
#include "../../../../java/util/List/List.h"

List World::getPlayerEntities()
{
	if (!instance) return {};
	return List(env->GetObjectField(instance, WorldClass.getFieldID("playerEntities")), env);
}
