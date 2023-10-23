#include "AxisAlignedBB.h"

float AxisAlignedBB::getMinX()
{
	if (!instance) return 0.0f;
	return (float)env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("minX"));
}

float AxisAlignedBB::getMinY()
{
	if (!instance) return 0.0f;
	return (float)env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("minY"));
}

float AxisAlignedBB::getMinZ()
{
	if (!instance) return 0.0f;
	return (float)env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("minZ"));
}

float AxisAlignedBB::getMaxX()
{
	if (!instance) return 0.0f;
	return (float)env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxX"));
}

float AxisAlignedBB::getMaxY()
{
	if (!instance) return 0.0f;
	return (float)env->GetDoubleField(instance, AxisAlignedBBClass.getFieldID("maxY"));
}

float AxisAlignedBB::getMaxZ()
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