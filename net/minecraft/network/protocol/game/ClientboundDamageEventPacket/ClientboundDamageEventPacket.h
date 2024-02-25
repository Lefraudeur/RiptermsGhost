#pragma once
#include "../../../Packet/Packet.h"

class ClientboundDamageEventPacket : public Packet //1.19+ only
{
public:
	using Packet::Packet;

	int getEntityId() const;
protected:
	inline static Ripterms::JavaClassV2 ClientboundDamageEventPacketClass{ "net/minecraft/network/protocol/game/ClientboundDamageEventPacket" };
};