#pragma once
#include "../../../Packet/Packet.h"
#include "../../../../../../Ripterms/Maths/Maths.h"
class C03PacketPlayer : public Packet
{
public:
	using Packet::Packet;
	static C03PacketPlayer newObject(bool isOnGround, JNIEnv* env = Ripterms::p_env); //not valid on 1.19.4

	Ripterms::Maths::Vector3d getXYZ();
	void setXYZ(const Ripterms::Maths::Vector3d& vector);

	Ripterms::Maths::Vector2d getYawPitch();
	void setYawPitch(Ripterms::Maths::Vector2d yawPitch);

	bool getOnGround();
	void setOnGround(bool state);

	bool getMoving();
	void setMoving(bool state);

	bool getRotating();
	void setRotating(bool state);
protected:
	inline static Ripterms::JavaClassV2 C03PacketPlayerClass{ "net/minecraft/network/play/client/C03PacketPlayer" };
};