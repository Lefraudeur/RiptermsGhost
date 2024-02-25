#include "ClientboundDamageEventPacket.h"

int ClientboundDamageEventPacket::getEntityId() const
{
	if (!instance) return 0;
	return env->GetIntField(instance, ClientboundDamageEventPacketClass.getFieldID("entityId"));
}