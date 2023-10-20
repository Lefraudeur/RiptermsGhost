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
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_7_10)
	{
		return Block
		(
			env->CallObjectMethod
			(
				instance,
				IBlockAccessClass.getMethodID("getBlock"),
				(int)std::floor(position.x),
				(int)std::floor(position.y),
				(int)std::floor(position.z)
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
