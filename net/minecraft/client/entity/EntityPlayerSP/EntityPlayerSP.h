#pragma once
#include "../AbstractClientPlayer/AbstractClientPlayer.h"

class EntityPlayerSP : public AbstractClientPlayer {
public:
	using AbstractClientPlayer::AbstractClientPlayer;
protected:
	inline static Ripterms::JavaClassV2 EntityPlayerSPClass{ "net/minecraft/client/entity/EntityPlayerSP" };
};
