#pragma once
#include "../../../../java/lang/Object/Object.h"

class World : public Object {
public:
	using Object::Object;
	static bool init();
protected:
	inline static Ripterms::JavaClass WorldClass{};
};