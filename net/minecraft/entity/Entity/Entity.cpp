#include "Entity.h"
#include "../../../../Ripterms/Cache/Cache.h"
#include "../../util/Vec3/Vec3.h"

Ripterms::Maths::Vector3d Entity::getPosition() const
{
	if (!instance) return Ripterms::Maths::Vector3d();
	if (Ripterms::majorVersion == Ripterms::Version::MAJOR_1_16_5)
	{
		return Vec3(env->GetObjectField(instance, EntityClass.getFieldID("positionVec")), env).getVector();
	}
	return Ripterms::Maths::Vector3d(
		(float)env->GetDoubleField(instance, EntityClass.getFieldID("posX")),
		(float)env->GetDoubleField(instance, EntityClass.getFieldID("posY")),
		(float)env->GetDoubleField(instance, EntityClass.getFieldID("posZ"))
	);
}

Ripterms::Maths::Vector3d Entity::getLastTickPosition() const
{
	if (!instance) return Ripterms::Maths::Vector3d();
	return Ripterms::Maths::Vector3d
	(
		(float)env->GetDoubleField(instance, EntityClass.getFieldID("lastTickPosX")),
		(float)env->GetDoubleField(instance, EntityClass.getFieldID("lastTickPosY")),
		(float)env->GetDoubleField(instance, EntityClass.getFieldID("lastTickPosZ"))
	);
}

Ripterms::Maths::Vector3d Entity::getMovementVector(float partialTicks) const
{
	if (!instance) return Ripterms::Maths::Vector3d();
	return (getPosition() - getLastTickPosition()) * partialTicks;
}

Ripterms::Maths::Vector2d Entity::getRotation() const
{
	if (!instance) return Ripterms::Maths::Vector2d();
	return Ripterms::Maths::Vector2d(
		env->GetFloatField(instance, EntityClass.getFieldID("rotationYaw")),
		env->GetFloatField(instance, EntityClass.getFieldID("rotationPitch"))
	);
}

Ripterms::Maths::Vector3d Entity::getMotion() const
{
	if (!instance) return Ripterms::Maths::Vector3d();
	if (Ripterms::majorVersion == Ripterms::Version::MAJOR_1_16_5)
	{
		return Vec3(env->GetObjectField(instance, EntityClass.getFieldID("motion")), env).getVector();
	}
	return Ripterms::Maths::Vector3d
	(
		(float)env->GetDoubleField(instance, EntityClass.getFieldID("motionX")),
		(float)env->GetDoubleField(instance, EntityClass.getFieldID("motionY")),
		(float)env->GetDoubleField(instance, EntityClass.getFieldID("motionZ"))
	);
}

bool Entity::isOnGround() const
{
	if (!instance) return false;
	return env->GetBooleanField(instance, EntityClass.getFieldID("onGround")) == JNI_TRUE;
}

bool Entity::isSprinting() const
{
	if (!instance) return false;
	return env->CallBooleanMethod(instance, EntityClass.getMethodID("isSprinting")) == JNI_TRUE;
}

int Entity::getHurtResistantTime() const
{
	if (!instance) return 0;
	return env->GetIntField(instance, EntityClass.getFieldID("hurtResistantTime"));
}

int Entity::getTicksExisted() const
{
	if (!instance) return 0;
	return env->GetIntField(instance, EntityClass.getFieldID("ticksExisted"));
}

AxisAlignedBB Entity::getBoundingBox() const
{
	if (!instance) return AxisAlignedBB(env);
	return AxisAlignedBB(env->GetObjectField(instance, EntityClass.getFieldID("boundingBox")), env);
}

float Entity::getEyeHeight() const
{
	if (!instance) return 0.0f;
	return env->CallFloatMethod(instance, EntityClass.getMethodID("getEyeHeight"));
}

void Entity::setSprinting(bool state)
{
	if (!instance) return;
	env->CallBooleanMethod(instance, EntityClass.getMethodID("setSprinting"), (jboolean)(state ? JNI_TRUE : JNI_FALSE));
}

void Entity::setMotion(const Ripterms::Maths::Vector3d& motion)
{
	if (!instance) return;
	if (Ripterms::majorVersion == Ripterms::Version::MAJOR_1_16_5)
	{
		Vec3 motion_obj(env->GetObjectField(instance, EntityClass.getFieldID("motion")), env);
		motion_obj.setVector(motion);
		return;
	}
	env->SetDoubleField(instance, EntityClass.getFieldID("motionX"), motion.x);
	env->SetDoubleField(instance, EntityClass.getFieldID("motionY"), motion.y);
	env->SetDoubleField(instance, EntityClass.getFieldID("motionZ"), motion.z);
}

void Entity::setRotation(const Ripterms::Maths::Vector2d& yawPitch)
{
	if (!instance) return;
	env->SetFloatField(instance, EntityClass.getFieldID("rotationYaw"), yawPitch.x);
	env->SetFloatField(instance, EntityClass.getFieldID("rotationPitch"), yawPitch.y);
}
