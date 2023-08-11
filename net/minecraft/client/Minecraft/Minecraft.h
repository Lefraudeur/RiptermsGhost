#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../entity/EntityPlayerSP/EntityPlayerSP.h"
#include "../multiplayer/WorldClient/WorldClient.h"
#include "../settings/GameSettings/GameSettings.h"
#include "../../profiler/PlayerUsageSnooper/PlayerUsageSnooper.h"

class Minecraft : public Object {
public:
	using Object::Object;
	static Minecraft getTheMinecraft();
	EntityPlayerSP getThePlayer();
	WorldClient getTheWorld();
	GameSettings getGameSettings();
	PlayerUsageSnooper getUsageSnooper();
};