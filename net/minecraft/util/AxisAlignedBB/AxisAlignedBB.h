#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../../../Ripterms/Maths/Maths.h"

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

	double getXWidth();
	double getZWidth();
	double getHeight();
	Ripterms::Maths::Vector3d getCenter();
protected:
	inline static Ripterms::JavaClassV2 AxisAlignedBBClass{ "net/minecraft/util/AxisAlignedBB" };
};