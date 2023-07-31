#pragma once
#include "../../../../java/lang/Object/Object.h"

class Minecraft : Object {
public:
	static jobject getTheMinecraft();
	inline static Ripterms::JavaClass MinecraftClass;
};