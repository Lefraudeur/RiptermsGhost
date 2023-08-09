#include "Object.h"

Object::Object(jobject instance)
{
	if (instance) {
		this->instance = Ripterms::p_env->NewGlobalRef(instance);
		Ripterms::p_env->DeleteLocalRef(instance);
	}
	else this->instance = nullptr;
}

Object::Object(const Object& other_Object)
{
	if (other_Object.instance) this->instance = Ripterms::p_env->NewGlobalRef(other_Object.instance);
	else this->instance = nullptr;
}

Object::Object()
{
}

Object& Object::operator=(const Object& other_Object)
{
	if (this->instance) Ripterms::p_env->DeleteGlobalRef(this->instance);
	if (other_Object.instance) this->instance = Ripterms::p_env->NewGlobalRef(other_Object.instance);
	else this->instance = nullptr;
	return *this;
}

Object& Object::operator=(jobject instance)
{
	if (this->instance) Ripterms::p_env->DeleteGlobalRef(this->instance);
	if (instance) {
		this->instance = Ripterms::p_env->NewGlobalRef(instance);
		Ripterms::p_env->DeleteLocalRef(instance);
	}
	else this->instance = nullptr;
	return *this;
}

bool Object::isEqualTo(const Object& other_Object)
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
	return this->instance == nullptr;
}

bool Object::isValid()
{
	return this->instance != nullptr;
}

Object::~Object()
{
	if (!Ripterms::p_env) return;
	if (instance) Ripterms::p_env->DeleteGlobalRef(instance);
}

void Object::clear()
{
	if (!Ripterms::p_env) return;
	if (this->instance) {
		Ripterms::p_env->DeleteGlobalRef(this->instance);
		this->instance = nullptr;
	}
}

jobject Object::getInstance()
{
	return instance;
}
