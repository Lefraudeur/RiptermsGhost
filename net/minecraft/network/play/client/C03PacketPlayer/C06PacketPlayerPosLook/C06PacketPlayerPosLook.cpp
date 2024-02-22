#include "C06PacketPlayerPosLook.h"

C06PacketPlayerPosLook C06PacketPlayerPosLook::newObject(const Ripterms::Maths::Vector3d& position, const Ripterms::Maths::Vector2d& rotation, bool isOnGround, JNIEnv* env)
{
	if (!env)
		return C06PacketPlayerPosLook(nullptr, env);
	return C06PacketPlayerPosLook
	(
		env->NewObject
		(
			C06PacketPlayerPosLookClass.get_jclass(env),
			C06PacketPlayerPosLookClass.getMethodID("<init>"),
			(jdouble)position.x,
			(jdouble)position.y,
			(jdouble)position.z,
			(jfloat)rotation.x,
			(jfloat)rotation.y,
			(isOnGround ? JNI_TRUE : JNI_FALSE)
		),
		env
	);
}

C06PacketPlayerPosLook C06PacketPlayerPosLook::newObject1_7_10(const Ripterms::Maths::Vector3d& position, double stance, const Ripterms::Maths::Vector2d& rotation, bool isOnGround, JNIEnv* env)
{
	if (!env)
		return C06PacketPlayerPosLook(nullptr, env);
	return C06PacketPlayerPosLook
	(
		env->NewObject
		(
			C06PacketPlayerPosLookClass.get_jclass(env),
			C06PacketPlayerPosLookClass.getMethodID("<init>"),
			(jdouble)position.x,
			(jdouble)position.y,
			stance,
			(jdouble)position.z,
			(jfloat)rotation.x,
			(jfloat)rotation.y,
			(isOnGround ? JNI_TRUE : JNI_FALSE)
		),
		env
	);
}
