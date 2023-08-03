#include "Entity.h"

bool Entity::init()
{
	EntityClass = new Ripterms::JavaClass("net/minecraft/entity/Entity");
	Ripterms::classes.push_back(EntityClass);
	return EntityClass->isSuccess;
}

Ripterms::Maths::Vector3d Entity::getPosition()
{
	if (!instance) return Ripterms::Maths::Vector3d();
	return Ripterms::Maths::Vector3d(
		(float)Ripterms::p_env->GetDoubleField(instance, EntityClass->fields["posX"]),
		(float)Ripterms::p_env->GetDoubleField(instance, EntityClass->fields["posY"]),
		(float)Ripterms::p_env->GetDoubleField(instance, EntityClass->fields["posZ"])
	);
}

Ripterms::Maths::Vector2d Entity::getRotation()
{
	if (!instance) return Ripterms::Maths::Vector2d();
	return Ripterms::Maths::Vector2d(
		Ripterms::p_env->GetFloatField(instance, EntityClass->fields["rotationYaw"]),
		Ripterms::p_env->GetFloatField(instance, EntityClass->fields["rotationPitch"])
	);
}

void Entity::setRotation(const Ripterms::Maths::Vector2d& yawPitch)
{
	if (!instance) return;
	Ripterms::p_env->SetFloatField(instance, EntityClass->fields["rotationYaw"], yawPitch.x);
	Ripterms::p_env->SetFloatField(instance, EntityClass->fields["rotationPitch"], yawPitch.y);
}
