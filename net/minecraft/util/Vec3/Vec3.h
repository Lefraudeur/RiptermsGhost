#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../../../Ripterms/Maths/Maths.h"

class Vec3 : public Object {
public:
	using Object::Object;

	Ripterms::Maths::Vector3d getVector() const;

	void setVector(const Ripterms::Maths::Vector3d& vector);
protected:
	inline static Ripterms::JavaClassV2 Vec3Class{ "net/minecraft/util/Vec3" };
};