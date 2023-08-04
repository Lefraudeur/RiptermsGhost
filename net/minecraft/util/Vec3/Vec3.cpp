#include "Vec3.h"

Ripterms::Maths::Vector3d Vec3::getVector()
{
	if (!instance) return Ripterms::Maths::Vector3d();
	return Ripterms::Maths::Vector3d(
		(float)Ripterms::p_env->GetDoubleField(instance, Ripterms::classcache->Vec3Class.fields["xCoord"]),
		(float)Ripterms::p_env->GetDoubleField(instance, Ripterms::classcache->Vec3Class.fields["yCoord"]),
		(float)Ripterms::p_env->GetDoubleField(instance, Ripterms::classcache->Vec3Class.fields["zCoord"])
	);
}
