#include "Block.h"

String Block::toString()
{
	if (!instance) return String(env);
	return String(env->CallObjectMethod(instance, ObjectClass.getMethodID("toString")), env);
}
