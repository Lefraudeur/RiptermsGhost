#pragma once
#include "../../../entity/player/EntityPlayer/EntityPlayer.h"

class AbstractClientPlayer : EntityPlayer {
public:
	using EntityPlayer::EntityPlayer;
	using EntityPlayer::operator=;
	using EntityPlayer::operator==;
	static bool init();
protected:
	inline static Ripterms::JavaClass AbstractClientPlayerClass{};
};