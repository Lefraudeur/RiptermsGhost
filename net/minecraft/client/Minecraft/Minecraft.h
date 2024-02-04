#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../entity/EntityPlayerSP/EntityPlayerSP.h"
#include "../multiplayer/WorldClient/WorldClient.h"
#include "../settings/GameSettings/GameSettings.h"
#include "../../util/MovingObjectPosition/MovingObjectPosition.h"
#include "../../util/Timer/Timer.h"
#include "../multiplayer/PlayerControllerMP/PlayerControllerMP.h"
#include "../gui/GuiScreen/GuiScreen.h"

class Minecraft : public Object {
public:
	using Object::Object;

	static Minecraft getTheMinecraft(JNIEnv* env = Ripterms::p_env);
	EntityPlayerSP getThePlayer();
	PlayerControllerMP getPlayerController();
	WorldClient getTheWorld();
	GameSettings getGameSettings();
	MovingObjectPosition getObjectMouseOver();
	Entity getPointedEntity();
	Entity getRenderViewEntity();
	Timer getTimer();
	GuiScreen getCurrentScreen();
	int getRightClickDelayTimer();
	void clickMouse();

	void setRightClickDelayTimer(int value);
protected:
	inline static Ripterms::JavaClassV2 MinecraftClass{ "net/minecraft/client/Minecraft" };
};