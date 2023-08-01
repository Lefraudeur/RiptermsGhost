#pragma once
#include "../Entity/Entity.h"

class EntityLivingBase : Entity {
public:
	using Entity::Entity;
	using Entity::operator=;
	using Entity::operator==;
	static bool init();
protected:
	inline static Ripterms::JavaClass EntityLivingBaseClass{};
};