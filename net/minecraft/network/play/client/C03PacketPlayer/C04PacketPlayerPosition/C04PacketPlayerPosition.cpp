#include "C04PacketPlayerPosition.h"

C04PacketPlayerPosition C04PacketPlayerPosition::newObject(const Ripterms::Maths::Vector3d& position, bool isOnGround, JNIEnv* env)
{
	if (!env)
		return C04PacketPlayerPosition(nullptr, env);
	return C04PacketPlayerPosition
	(
		env->NewObject
		(
			C04PacketPlayerPositionClass.get_jclass(env),
			C04PacketPlayerPositionClass.getMethodID("<init>"),
			(jdouble)position.x,
			(jdouble)position.y,
			(jdouble)position.z,
			(isOnGround ? JNI_TRUE : JNI_FALSE)
		),
		env
	);
}

C04PacketPlayerPosition C04PacketPlayerPosition::newObject1_7_10(const Ripterms::Maths::Vector3d& position, double stance, bool isOnGround, JNIEnv* env)
{
	if (!env)
		return C04PacketPlayerPosition(nullptr, env);
	return C04PacketPlayerPosition
	(
		env->NewObject
		(
			C04PacketPlayerPositionClass.get_jclass(env),
			C04PacketPlayerPositionClass.getMethodID("<init>"),
			(jdouble)position.x,
			(jdouble)position.y,
			stance,
			(jdouble)position.z,
			(isOnGround ? JNI_TRUE : JNI_FALSE)
		),
		env
	);
}
