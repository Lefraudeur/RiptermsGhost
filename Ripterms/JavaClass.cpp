#include "Ripterms.h"

Ripterms::JavaClass::JavaClass(const std::string& class_path)
{
	fill(class_path);
}

Ripterms::JavaClass::JavaClass()
{
}

Ripterms::JavaClass::JavaClass(JavaClass& otherJavaClass)
{
	if (otherJavaClass.javaClass) this->javaClass = (jclass)p_env->NewLocalRef(otherJavaClass.javaClass);
	else this->javaClass = nullptr;
	this->fields = otherJavaClass.fields;
	this->methods = otherJavaClass.methods;
}

Ripterms::JavaClass::~JavaClass()
{
	if (javaClass) p_env->DeleteLocalRef(javaClass);
}

void Ripterms::JavaClass::fill(const std::string& class_path)
{
}