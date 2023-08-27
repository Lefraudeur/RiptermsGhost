#pragma once
#include "../Entity/Entity.h"

class EntityLivingBase : public Entity {
public:
	using Entity::Entity;
protected:
	inline static Ripterms::JavaClassV2 EntityLivingBaseClass{ "net/minecraft/entity/EntityLivingBase" };
};