#pragma once
#include "../../EntityLivingBase/EntityLivingBase.h"

class EntityPlayer : EntityLivingBase {
public:
	using EntityLivingBase::EntityLivingBase;
	using EntityLivingBase::operator=;
	using EntityLivingBase::operator==;
	static bool init();
protected:
	inline static Ripterms::JavaClass EntityPlayerClass{};
};