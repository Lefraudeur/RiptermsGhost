#pragma once
#include "../../../../../java/lang/Object/Object.h"
#include "../KeyBinding/KeyBinding.h"

class GameSettings : public Object {
public:
	using Object::Object;

	float getGammaSetting();
	KeyBinding getKeyBindSneak();
	KeyBinding getKeyBindSprint();

	void setGammaSetting(float value);
protected:
	inline static Ripterms::JavaClassV2 GameSettingsClass{ "net/minecraft/client/settings/GameSettings" };
};