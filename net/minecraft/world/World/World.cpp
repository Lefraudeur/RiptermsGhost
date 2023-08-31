#include "World.h"
#include "../../../../java/util/List/List.h"

IBlockState World::getBlockState(const BlockPos& blockPos)
{
	if (!instance)
		return IBlockState(env);
	return IBlockState
	(
		env->CallObjectMethod
		(
			instance,
			IBlockAccessClass.getMethodID("getBlockState"), 
			blockPos.getInstance()
		), env
	);
}

List World::getPlayerEntities()
{
	if (!instance) return {};
	return List(env->GetObjectField(instance, WorldClass.getFieldID("playerEntities")), env);
}
