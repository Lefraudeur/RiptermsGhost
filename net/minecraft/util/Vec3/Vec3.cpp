#include "Vec3.h"

Ripterms::Maths::Vector3d Vec3::getVector() const
{
	if (!instance) return Ripterms::Maths::Vector3d();
	return Ripterms::Maths::Vector3d(
		env->GetDoubleField(instance, Vec3Class.getFieldID("xCoord")),
		env->GetDoubleField(instance, Vec3Class.getFieldID("yCoord")),
		env->GetDoubleField(instance, Vec3Class.getFieldID("zCoord"))
	);
}

void Vec3::setVector(const Ripterms::Maths::Vector3d& vector)
{
	if (!instance) return;
	env->SetDoubleField(instance, Vec3Class.getFieldID("xCoord"), (jdouble)vector.x);
	env->SetDoubleField(instance, Vec3Class.getFieldID("yCoord"), (jdouble)vector.y);
	env->SetDoubleField(instance, Vec3Class.getFieldID("zCoord"), (jdouble)vector.z);
}
