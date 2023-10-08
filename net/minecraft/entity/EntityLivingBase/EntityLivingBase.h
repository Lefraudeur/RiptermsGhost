#pragma once
#include "../Entity/Entity.h"

class EntityLivingBase : public Entity {
public:
	using Entity::Entity;
	void setPositionAndUpdate(const Ripterms::Maths::Vector3d& position) override;
protected:
	inline static Ripterms::JavaClassV2 EntityLivingBaseClass{ "net/minecraft/entity/EntityLivingBase" };
};