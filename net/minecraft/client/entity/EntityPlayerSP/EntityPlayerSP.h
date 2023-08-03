#pragma once
#include "../AbstractClientPlayer/AbstractClientPlayer.h"

class EntityPlayerSP : public AbstractClientPlayer {
public:
	using AbstractClientPlayer::AbstractClientPlayer;
	static bool init();
protected:
	inline static Ripterms::JavaClass* EntityPlayerSPClass = nullptr;
};
