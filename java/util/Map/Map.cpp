#include "Map.h"

Object Map::put(const Object& key, const Object& value)
{
	if (!instance) return Object();
	return Object(env->CallObjectMethod(instance, MapClass.getMethodID("put"), key.getInstance(), value.getInstance()), env);
}
