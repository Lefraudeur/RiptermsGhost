#include "Collection.h"

void Collection::clear()
{
	if (!instance) return;
	Ripterms::p_env->CallVoidMethod(instance, Ripterms::classcache->CollectionClass.methods["clear"]);
}
