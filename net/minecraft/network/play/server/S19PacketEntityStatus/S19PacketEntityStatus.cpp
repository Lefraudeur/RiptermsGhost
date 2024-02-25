#include "S19PacketEntityStatus.h"

int S19PacketEntityStatus::getEntityId() const
{
	if (!instance) return 0;
	return env->GetIntField(instance, S19PacketEntityStatusClass.getFieldID("entityId"));
}

jbyte S19PacketEntityStatus::getLogicOpcode() const
{
	if (!instance) return 0;
	return env->GetByteField(instance, S19PacketEntityStatusClass.getFieldID("logicOpcode"));
}
