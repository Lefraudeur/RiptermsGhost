#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../util/AxisAlignedBB/AxisAlignedBB.h"

class Entity : public Object
{
public:
	using Object::Object;

	Ripterms::Maths::Vector3d getPosition() const;
	Ripterms::Maths::Vector3d getLastTickPosition() const;
	Ripterms::Maths::Vector3d getMovementVector(float partialTicks) const; //(currpos - lastpos) * partial ticks
	Ripterms::Maths::Vector2d getRotation() const;
	Ripterms::Maths::Vector3d getMotion() const;
	bool isOnGround() const;
	bool isSprinting() const;
	int getHurtResistantTime() const;
	int getTicksExisted() const;
	AxisAlignedBB getBoundingBox() const;
	float getEyeHeight() const;

	void setSprinting(bool state);
	void setMotion(const Ripterms::Maths::Vector3d& motion);
	void setRotation(const Ripterms::Maths::Vector2d& yawPitch);
protected:
	inline static Ripterms::JavaClassV2 EntityClass{ "net/minecraft/entity/Entity" };
};