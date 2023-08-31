#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../Block.h"

class IBlockState : public Object
{
public:
	using Object::Object;
	Block getBlock();
protected:
	inline static Ripterms::JavaClassV2 IBlockStateClass{ "net/minecraft/block/state/IBlockState" };
};