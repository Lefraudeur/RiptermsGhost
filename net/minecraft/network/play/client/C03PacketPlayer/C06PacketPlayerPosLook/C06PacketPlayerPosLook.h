#pragma once
#include "../C03PacketPlayer.h"

class C06PacketPlayerPosLook : public C03PacketPlayer
{
public:
	using C03PacketPlayer::C03PacketPlayer;
	static C06PacketPlayerPosLook newObject(const Ripterms::Maths::Vector3d& position, const Ripterms::Maths::Vector2d& rotation, bool isOnGround, JNIEnv* env = Ripterms::p_env);

	//on 1.7.10, packet is different, it contains a stance value, which is usually set to posY
	//and y is set to boundingBox.minY
	static C06PacketPlayerPosLook newObject1_7_10(const Ripterms::Maths::Vector3d& position, double stance, const Ripterms::Maths::Vector2d& rotation, bool isOnGround, JNIEnv* env = Ripterms::p_env);
protected:
	inline static Ripterms::JavaClassV2 C06PacketPlayerPosLookClass{ "net/minecraft/network/play/client/C03PacketPlayer$C06PacketPlayerPosLook" };
};