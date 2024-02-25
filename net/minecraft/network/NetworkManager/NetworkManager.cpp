#include "NetworkManager.h"

void NetworkManager::channelRead0(ChannelHandlerContext& context, Packet& packet)
{
	if (!instance) return;
	env->CallVoidMethod(instance, NetworkManagerClass.getMethodID("channelRead0"), context.getInstance(), packet.getInstance());
}
