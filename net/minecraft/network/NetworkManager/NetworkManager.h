#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../../../io/netty/ChannelHandlerContext/ChannelHandlerContext.h"
#include "../Packet/Packet.h"

class NetworkManager : public Object
{
public:
	using Object::Object;

	void channelRead0(ChannelHandlerContext& context, Packet& packet);
protected:
	inline static Ripterms::JavaClassV2 NetworkManagerClass{ "net/minecraft/network/NetworkManager" };
};