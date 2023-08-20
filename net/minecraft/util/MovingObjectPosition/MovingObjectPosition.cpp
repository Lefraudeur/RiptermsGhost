#include "MovingObjectPosition.h"

MovingObjectType MovingObjectPosition::getType()
{
	if (!instance) return MovingObjectType();
	if (Ripterms::majorVersion == Ripterms::MAJOR_1_16_5)
		return MovingObjectType(Ripterms::p_env->CallObjectMethod(instance, Ripterms::classcache->MovingObjectPositionClass.methods["getType"]));
	return MovingObjectType(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->MovingObjectPositionClass.fields["typeOfHit"]));
}
