#include "String.h"

String::String(const std::string& str) : Object(Ripterms::p_env->NewStringUTF(str.c_str()))
{
}

String::String(const char* str) : Object(Ripterms::p_env->NewStringUTF(str))
{
}

int String::size()
{
	if (!instance) return 0;
	return Ripterms::p_env->GetStringUTFLength((jstring)instance);
}

std::string String::toString()
{
	if (!instance) return std::string();
	int sz = size();
	char* buff = new char[sz];
	Ripterms::p_env->GetStringUTFRegion((jstring)instance, 0, sz, buff);
	std::string str(buff, sz);
	delete[] buff;
	return str;
}