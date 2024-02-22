#include "C03PacketPlayer.h"

C03PacketPlayer C03PacketPlayer::newObject(bool isOnGround, JNIEnv* env)
{
	if (!env)
		return C03PacketPlayer(nullptr, env);
	return C03PacketPlayer(env->NewObject(C03PacketPlayerClass.get_jclass(env), C03PacketPlayerClass.getMethodID("<init>"), (isOnGround ? JNI_TRUE : JNI_FALSE)), env);
}

Ripterms::Maths::Vector3d C03PacketPlayer::getXYZ()
{
	if (!instance)
		return Ripterms::Maths::Vector3d();
	return Ripterms::Maths::Vector3d
	(
		env->GetDoubleField(instance, C03PacketPlayerClass.getFieldID("x")),
		env->GetDoubleField(instance, C03PacketPlayerClass.getFieldID("y")),
		env->GetDoubleField(instance, C03PacketPlayerClass.getFieldID("z"))
	);
}

void C03PacketPlayer::setXYZ(const Ripterms::Maths::Vector3d& vector)
{
	if (!instance)
		return;
	env->SetDoubleField(instance, C03PacketPlayerClass.getFieldID("x"), (jdouble)vector.x);
	env->SetDoubleField(instance, C03PacketPlayerClass.getFieldID("y"), (jdouble)vector.y);
	env->SetDoubleField(instance, C03PacketPlayerClass.getFieldID("z"), (jdouble)vector.z);
}

Ripterms::Maths::Vector2d C03PacketPlayer::getYawPitch()
{
	if (!instance)
		return Ripterms::Maths::Vector2d();
	return Ripterms::Maths::Vector2d
	(
		env->GetFloatField(instance, C03PacketPlayerClass.getFieldID("yaw")),
		env->GetFloatField(instance, C03PacketPlayerClass.getFieldID("pitch"))
	);
}

void C03PacketPlayer::setYawPitch(Ripterms::Maths::Vector2d yawPitch)
{
	if (!instance)
		return;
	env->SetFloatField(instance, C03PacketPlayerClass.getFieldID("yaw"), (jfloat)yawPitch.x);
	env->SetFloatField(instance, C03PacketPlayerClass.getFieldID("pitch"), (jfloat)yawPitch.y);
}

bool C03PacketPlayer::getOnGround()
{
	if (!instance)
		return false;
	return env->GetBooleanField(instance, C03PacketPlayerClass.getFieldID("onGround")) == JNI_TRUE;
}

void C03PacketPlayer::setOnGround(bool state)
{
	if (!instance)
		return;
	env->SetBooleanField(instance, C03PacketPlayerClass.getFieldID("onGround"), (state ? JNI_TRUE : JNI_FALSE));
}

bool C03PacketPlayer::getMoving()
{
	if (!instance)
		return false;
	return env->GetBooleanField(instance, C03PacketPlayerClass.getFieldID("moving")) == JNI_TRUE;
}

void C03PacketPlayer::setMoving(bool state)
{
	if (!instance)
		return;
	env->SetBooleanField(instance, C03PacketPlayerClass.getFieldID("moving"), (state ? JNI_TRUE : JNI_FALSE));
}

bool C03PacketPlayer::getRotating()
{
	if (!instance)
		return false;
	return env->GetBooleanField(instance, C03PacketPlayerClass.getFieldID("rotating")) == JNI_TRUE;
}

void C03PacketPlayer::setRotating(bool state)
{
	if (!instance)
		return;
	env->SetBooleanField(instance, C03PacketPlayerClass.getFieldID("rotating"), (state ? JNI_TRUE : JNI_FALSE));
}
