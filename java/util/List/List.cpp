#include "List.h"

List List::newObject()
{
	Object arrayListClass(Ripterms::p_env->FindClass("java/util/ArrayList"));
	jmethodID constructor = Ripterms::p_env->GetMethodID((jclass)arrayListClass.getInstance(), "<init>", "()V");
	return List(Ripterms::p_env->NewObject((jclass)arrayListClass.getInstance(), constructor));
}
