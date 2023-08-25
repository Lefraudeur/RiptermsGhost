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

MovingObjectPosition Minecraft::getObjectMouseOver()
{
	if(!instance) return MovingObjectPosition();
	return MovingObjectPosition(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->MinecraftClass.fields["objectMouseOver"]));
}

Entity Minecraft::getPointedEntity()
{
	if (!instance) return Entity();
	return Entity(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->MinecraftClass.fields["pointedEntity"]));
}

int Minecraft::getRightClickDelayTimer()
{
	if (!instance) return 0;
	return Ripterms::p_env->GetIntField(instance, Ripterms::classcache->MinecraftClass.fields["rightClickDelayTimer"]);
}

void Minecraft::setRightClickDelayTimer(int value)
{
	if (!instance) return;
	Ripterms::p_env->SetIntField(instance, Ripterms::classcache->MinecraftClass.fields["rightClickDelayTimer"], value);
}
