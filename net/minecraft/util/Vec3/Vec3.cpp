#include "Vec3.h"

Ripterms::Maths::Vector3d Vec3::getVector() const
{
	if (!instance) return Ripterms::Maths::Vector3d();
	return Ripterms::Maths::Vector3d(
		(float)env->GetDoubleField(instance, Vec3Class.getFieldID("xCoord")),
		(float)env->GetDoubleField(instance, Vec3Class.getFieldID("yCoord")),
		(float)env->GetDoubleField(instance, Vec3Class.getFieldID("zCoord"))
	);
}

void Vec3::setVector(const Ripterms::Maths::Vector3d& vector)
{
	if (!instance) return;
	env->SetDoubleField(instance, Vec3Class.getFieldID("xCoord"), vector.x);
	env->SetDoubleField(instance, Vec3Class.getFieldID("yCoord"), vector.y);
	env->SetDoubleField(instance, Vec3Class.getFieldID("zCoord"), vector.z);
}
