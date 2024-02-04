#pragma once
#include "../../../../../java/lang/Object/Object.h"
#include "../KeyBinding/KeyBinding.h"

class GameSettings : public Object {
public:
	using Object::Object;

	double getGammaSetting();
	KeyBinding getKeyBindSneak();
	KeyBinding getKeyBindSprint();

	void setGammaSetting(double value);
protected:
	inline static Ripterms::JavaClassV2 GameSettingsClass{ "net/minecraft/client/settings/GameSettings" };
};