#include "Entity.h"
#include "../../util/Vec3/Vec3.h"

Ripterms::Maths::Vector3d Entity::getPosition() const
{
	if (!instance) return Ripterms::Maths::Vector3d();
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5 || Ripterms::version.type == Ripterms::Version::MAJOR_1_19_4)
	{
		return Vec3(env->GetObjectField(instance, EntityClass.getFieldID("positionVec")), env).getVector();
	}
	return Ripterms::Maths::Vector3d(
		env->GetDoubleField(instance, EntityClass.getFieldID("posX")),
		env->GetDoubleField(instance, EntityClass.getFieldID("posY")),
		env->GetDoubleField(instance, EntityClass.getFieldID("posZ"))
	);
}

Ripterms::Maths::Vector3d Entity::getLastTickPosition() const
{
	if (!instance) return Ripterms::Maths::Vector3d();
	return Ripterms::Maths::Vector3d
	(
		env->GetDoubleField(instance, EntityClass.getFieldID("lastTickPosX")),
		env->GetDoubleField(instance, EntityClass.getFieldID("lastTickPosY")),
		env->GetDoubleField(instance, EntityClass.getFieldID("lastTickPosZ"))
	);
}

Ripterms::Maths::Vector3d Entity::getMovementVector(float partialTicks) const
{
	if (!instance) return Ripterms::Maths::Vector3d();
	return (getPosition() - getLastTickPosition()) * partialTicks;
}

Ripterms::Maths::Vector3d Entity::getRenderPos(float partialTicks) const
{
	return getLastTickPosition() + getMovementVector(partialTicks);
}

Ripterms::Maths::Vector2d Entity::getRotation() const
{
	if (!instance) return Ripterms::Maths::Vector2d();
	return Ripterms::Maths::Vector2d(
		env->GetFloatField(instance, EntityClass.getFieldID("rotationYaw")),
		env->GetFloatField(instance, EntityClass.getFieldID("rotationPitch"))
	);
}

Ripterms::Maths::Vector2d Entity::getPrevRotation() const
{
	if (!instance) return Ripterms::Maths::Vector2d();
	return Ripterms::Maths::Vector2d(
		env->GetFloatField(instance, EntityClass.getFieldID("prevRotationYaw")),
		env->GetFloatField(instance, EntityClass.getFieldID("prevRotationPitch"))
	);
}

Ripterms::Maths::Vector2d Entity::getRenderRotation(float partialTicks) const
{
	return getPrevRotation() + ((getRotation() - getPrevRotation()) * partialTicks);
}

Ripterms::Maths::Vector3d Entity::getMotion() const
{
	if (!instance) return Ripterms::Maths::Vector3d();
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5 || Ripterms::version.type == Ripterms::Version::MAJOR_1_19_4)
	{
		return Vec3(env->GetObjectField(instance, EntityClass.getFieldID("motion")), env).getVector();
	}
	return Ripterms::Maths::Vector3d
	(
		env->GetDoubleField(instance, EntityClass.getFieldID("motionX")),
		env->GetDoubleField(instance, EntityClass.getFieldID("motionY")),
		env->GetDoubleField(instance, EntityClass.getFieldID("motionZ"))
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

Entity Entity::getRidingEntity() const
{
	if (!instance) return Entity(env);
	return Entity
	(
		env->GetObjectField(instance, EntityClass.getFieldID("ridingEntity")),
		env
	);
}

int Entity::getEntityId() const
{
	if (!instance) return 0;
	return env->GetIntField(instance, EntityClass.getFieldID("entityId"));
}

void Entity::setPosition(const Ripterms::Maths::Vector3d& position)
{
	if (!instance) return;
	env->CallVoidMethod(instance, EntityClass.getMethodID("setPosition"), (jdouble)position.x, (jdouble)position.y, (jdouble)position.z);
}

void Entity::setRidingEntity(Entity& entity)
{
	if (!instance) return;
	env->SetObjectField(instance, EntityClass.getFieldID("ridingEntity"), entity.getInstance());
}

void Entity::setBoundingBox(const AxisAlignedBB& bb)
{
	if (!instance)
		return;
	env->SetObjectField(instance, EntityClass.getFieldID("boundingBox"), bb.getInstance());
}

void Entity::setSprinting(bool state)
{
	if (!instance) return;
	env->CallBooleanMethod(instance, EntityClass.getMethodID("setSprinting"), (jboolean)(state ? JNI_TRUE : JNI_FALSE));
}

void Entity::setMotion(const Ripterms::Maths::Vector3d& motion)
{
	if (!instance) return;
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5 || Ripterms::version.type == Ripterms::Version::MAJOR_1_19_4)
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
	env->SetFloatField(instance, EntityClass.getFieldID("rotationYaw"), (jfloat)yawPitch.x);
	env->SetFloatField(instance, EntityClass.getFieldID("rotationPitch"), (jfloat)yawPitch.y);
}

void Entity::setPositionAndUpdate(const Ripterms::Maths::Vector3d& position)
{
	if (!instance)
		return;
	env->CallVoidMethod(
		instance, 
		EntityClass.getMethodID("setPositionAndUpdate"), 
		(jdouble)position.x, 
		(jdouble)position.y, 
		(jdouble)position.z);
}
