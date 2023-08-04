#pragma once
#include "../Object/Object.h"

class ClassLoader : public Object {
public:
	using Object::Object;
	bool defineClass(const jbyte* classBytes, jsize size);
};
