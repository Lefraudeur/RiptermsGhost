#pragma once
#include "../../../../java/lang/Object/Object.h"

class AxisAlignedBB : public Object
{
public:
	using Object::Object;

	float getMinX();
	float getMinY();
	float getMinZ();
	float getMaxX();
	float getMaxY();
	float getMaxZ();

protected:
	inline static Ripterms::JavaClassV2 AxisAlignedBBClass{ "net/minecraft/util/AxisAlignedBB" };
};