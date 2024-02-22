#include "BlockPos.h"

BlockPos BlockPos::newObject(const Ripterms::Maths::Vector3d& vector, JNIEnv* env)
{
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_19_4)
	{
		return BlockPos
		(
			env->NewObject
			(
				BlockPosClass.get_jclass(env),
				BlockPosClass.getMethodID("<init>"),
				(jint)std::floor(vector.x),
				(jint)std::floor(vector.y),
				(jint)std::floor(vector.z)
			), env
		);
	}
	return BlockPos
	(
		env->NewObject
		(
			BlockPosClass.get_jclass(env),
			BlockPosClass.getMethodID("<init>"),
			(jdouble)vector.x,
			(jdouble)vector.y,
			(jdouble)vector.z
		), env
	);
}
