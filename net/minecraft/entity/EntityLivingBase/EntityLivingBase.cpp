#include "EntityLivingBase.h"

void EntityLivingBase::setPositionAndUpdate(const Ripterms::Maths::Vector3d& position)
{
	if (!instance)
		return;
	if (Ripterms::version == Ripterms::Version::FORGE_1_7_10 || Ripterms::version == Ripterms::Version::LUNAR_1_7_10)
	{
		env->CallVoidMethod(
			instance,
			EntityLivingBaseClass.getMethodID("setPositionAndUpdate"),
			(jdouble)position.x,
			(jdouble)position.y,
			(jdouble)position.z);
		return;
	}
	Entity::setPositionAndUpdate(position);
	return;
}