#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../entity/EntityPlayerSP/EntityPlayerSP.h"
#include "../multiplayer/WorldClient/WorldClient.h"
#include "../settings/GameSettings/GameSettings.h"
#include "../../util/MovingObjectPosition/MovingObjectPosition.h"
#include "../../util/Timer/Timer.h"

class Minecraft : public Object {
public:
	using Object::Object;

	static Minecraft getTheMinecraft(JNIEnv* env = Ripterms::p_env);
	EntityPlayerSP getThePlayer();
	WorldClient getTheWorld();
	GameSettings getGameSettings();
	MovingObjectPosition getObjectMouseOver();
	Entity getPointedEntity();
	Timer getTimer();
	int getRightClickDelayTimer();

	void setRightClickDelayTimer(int value);
protected:
	inline static Ripterms::JavaClassV2 MinecraftClass{ "net/minecraft/client/Minecraft" };
};