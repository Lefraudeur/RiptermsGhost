#include "Minecraft.h"

Minecraft Minecraft::getTheMinecraft()
{
	return Minecraft(Ripterms::p_env->GetStaticObjectField(MinecraftClass.javaClass, MinecraftClass.fields["theMinecraft"]));
}

bool Minecraft::init()
{
	return MinecraftClass.fill("net/minecraft/client/Minecraft");
}
