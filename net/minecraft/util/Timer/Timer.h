#pragma once
#include "../../../../java/lang/Object/Object.h"

class Timer : public Object {
public:
	using Object::Object;
	float getRenderPartialTicks();
protected:
	inline static Ripterms::JavaClassV2 TimerClass{ "net/minecraft/util/Timer" };
};