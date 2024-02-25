#include "Object.h"
#include "../String/String.h"

Object::Object(jobject instance, JNIEnv* env, bool is_global)
{
	this->env = env;
	this->is_global = is_global;
	if (instance)
	{
		this->instance = (is_global ? env->NewGlobalRef(instance) : instance);
	}
	else this->instance = nullptr;
}

Object::Object(const Object& other_Object)
{
	this->env = other_Object.env;
	this->is_global = other_Object.is_global;
	if (other_Object.instance)
	{
		this->instance = (is_global ? env->NewGlobalRef(other_Object.instance) : other_Object.instance);
	}
	else this->instance = nullptr;
}

Object::Object(JNIEnv* env, bool is_global)
{
	this->is_global = is_global;
	this->env = env;
}

Object& Object::operator=(const Object& other_Object)
{
	this->env = other_Object.env;
	if (this->instance && is_global)
	{
		env->DeleteGlobalRef(this->instance);
	}
	if (other_Object.instance)
		this->instance = (is_global ? env->NewGlobalRef(other_Object.instance) : other_Object.instance);
	else this->instance = nullptr;
	return *this;
}

Object& Object::operator=(jobject instance)
{
	setInstance(instance, nullptr);
	return *this;
}

Object::operator jobject()
{
	return getInstance();
}

void Object::setInstance(jobject instance, JNIEnv* env)
{
	if (this->instance && is_global)
	{
		env->DeleteGlobalRef(this->instance);
	}

	if (!this->env) this->env = Ripterms::p_env;
	if (env) this->env = env;

	if (instance)
	{
		this->instance = (is_global ? env->NewGlobalRef(instance) : instance);
	}
	else this->instance = nullptr;
}

bool Object::isEqualTo(const Object& other_Object)
{
	if (this->instance == other_Object.instance)
	{
		return true;
	}
	if (this->instance && other_Object.instance)
	{
		return env->IsSameObject(this->instance, other_Object.instance) == JNI_TRUE;
	}
	return false;
}

bool Object::instanceOf(jclass classRef)
{
	if (!isValid() || !classRef)
		return false;
	return env->IsInstanceOf(instance, classRef) == JNI_TRUE;
}

bool Object::equals(const Object& other_Object)
{
	if (this->instance == other_Object.instance)
	{
		return true;
	}
	if (this->instance && other_Object.instance)
	{
		return env->CallBooleanMethod(instance, ObjectClass.getMethodID("equals"), other_Object.getInstance()) == JNI_TRUE;
	}
	return false;
}

bool Object::isValid()
{
	return this->instance != nullptr;
}

Object::~Object()
{
	if (is_global)
		clear();
}

void Object::clear()
{
	if (!Ripterms::p_env) 
		return; // process termination scenario
	if (isValid())
	{
		if (is_global)
			env->DeleteGlobalRef(instance);
		else
			env->DeleteLocalRef(instance);
		this->instance = nullptr;
	}
}

const jobject& Object::getInstance() const
{
	return instance;
}

Object& Object::makeGlobal()
{
	if (this->is_global) return *this;
	this->is_global = true;
	if (!this->instance) return *this;
	this->instance = env->NewGlobalRef(this->instance);
	return *this;
}

void Object::set_env(JNIEnv* env)
{
	this->env = env;
	return;
}
