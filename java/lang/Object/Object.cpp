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

Object::Object(JNIEnv* env)
{
	this->env = env;
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
	setInstance(instance);
	return *this;
}

Object::operator jobject()
{
	return getInstance();
}

void Object::setInstance(jobject instance, JNIEnv* env)
{
	if (this->instance) this->env->DeleteGlobalRef(this->instance);

	if (!this->env) this->env = Ripterms::p_env;
	if (env) this->env = env;

	if (instance)
	{
		this->instance = this->env->NewGlobalRef(instance);
		if (this->env->GetObjectRefType(instance) == JNILocalRefType)
			this->env->DeleteLocalRef(instance);
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

bool Object::instanceOf(const Ripterms::JavaClassV2::JClass& classRef)
{
	if (!isValid() || !classRef.isValid())
		return false;
	return env->IsInstanceOf(instance, classRef.getInstance()) == JNI_TRUE;
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
