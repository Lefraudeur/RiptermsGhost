#include "Minecraft.h"

Minecraft Minecraft::getTheMinecraft(JNIEnv* env)
{
	return Minecraft(env->GetStaticObjectField(MinecraftClass.get_jclass(env), MinecraftClass.getFieldID("theMinecraft")), env);
}

EntityPlayerSP Minecraft::getThePlayer()
{
	if (!this->instance) return EntityPlayerSP(nullptr, env);
	return EntityPlayerSP(env->GetObjectField(this->instance, MinecraftClass.getFieldID("thePlayer")), env);
}

PlayerControllerMP Minecraft::getPlayerController()
{
	if (!instance) return PlayerControllerMP(nullptr, env);
	return PlayerControllerMP(env->GetObjectField(instance, MinecraftClass.getFieldID("playerController")), env);
}

WorldClient Minecraft::getTheWorld()
{
	if (!this->instance) return WorldClient(nullptr, env);
	return WorldClient(env->GetObjectField(this->instance, MinecraftClass.getFieldID("theWorld")), env);
}

GameSettings Minecraft::getGameSettings()
{
	if (!instance) return GameSettings(nullptr, env);
	return GameSettings(env->GetObjectField(instance, MinecraftClass.getFieldID("gameSettings")), env);
}

MovingObjectPosition Minecraft::getObjectMouseOver()
{
	if(!instance) return MovingObjectPosition(nullptr, env);
	return MovingObjectPosition(env->GetObjectField(instance, MinecraftClass.getFieldID("objectMouseOver")), env);
}

Entity Minecraft::getPointedEntity()
{
	if (!instance) return Entity(nullptr, env);
	return Entity(env->GetObjectField(instance, MinecraftClass.getFieldID("pointedEntity")), env);
}

Entity Minecraft::getRenderViewEntity()
{
	if (!instance) return Entity(nullptr, env);
	return Entity(env->GetObjectField(instance, MinecraftClass.getFieldID("renderViewEntity")), env);
}

Timer Minecraft::getTimer()
{
	if(!instance) return Timer(env);
	return Timer(env->GetObjectField(instance, MinecraftClass.getFieldID("timer")), env);
}

GuiScreen Minecraft::getCurrentScreen()
{
	if (!instance)
		return GuiScreen(env);
	return GuiScreen(env->GetObjectField(instance, MinecraftClass.getFieldID("currentScreen")), env);
}

int Minecraft::getRightClickDelayTimer()
{
	if (!instance) return 0;
	return env->GetIntField(instance, MinecraftClass.getFieldID("rightClickDelayTimer"));
}

void Minecraft::clickMouse()
{
	if (!instance)
		return;
	env->CallVoidMethod(instance, MinecraftClass.getMethodID("clickMouse"));
	return;
}

void Minecraft::setRightClickDelayTimer(int value)
{
	if (!instance) return;
	env->SetIntField(instance, MinecraftClass.getFieldID("rightClickDelayTimer"), value);
}
