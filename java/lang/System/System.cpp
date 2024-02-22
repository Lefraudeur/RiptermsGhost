#include "System.h"

void System::gc(JNIEnv* env)
{
	env->CallStaticVoidMethod(SystemClass.get_jclass(env), SystemClass.getMethodID("gc"));
}