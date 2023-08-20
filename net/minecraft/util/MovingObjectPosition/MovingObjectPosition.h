#pragma once
#include "MovingObjectPosition.h"
#include "../../../../java/lang/Object/Object.h"
#include "MovingObjectType/MovingObjectType.h"

class MovingObjectPosition : public Object {
public:
	using Object::Object;
	MovingObjectType getType();
};