#pragma once
#include "../../../Packet/Packet.h"

class S12PacketEntityVelocity : public Packet
{
public:
	using Packet::Packet;

	int getEntityID() const;
	int getMotionX() const;
	int getMotionY() const;
	int getMotionZ() const;

	void setEntityID(int value);
	void setMotionX(int value);
	void setMotionY(int value);
	void setMotionZ(int value);
private:
	inline static Ripterms::JavaClassV2 S12PacketEntityVelocityClass{ "net/minecraft/network/play/server/S12PacketEntityVelocity" };
};