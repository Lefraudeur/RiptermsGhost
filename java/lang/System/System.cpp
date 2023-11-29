#include "System.h"

void System::gc(JNIEnv* env)
{
	env->CallStaticVoidMethod(SystemClass.getJClass(env), SystemClass.getMethodID("gc"));
}