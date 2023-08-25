#include "Collection.h"

void Collection::clear()
{
	if (!instance) return;
	Ripterms::p_env->CallVoidMethod(instance, Ripterms::classcache->CollectionClass.methods["clear"]);
}

bool Collection::add(Object element)
{
	if (!instance) return false;
	return Ripterms::p_env->CallBooleanMethod(instance, Ripterms::classcache->CollectionClass.methods["add"], element.getInstance()) == JNI_TRUE;
}
