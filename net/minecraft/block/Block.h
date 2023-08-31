#pragma once
#include "../../../java/lang/Object/Object.h"

class Block : public Object
{
public:
	using Object::Object;
protected:
	inline static Ripterms::JavaClassV2 BlockClass{ "net/minecraft/block/Block" };
};