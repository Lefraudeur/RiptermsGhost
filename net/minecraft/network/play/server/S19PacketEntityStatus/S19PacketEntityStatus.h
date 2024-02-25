#pragma once
#include "../../../Packet/Packet.h"

class S19PacketEntityStatus : public Packet
{
public:
	using Packet::Packet;

	int getEntityId() const;
	jbyte getLogicOpcode() const;
private:
	inline static Ripterms::JavaClassV2 S19PacketEntityStatusClass{ "net/minecraft/network/play/server/S19PacketEntityStatus" };
};