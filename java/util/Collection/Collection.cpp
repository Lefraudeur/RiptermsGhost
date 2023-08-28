#include "Collection.h"

void Collection::clear()
{
	if (!instance) return;
	env->CallVoidMethod(instance, CollectionClass.getMethodID("clear"));
}

bool Collection::add(const Object& element)
{
	if (!instance) return false;
	return env->CallBooleanMethod(instance, CollectionClass.getMethodID("add"), element.getInstance()) == JNI_TRUE;
}
