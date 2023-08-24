#include "String.h"

String::String(const std::string& str) : Object(Ripterms::p_env->NewStringUTF(str.c_str()))
{
}

String::String(const char* str) : Object(Ripterms::p_env->NewStringUTF(str))
{
}

int String::size() const
{
	if (!instance) return 0;
	return Ripterms::p_env->GetStringUTFLength((jstring)instance);
}

std::string String::toStdString() const
{
	if (!instance) return std::string();
	int sz = size();
	char* buff = new char[sz + 1];
	Ripterms::p_env->GetStringUTFRegion((jstring)instance, 0, sz, buff);
	buff[sz] = '\0';
	std::string str = buff;
	delete[] buff;
	return str;
}