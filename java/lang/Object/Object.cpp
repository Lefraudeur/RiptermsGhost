#include "Object.h"

Object::Object(jobject instance)
{
	this->instance = instance;
}

Object::Object(Object& other_Object)
{
	if (other_Object.instance) this->instance = Ripterms::p_env->NewLocalRef(other_Object.instance);
	else this->instance = nullptr;
}

Object::~Object()
{
	if (instance) Ripterms::p_env->DeleteLocalRef(instance);
}

bool Object::init()
{
	return ObjectClass.fill("java/lang/Object");
}
