#pragma once
#include "../Object/Object.h"

class System : public Object {
public:
	using Object::Object;
	static void gc();
};
