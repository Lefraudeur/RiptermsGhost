#pragma once
#include "../../../Packet/Packet.h"

class S14PacketEntity : public Packet
{
public:
	using Packet::Packet;

	int getEntityId() const;

	//jbyte used for pos in version < 1.16.5
	jbyte getPosX() const;
	jbyte getPosY() const;
	jbyte getPosZ() const;

	//jshort for pos in 1.16.5+
	jshort getXa() const;
	jshort getYa() const;
	jshort getZa() const;

	jbyte getYaw() const;
	jbyte getPitch() const;
	bool getOnGround() const; //1.8.9+ only

	bool getHasRot() const;

	bool getHasPos() const; //1.16.5+ only
protected:
	inline static Ripterms::JavaClassV2 S14PacketEntityClass{ "net/minecraft/network/play/server/S14PacketEntity" };
};