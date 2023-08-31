#include "IBlockState.h"

Block IBlockState::getBlock()
{
	if (!instance)
		return Block(env);
	return Block(env->CallObjectMethod(instance, IBlockStateClass.getMethodID("getBlock")), env);
}
