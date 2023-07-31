#include "Minecraft.h"

jobject Minecraft::getTheMinecraft()
{
	return nullptr;
}

bool Minecraft::init()
{
	return MinecraftClass.fill("net/minecraft/client/Minecraft");
}
