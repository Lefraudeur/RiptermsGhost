#pragma once
#include "../AbstractClientPlayer/AbstractClientPlayer.h"

class EntityPlayerSP : AbstractClientPlayer {
public:
	using AbstractClientPlayer::AbstractClientPlayer;
	using AbstractClientPlayer::operator=;
	using AbstractClientPlayer::operator==;
	static bool init();
protected:
	inline static Ripterms::JavaClass EntityPlayerSPClass{};
};
