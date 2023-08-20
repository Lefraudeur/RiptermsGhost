#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../entity/EntityPlayerSP/EntityPlayerSP.h"
#include "../multiplayer/WorldClient/WorldClient.h"
#include "../settings/GameSettings/GameSettings.h"
#include "../../util/MovingObjectPosition/MovingObjectPosition.h"

class Minecraft : public Object {
public:
	using Object::Object;
	static Minecraft getTheMinecraft();
	EntityPlayerSP getThePlayer();
	WorldClient getTheWorld();
	GameSettings getGameSettings();
	MovingObjectPosition getObjectMouseOver();
	int getRightClickDelayTimer();
	void setRightClickDelayTimer(int value);
};