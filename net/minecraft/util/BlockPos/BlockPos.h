#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../../../Ripterms/Maths/Maths.h"

class BlockPos : public Object
{
public:
	using Object::Object;
	static BlockPos newObject(const Ripterms::Maths::Vector3d& vector, JNIEnv* env = Ripterms::p_env);
protected:
	inline static Ripterms::JavaClassV2 BlockPosClass{ "net/minecraft/util/BlockPos" };
};