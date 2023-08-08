#pragma once
#include "../../../../../java/lang/Object/Object.h"

class GameSettings : public Object {
public:
	using Object::Object;
	float getGammaSetting();
	void setGammaSetting(float value);
};