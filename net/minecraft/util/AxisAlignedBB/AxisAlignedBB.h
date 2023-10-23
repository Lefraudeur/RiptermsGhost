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

	void setMinX(float value);
	void setMinY(float value);
	void setMinZ(float value);
	void setMaxX(float value);
	void setMaxY(float value);
	void setMaxZ(float value);

protected:
	inline static Ripterms::JavaClassV2 AxisAlignedBBClass{ "net/minecraft/util/AxisAlignedBB" };
};