#pragma once
#include "../Object/Object.h"

class ClassLoader : public Object {
public:
	using Object::Object;
	bool loadJar(const unsigned char* jarBytes, size_t size);
	bool defineClass(const jbyte* classBytes, jsize size);
	static ClassLoader newObject(JNIEnv* env = Ripterms::p_env);
};
