#pragma once
#include "../../EntityLivingBase/EntityLivingBase.h"

class EntityPlayer : public EntityLivingBase {
public:
	using EntityLivingBase::EntityLivingBase;
	static bool init();
protected:
	inline static Ripterms::JavaClass EntityPlayerClass{};
};