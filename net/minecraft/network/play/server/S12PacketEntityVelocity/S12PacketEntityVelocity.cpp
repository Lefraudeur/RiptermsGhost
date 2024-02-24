#include "S12PacketEntityVelocity.h"

int S12PacketEntityVelocity::getEntityID() const
{
	if (!instance) return 0;
	return env->GetIntField(instance, S12PacketEntityVelocityClass.getFieldID("entityID"));
}

int S12PacketEntityVelocity::getMotionX() const
{
	if (!instance) return 0;
	return env->GetIntField(instance, S12PacketEntityVelocityClass.getFieldID("motionX"));
}

int S12PacketEntityVelocity::getMotionY() const
{
	if (!instance) return 0;
	return env->GetIntField(instance, S12PacketEntityVelocityClass.getFieldID("motionY"));
}

int S12PacketEntityVelocity::getMotionZ() const
{
	if (!instance) return 0;
	return env->GetIntField(instance, S12PacketEntityVelocityClass.getFieldID("motionZ"));
}

void S12PacketEntityVelocity::setEntityID(int value)
{
	if (!instance) return;
	env->SetIntField(instance, S12PacketEntityVelocityClass.getFieldID("entityID"), (jint)value);
}

void S12PacketEntityVelocity::setMotionX(int value)
{
	if (!instance) return;
	env->SetIntField(instance, S12PacketEntityVelocityClass.getFieldID("motionX"), (jint)value);
}

void S12PacketEntityVelocity::setMotionY(int value)
{
	if (!instance) return;
	env->SetIntField(instance, S12PacketEntityVelocityClass.getFieldID("motionY"), (jint)value);
}

void S12PacketEntityVelocity::setMotionZ(int value)
{
	if (!instance) return;
	env->SetIntField(instance, S12PacketEntityVelocityClass.getFieldID("motionZ"), (jint)value);
}
