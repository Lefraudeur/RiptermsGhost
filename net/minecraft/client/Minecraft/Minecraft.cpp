#include "Minecraft.h"

Minecraft Minecraft::getTheMinecraft()
{
	return Minecraft(Ripterms::p_env->GetStaticObjectField(Ripterms::classcache->MinecraftClass.javaClass, Ripterms::classcache->MinecraftClass.fields["theMinecraft"]));
}

EntityPlayerSP Minecraft::getThePlayer()
{
	if (!this->instance) return EntityPlayerSP();
	return EntityPlayerSP(Ripterms::p_env->GetObjectField(this->instance, Ripterms::classcache->MinecraftClass.fields["thePlayer"]));
}

WorldClient Minecraft::getTheWorld()
{
	if (!this->instance) return WorldClient();
	return WorldClient(Ripterms::p_env->GetObjectField(this->instance, Ripterms::classcache->MinecraftClass.fields["theWorld"]));
}

GameSettings Minecraft::getGameSettings()
{
	if (!instance) return GameSettings();
	return GameSettings(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->MinecraftClass.fields["gameSettings"]));
}
