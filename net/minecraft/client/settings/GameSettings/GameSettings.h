#pragma once
#include "../../../../../java/lang/Object/Object.h"

class GameSettings : public Object {
public:
	using Object::Object;
	float getGammaSetting();
	void setGammaSetting(float value);
protected:
	inline static Ripterms::JavaClassV2 GameSettingsClass{ "net/minecraft/client/settings/GameSettings" };
};