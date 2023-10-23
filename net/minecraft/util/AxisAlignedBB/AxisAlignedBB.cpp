#include "AxisAlignedBB.h"

float AxisAlignedBB::getMinX() const
{
	if (!instance) return 0.0f;
	return (float)env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("minX"));
}

float AxisAlignedBB::getMinY() const
{
	if (!instance) return 0.0f;
	return (float)env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("minY"));
}

float AxisAlignedBB::getMinZ() const
{
	if (!instance) return 0.0f;
	return (float)env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("minZ"));
}

float AxisAlignedBB::getMaxX() const
{
	if (!instance) return 0.0f;
	return (float)env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxX"));
}

float AxisAlignedBB::getMaxY() const
{
	if (!instance) return 0.0f;
	return (float)env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxY"));
}

float AxisAlignedBB::getMaxZ() const
{
	if (!instance) return 0.0f;
	return (float)env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxZ"));
}


void AxisAlignedBB::setMinX(float  value)
{
	if (!instance) return;
	env->SetDoubleField(instance, AxisAlignedBBClass.getFieldID("minX"), (jdouble)value);
}
void AxisAlignedBB::setMinY(float  value)
{
	if (!instance) return;
	env->SetDoubleField(instance, AxisAlignedBBClass.getFieldID("minY"), (jdouble)value);
}
void AxisAlignedBB::setMinZ(float  value)
{
	if (!instance) return;
	env->SetDoubleField(instance, AxisAlignedBBClass.getFieldID("minZ"), (jdouble)value);
}


void AxisAlignedBB::setMaxX(float  value)
{
	if (!instance) return;
	env->SetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxX"), (jdouble)value);
}
void AxisAlignedBB::setMaxY(float  value)
{
	if (!instance) return;
	env->SetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxY"), (jdouble)value);
}
void AxisAlignedBB::setMaxZ(float  value)
{
	if (!instance) return;
	env->SetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxZ"), (jdouble)value);
}