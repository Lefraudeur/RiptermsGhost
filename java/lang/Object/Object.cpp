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

void Object::operator=(Object& other_Object)
{
	if (this->instance) Ripterms::p_env->DeleteLocalRef(this->instance);
	if (other_Object.instance) this->instance = Ripterms::p_env->NewLocalRef(other_Object.instance);
	else this->instance = nullptr;
}

void Object::operator=(jobject instance)
{
	if (this->instance) Ripterms::p_env->DeleteLocalRef(this->instance);
	this->instance = instance;
}

Object::Object()
{
}

Object::~Object()
{
	if (instance) Ripterms::p_env->DeleteLocalRef(instance);
}

bool Object::init()
{
	return ObjectClass.fill("java/lang/Object");
}
