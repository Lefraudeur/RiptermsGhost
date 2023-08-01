#pragma once
#include "../../../../java/lang/Object/Object.h"

class Entity : Object {
public:
	using Object::Object;
	using Object::operator=;
	using Object::operator==;
	static bool init();
protected:
	inline static Ripterms::JavaClass EntityClass{};
};