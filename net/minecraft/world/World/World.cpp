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

Block World::getBlock(const Ripterms::Maths::Vector3d& position)
{
	if (!instance) return Block(env);
	if (Ripterms::version == Ripterms::Version::LUNAR_1_7_10 || Ripterms::version == Ripterms::Version::FORGE_1_7_10)
	{
		return Block
		(
			env->CallObjectMethod
			(
				instance,
				WorldClass.getMethodID("getBlock"), 
				(jint)position.x,
				(jint)position.y,
				(jint)position.z
			),
			env
		);
	}
	BlockPos blockPos = BlockPos::newObject(position, env);
	return getBlockState(blockPos).getBlock();
}

List World::getPlayerEntities()
{
	if (!instance) return {};
	return List(env->GetObjectField(instance, WorldClass.getFieldID("playerEntities")), env);
}
