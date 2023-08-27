#include "Object.h"

Object::Object(jobject instance, JNIEnv* env)
{
	if (instance)
	{
		this->instance = env->NewGlobalRef(instance);
		if (env->GetObjectRefType(instance) == JNILocalRefType)
			env->DeleteLocalRef(instance);
	}
	else this->instance = nullptr;
	this->env = env;
}

Object::Object(const Object& other_Object) :
	Object(other_Object.instance, other_Object.env)
{
}

Object::Object()
{
}

Object& Object::operator=(const Object& other_Object)
{
	this->env = other_Object.env;
	if (this->instance) env->DeleteGlobalRef(this->instance);
	if (other_Object.instance)
		this->instance = env->NewGlobalRef(other_Object.instance);
	else this->instance = nullptr;
	return *this;
}

Object& Object::operator=(jobject instance)
{
	if (!this->env) env = Ripterms::p_env;
	if (this->instance) env->DeleteGlobalRef(this->instance);
	if (instance)
		this->instance = env->NewGlobalRef(instance);
	else this->instance = nullptr;
	return *this;
}

Object::operator jobject()
{
	return getInstance();
}

bool Object::isEqualTo(const Object& other_Object)
{
	if (this->instance == other_Object.instance) {
		return true;
	}
	if (this->instance && other_Object.instance) {
		return env->IsSameObject(this->instance, other_Object.instance) == JNI_TRUE;
	}
	return false;
}

bool Object::isValid()
{
	return this->instance != nullptr;
}

Object::~Object()
{
	clear();
}

void Object::clear()
{
	if (!Ripterms::p_env) 
		return; // process termination scenario
	if (isValid())
	{
		env->DeleteGlobalRef(this->instance);
		this->instance = nullptr;
	}
}

const jobject& Object::getInstance() const
{
	return instance;
}
