#include "PlayerControllerMP.h"

void PlayerControllerMP::attackEntity(EntityPlayer player, Entity targetEntity)
{
	if (!instance)
		return;
	env->CallVoidMethod(instance, PlayerControllerMPClass.getMethodID("attackEntity"), player.getInstance(), targetEntity.getInstance());
}
