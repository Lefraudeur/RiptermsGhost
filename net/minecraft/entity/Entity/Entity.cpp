#include "Entity.h"
#include "../../util/Vec3/Vec3.h"

Ripterms::Maths::Vector3d Entity::getPosition() const
{
	if (!instance) return Ripterms::Maths::Vector3d();
	if (Ripterms::majorVersion == Ripterms::Version::MAJOR_1_16_5) {
		return Vec3(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->EntityClass.fields["positionVec"])).getVector();
	}
	return Ripterms::Maths::Vector3d(
		(float)Ripterms::p_env->GetDoubleField(instance, Ripterms::classcache->EntityClass.fields["posX"]),
		(float)Ripterms::p_env->GetDoubleField(instance, Ripterms::classcache->EntityClass.fields["posY"]),
		(float)Ripterms::p_env->GetDoubleField(instance, Ripterms::classcache->EntityClass.fields["posZ"])
	);
}

Ripterms::Maths::Vector2d Entity::getRotation() const
{
	if (!instance) return Ripterms::Maths::Vector2d();
	return Ripterms::Maths::Vector2d(
		Ripterms::p_env->GetFloatField(instance, Ripterms::classcache->EntityClass.fields["rotationYaw"]),
		Ripterms::p_env->GetFloatField(instance, Ripterms::classcache->EntityClass.fields["rotationPitch"])
	);
}

Ripterms::Maths::Vector3d Entity::getMotion() const
{
	if (!instance) return Ripterms::Maths::Vector3d();
	if (Ripterms::majorVersion == Ripterms::Version::MAJOR_1_16_5)
	{
		return Vec3(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->EntityClass.fields["motion"])).getVector();
	}
	return Ripterms::Maths::Vector3d
	(
		(float)Ripterms::p_env->GetDoubleField(instance, Ripterms::classcache->EntityClass.fields["motionX"]),
		(float)Ripterms::p_env->GetDoubleField(instance, Ripterms::classcache->EntityClass.fields["motionY"]),
		(float)Ripterms::p_env->GetDoubleField(instance, Ripterms::classcache->EntityClass.fields["motionZ"])
	);
}

int Entity::getHurtResistantTime() const
{
	if (!instance) return 0;
	return Ripterms::p_env->GetIntField(instance, Ripterms::classcache->EntityClass.fields["hurtResistantTime"]);
}

int Entity::getTicksExisted() const
{
	if (!instance) return 0;
	return Ripterms::p_env->GetIntField(instance, Ripterms::classcache->EntityClass.fields["ticksExisted"]);
}

void Entity::setMotion(const Ripterms::Maths::Vector3d& motion)
{
	if (!instance) return;
	if (Ripterms::majorVersion == Ripterms::Version::MAJOR_1_16_5)
	{
		Vec3 motion_obj(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->EntityClass.fields["motion"]));
		motion_obj.setVector(motion);
		return;
	}
	Ripterms::p_env->SetDoubleField(instance, Ripterms::classcache->EntityClass.fields["motionX"], motion.x);
	Ripterms::p_env->SetDoubleField(instance, Ripterms::classcache->EntityClass.fields["motionY"], motion.y);
	Ripterms::p_env->SetDoubleField(instance, Ripterms::classcache->EntityClass.fields["motionZ"], motion.z);
}

void Entity::setRotation(const Ripterms::Maths::Vector2d& yawPitch)
{
	if (!instance) return;
	Ripterms::p_env->SetFloatField(instance, Ripterms::classcache->EntityClass.fields["rotationYaw"], yawPitch.x);
	Ripterms::p_env->SetFloatField(instance, Ripterms::classcache->EntityClass.fields["rotationPitch"], yawPitch.y);
}
