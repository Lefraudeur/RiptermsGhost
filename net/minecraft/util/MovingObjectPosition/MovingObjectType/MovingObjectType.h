#pragma once
#include "../../../../java/lang/Object/Object.h"

class MovingObjectType : public Object {
public:
	using Object::Object;
	static MovingObjectType getType(const std::string& name);
};
