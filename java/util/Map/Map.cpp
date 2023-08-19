#include "Map.h"

Object Map::put(const Object& key, const Object& value)
{
	if (!instance) return Object();
	return Object(Ripterms::p_env->CallObjectMethod(instance, Ripterms::classcache->MapClass.methods["put"], key.getInstance(), value.getInstance()));
}
