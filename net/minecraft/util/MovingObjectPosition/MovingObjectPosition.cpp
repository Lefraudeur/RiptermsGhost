#include "MovingObjectPosition.h"

MovingObjectType MovingObjectPosition::getType()
{
	if (!instance) return MovingObjectType(nullptr ,env);
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5 || Ripterms::version.type == Ripterms::Version::MAJOR_1_19_4)
		return MovingObjectType(env->CallObjectMethod(instance, MovingObjectPositionClass.getMethodID("getType")), env);
	return MovingObjectType(env->GetObjectField(instance, MovingObjectPositionClass.getFieldID("typeOfHit")), env);
}
