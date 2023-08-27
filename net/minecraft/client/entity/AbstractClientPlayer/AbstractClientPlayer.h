#pragma once
#include "../../../entity/player/EntityPlayer/EntityPlayer.h"

class AbstractClientPlayer : public EntityPlayer {
public:
	using EntityPlayer::EntityPlayer;
protected:
	inline static Ripterms::JavaClassV2 AbstractClientPlayerClass{ "net/minecraft/client/entity/AbstractClientPlayer" };
};