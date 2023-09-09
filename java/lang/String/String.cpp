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
	return env->GetStringLength((jstring)instance);
}

int String::modifiedUTF8size() const
{
	if (!instance) return 0;
	return env->GetStringUTFLength((jstring)instance);
}

std::string String::toStdString() const
{
	int bufferSize = this->modifiedUTF8size();
	char* buffer = new char[bufferSize + 1] { 0 };
	env->GetStringUTFRegion((jstring)instance, 0, size(), buffer);
	buffer[bufferSize] = '\0';
	std::string str = buffer;
	delete[] buffer;
	return str;
}
