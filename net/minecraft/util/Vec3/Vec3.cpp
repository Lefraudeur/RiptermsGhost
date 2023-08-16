#include "Vec3.h"

Ripterms::Maths::Vector3d Vec3::getVector() const
{
	if (!instance) return Ripterms::Maths::Vector3d();
	return Ripterms::Maths::Vector3d(
		(float)Ripterms::p_env->GetDoubleField(instance, Ripterms::classcache->Vec3Class.fields["xCoord"]),
		(float)Ripterms::p_env->GetDoubleField(instance, Ripterms::classcache->Vec3Class.fields["yCoord"]),
		(float)Ripterms::p_env->GetDoubleField(instance, Ripterms::classcache->Vec3Class.fields["zCoord"])
	);
}

void Vec3::setVector(const Ripterms::Maths::Vector3d& vector)
{
	if (!instance) return;
	Ripterms::p_env->SetDoubleField(instance, Ripterms::classcache->Vec3Class.fields["xCoord"], vector.x);
	Ripterms::p_env->SetDoubleField(instance, Ripterms::classcache->Vec3Class.fields["yCoord"], vector.y);
	Ripterms::p_env->SetDoubleField(instance, Ripterms::classcache->Vec3Class.fields["zCoord"], vector.z);
}
