#pragma once
#include "../../../../java/lang/Object/Object.h"

class AxisAlignedBB : public Object
{
public:
	using Object::Object;

	float getMinX() const;
	float getMinY() const;
	float getMinZ() const;
	float getMaxX() const;
	float getMaxY() const;
	float getMaxZ() const;

	void setMinX(float value);
	void setMinY(float value);
	void setMinZ(float value);
	void setMaxX(float value);
	void setMaxY(float value);
	void setMaxZ(float value);

protected:
	inline static Ripterms::JavaClassV2 AxisAlignedBBClass{ "net/minecraft/util/AxisAlignedBB" };
};