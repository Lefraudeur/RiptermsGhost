#pragma once
#include "../../../../../java/lang/Object/Object.h"
#include "../../../network/Packet/Packet.h"

class NetHandlerPlayClient : public Object
{
public:
	using Object::Object;
	void addToSendQueue(const Packet& packet);
protected:
	inline static Ripterms::JavaClassV2 NetHandlerPlayClientClass{ "net/minecraft/client/network/NetHandlerPlayClient" };
};