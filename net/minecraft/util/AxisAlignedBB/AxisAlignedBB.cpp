#include "AxisAlignedBB.h"

double AxisAlignedBB::getMinX() const
{
	if (!instance) return 0.0;
	return env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("minX"));
}

double AxisAlignedBB::getMinY() const
{
	if (!instance) return 0.0;
	return env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("minY"));
}

double AxisAlignedBB::getMinZ() const
{
	if (!instance) return 0.0;
	return env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("minZ"));
}

double AxisAlignedBB::getMaxX() const
{
	if (!instance) return 0.0;
	return env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxX"));
}

double AxisAlignedBB::getMaxY() const
{
	if (!instance) return 0.0;
	return env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxY"));
}

double AxisAlignedBB::getMaxZ() const
{
	if (!instance) return 0.0;
	return env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxZ"));
}


void AxisAlignedBB::setMinX(double  value)
{
	if (!instance) return;
	env->SetDoubleField(instance, AxisAlignedBBClass.getFieldID("minX"), (jdouble)value);
}
void AxisAlignedBB::setMinY(double  value)
{
	if (!instance) return;
	env->SetDoubleField(instance, AxisAlignedBBClass.getFieldID("minY"), (jdouble)value);
}
void AxisAlignedBB::setMinZ(double  value)
{
	if (!instance) return;
	env->SetDoubleField(instance, AxisAlignedBBClass.getFieldID("minZ"), (jdouble)value);
}


void AxisAlignedBB::setMaxX(double  value)
{
	if (!instance) return;
	env->SetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxX"), (jdouble)value);
}
void AxisAlignedBB::setMaxY(double  value)
{
	if (!instance) return;
	env->SetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxY"), (jdouble)value);
}
void AxisAlignedBB::setMaxZ(double  value)
{
	if (!instance) return;
	env->SetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxZ"), (jdouble)value);
}

double AxisAlignedBB::getXWidth()
{
	return getMaxX() - getMinX();
}

double AxisAlignedBB::getZWidth()
{
	return getMaxZ() - getMinZ();
}

double AxisAlignedBB::getHeight()
{
	return getMaxY() - getMinY();
}

Ripterms::Maths::Vector3d AxisAlignedBB::getCenter()
{
	double halfXWidth = getXWidth() / 2.0;
	double halfZWidth = getZWidth() / 2.0;
	double halfHeight = getHeight() / 2.0;
	return Ripterms::Maths::Vector3d(getMinX() + halfXWidth, getMinY() + halfHeight, getMinZ() + halfZWidth);
}
