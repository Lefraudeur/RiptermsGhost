#include "NetHandlerPlayClient.h"

void NetHandlerPlayClient::addToSendQueue(const Packet& packet)
{
	if (!instance)
		return;
	env->CallVoidMethod(instance, NetHandlerPlayClientClass.getMethodID("addToSendQueue"), packet.getInstance());
}