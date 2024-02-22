#include "List.h"

List List::newObject(JNIEnv* env)
{
	jclass arrayListClass = env->FindClass("java/util/ArrayList");
	jmethodID constructor = env->GetMethodID(arrayListClass, "<init>", "()V");
	return List(env->NewObject(arrayListClass, constructor), env);
}
