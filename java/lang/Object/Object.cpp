#include "Object.h"

Object::Object(jobject instance)
{
	this->instance = instance;
}

Object::Object(Object& other_Object)
{
	this->instance = Ripterms::p_env->NewLocalRef(other_Object.instance);
}

Object::~Object()
{
	Ripterms::p_env->DeleteLocalRef(instance);
}
