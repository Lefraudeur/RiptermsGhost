#include "List.h"

List List::newObject(JNIEnv* env)
{
	Ripterms::JavaClassV2::JClass arrayListClass(env->FindClass("java/util/ArrayList"), env);
	jmethodID constructor = env->GetMethodID(arrayListClass, "<init>", "()V");
	return List(env->NewObject(arrayListClass, constructor), env);
}
