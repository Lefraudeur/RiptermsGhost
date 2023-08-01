#pragma once
#include "../../../../java/lang/Object/Object.h"

class Entity : public Object {
public:
	using Object::Object;
	static bool init();
protected:
	inline static Ripterms::JavaClass EntityClass{};
};