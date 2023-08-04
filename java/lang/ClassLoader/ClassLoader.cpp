#include "ClassLoader.h"

bool ClassLoader::defineClass(const jbyte* classBytes, jsize size)
{
	jclass jaclass = Ripterms::p_env->DefineClass(nullptr, instance, classBytes, size);
	if (!jaclass) return false;
	Ripterms::p_env->DeleteLocalRef(jaclass);
	return true;
}
