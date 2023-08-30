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
