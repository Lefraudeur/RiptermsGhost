#include "PlayerControllerMP.h"

void PlayerControllerMP::attackEntity(const EntityPlayer& player, const Entity& targetEntity)
{
	if (!instance)
		return;
	env->CallVoidMethod(instance, PlayerControllerMPClass.getMethodID("attackEntity"), player.getInstance(), targetEntity.getInstance());
}
