#include "Object.h"

Object::Object(jobject instance)
{
	this->instance = instance;
}

Object::Object(const Object& other_Object)
{
	if (other_Object.instance) this->instance = Ripterms::p_env->NewLocalRef(other_Object.instance);
	else this->instance = nullptr;
}

Object::Object()
{
}

Object& Object::operator=(const Object& other_Object)
{
	if (this->instance) Ripterms::p_env->DeleteLocalRef(this->instance);
	if (other_Object.instance) this->instance = Ripterms::p_env->NewLocalRef(other_Object.instance);
	else this->instance = nullptr;
	return *this;
}

Object& Object::operator=(jobject instance)
{
	if (this->instance) Ripterms::p_env->DeleteLocalRef(this->instance);
	this->instance = instance;
	return *this;
}

bool Object::operator==(const Object& other_Object)
{
	if (this->instance == other_Object.instance) {
		return true;
	}
	else if (this->instance && other_Object.instance) {
		return Ripterms::p_env->IsSameObject(this->instance, other_Object.instance) == JNI_TRUE;
	}
	return false;
}

bool Object::operator!()
{
	return !this->instance;
}

Object::~Object()
{
	if (instance) Ripterms::p_env->DeleteLocalRef(instance);
}

bool Object::init()
{
	return ObjectClass.fill("java/lang/Object");
}
