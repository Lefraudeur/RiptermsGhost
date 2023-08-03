#pragma once
#include "../Entity/Entity.h"

class EntityLivingBase : public Entity {
public:
	using Entity::Entity;
	static bool init();
protected:
	inline static Ripterms::JavaClass* EntityLivingBaseClass = nullptr;
};