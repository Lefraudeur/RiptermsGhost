#pragma once
#include "../../EntityLivingBase/EntityLivingBase.h"

class EntityPlayer : public EntityLivingBase {
public:
	using EntityLivingBase::EntityLivingBase;
protected:
	inline static Ripterms::JavaClassV2 EntityPlayerClass{ "net/minecraft/entity/player/EntityPlayer" };
};