#include "String.h"

String::String(const std::string& str, JNIEnv* env) : Object(env->NewStringUTF(str.c_str()), env)
{
}

String::String(const char* str, JNIEnv* env) : Object(env->NewStringUTF(str), env)
{
}

int String::size() const
{
	if (!instance) return 0;
	return env->GetStringUTFLength((jstring)instance);
}

std::string String::toStdString() const
{
	if (!instance) return std::string();
	int sz = size();
	char* buff = new char[sz + 1];
	env->GetStringUTFRegion((jstring)instance, 0, sz, buff);
	buff[sz] = '\0';
	std::string str = buff;
	delete[] buff;
	return str;
}