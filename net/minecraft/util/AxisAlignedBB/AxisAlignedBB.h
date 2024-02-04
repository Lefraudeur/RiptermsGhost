#pragma once
#include "../../../../java/lang/Object/Object.h"

class AxisAlignedBB : public Object
{
public:
	using Object::Object;

	double getMinX() const;
	double getMinY() const;
	double getMinZ() const;
	double getMaxX() const;
	double getMaxY() const;
	double getMaxZ() const;

	void setMinX(double value);
	void setMinY(double value);
	void setMinZ(double value);
	void setMaxX(double value);
	void setMaxY(double value);
	void setMaxZ(double value);

protected:
	inline static Ripterms::JavaClassV2 AxisAlignedBBClass{ "net/minecraft/util/AxisAlignedBB" };
};