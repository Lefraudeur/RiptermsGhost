#pragma once
#include "../../../Packet/Packet.h"

class S14PacketEntity : public Packet
{
public:
	using Packet::Packet;

	int getEntityId() const;
	jbyte getPosX() const;
	jbyte getPosY() const;
	jbyte getPosZ() const;
	jbyte getYaw() const;
	jbyte getPitch() const;
	bool getOnGround() const;
	bool getHasRot() const;
protected:
	inline static Ripterms::JavaClassV2 S14PacketEntityClass{ "net/minecraft/network/play/server/S14PacketEntity" };
};