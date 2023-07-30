#include "Ripterms.h"

Ripterms::JavaClass::JavaClass(const std::string& class_path)
{
	this->javaClass = javaClass;
	this->fields = fields;
	this->methods = methods;
}

Ripterms::JavaClass::JavaClass(JavaClass& otherJavaClass)
{
	this->javaClass = (jclass)p_env->NewLocalRef(otherJavaClass.javaClass);
}

Ripterms::JavaClass::~JavaClass()
{
	p_env->DeleteLocalRef(javaClass);
}
