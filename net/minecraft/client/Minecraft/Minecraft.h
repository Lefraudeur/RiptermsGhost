#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../entity/EntityPlayerSP/EntityPlayerSP.h"
#include "../multiplayer/WorldClient/WorldClient.h"

class Minecraft : public Object {
public:
	using Object::Object;
	static Minecraft getTheMinecraft();
	EntityPlayerSP getThePlayer();
	WorldClient getTheWorld();
	static bool init();
protected:
	inline static Ripterms::JavaClass* MinecraftClass = nullptr;
};