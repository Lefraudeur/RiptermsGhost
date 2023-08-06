#include "World.h"
#include "../../../../java/util/List/List.h"

List World::getPlayerEntities()
{
	if (!instance) return {};
	return List(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->WorldClass.fields["playerEntities"]));
}
