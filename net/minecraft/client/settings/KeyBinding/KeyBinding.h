#pragma once
#include "../../../../../java/lang/Object/Object.h"

class KeyBinding : public Object {
public:
	using Object::Object;
	void setPressed(bool pressed);
	void setPressTime(int pressTime);
	bool isPressed();
protected:
	inline static Ripterms::JavaClassV2 KeyBindingClass{ "net/minecraft/client/settings/KeyBinding" };
};