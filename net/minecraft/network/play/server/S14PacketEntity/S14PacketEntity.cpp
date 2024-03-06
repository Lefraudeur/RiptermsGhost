#include "S14PacketEntity.h"

int S14PacketEntity::getEntityId() const
{
	if (!instance) return 0;
	return env->GetIntField(instance, S14PacketEntityClass.getFieldID("entityId"));
}

jbyte S14PacketEntity::getPosX() const
{
	if (!instance) return 0;
	return env->GetByteField(instance, S14PacketEntityClass.getFieldID("posX"));
}

jbyte S14PacketEntity::getPosY() const
{
	if (!instance) return 0;
	return env->GetByteField(instance, S14PacketEntityClass.getFieldID("posY"));
}

jbyte S14PacketEntity::getPosZ() const
{
	if (!instance) return 0;
	return env->GetByteField(instance, S14PacketEntityClass.getFieldID("posZ"));
}

jshort S14PacketEntity::getXa() const
{
	if (!instance) return 0;
	return env->GetShortField(instance, S14PacketEntityClass.getFieldID("posX"));
}

jshort S14PacketEntity::getYa() const
{
	if (!instance) return 0;
	return env->GetShortField(instance, S14PacketEntityClass.getFieldID("posY"));
}

jshort S14PacketEntity::getZa() const
{
	if (!instance) return 0;
	return env->GetShortField(instance, S14PacketEntityClass.getFieldID("posZ"));
}

jbyte S14PacketEntity::getYaw() const
{
	if (!instance) return 0;
	return env->GetByteField(instance, S14PacketEntityClass.getFieldID("yaw"));
}

jbyte S14PacketEntity::getPitch() const
{
	if (!instance) return 0;
	return env->GetByteField(instance, S14PacketEntityClass.getFieldID("pitch"));
}

bool S14PacketEntity::getOnGround() const
{
	if (!instance) return false;
	return env->GetBooleanField(instance, S14PacketEntityClass.getFieldID("onGround")) == JNI_TRUE;
}

bool S14PacketEntity::getHasRot() const
{
	if (!instance) return false;
	return env->GetBooleanField(instance, S14PacketEntityClass.getFieldID("hasRot")) == JNI_TRUE;
}

bool S14PacketEntity::getHasPos() const
{
	if (!instance) return false;
	return env->GetBooleanField(instance, S14PacketEntityClass.getFieldID("hasPos")) == JNI_TRUE;
}
