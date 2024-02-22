#include "Double.h"

Double Double::newObject(double value, JNIEnv* env)
{
	if (!env) return Double(nullptr, env);
	return Double(env->NewObject(DoubleClass.get_jclass(env), DoubleClass.getMethodID("<init>"), (jdouble)value), env);
}

double Double::doubleValue()
{
	if (!instance) return 0.0;
	return (double)env->CallDoubleMethod(instance, DoubleClass.getMethodID("doubleValue"));
}
