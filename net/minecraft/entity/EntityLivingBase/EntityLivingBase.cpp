#include "EntityLivingBase.h"

bool EntityLivingBase::init()
{
	EntityLivingBaseClass = new Ripterms::JavaClass("net/minecraft/entity/EntityLivingBase");
	Ripterms::classes.push_back(EntityLivingBaseClass);
	return EntityLivingBaseClass->isSuccess;
}
