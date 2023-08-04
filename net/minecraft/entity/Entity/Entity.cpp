#include "Entity.h"
#include "../../util/Vec3/Vec3.h"

Ripterms::Maths::Vector3d Entity::getPosition()
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

Ripterms::Maths::Vector2d Entity::getRotation()
{
	if (!instance) return Ripterms::Maths::Vector2d();
	return Ripterms::Maths::Vector2d(
		Ripterms::p_env->GetFloatField(instance, Ripterms::classcache->EntityClass.fields["rotationYaw"]),
		Ripterms::p_env->GetFloatField(instance, Ripterms::classcache->EntityClass.fields["rotationPitch"])
	);
}

void Entity::setRotation(const Ripterms::Maths::Vector2d& yawPitch)
{
	if (!instance) return;
	Ripterms::p_env->SetFloatField(instance, Ripterms::classcache->EntityClass.fields["rotationYaw"], yawPitch.x);
	Ripterms::p_env->SetFloatField(instance, Ripterms::classcache->EntityClass.fields["rotationPitch"], yawPitch.y);
}
