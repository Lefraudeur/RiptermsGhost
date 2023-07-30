#include "Object.h"

Object::Object(jobject instance)
{
	this->instance = instance;
	static bool runonce = true;
	if (runonce) {
		javaClass.fill("java/lang/Object");
		runonce = false;
	}
}

Object::Object(Object& other_Object)
{
	if (other_Object.instance) this->instance = Ripterms::p_env->NewLocalRef(other_Object.instance);
}

Object::~Object()
{
	if (instance) Ripterms::p_env->DeleteLocalRef(instance);
}
