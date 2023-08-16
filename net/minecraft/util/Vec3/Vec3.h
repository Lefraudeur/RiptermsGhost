#pragma once
#include "../../../../java/lang/Object/Object.h"

class Vec3 : public Object {
public:
	using Object::Object;

	Ripterms::Maths::Vector3d getVector() const;

	void setVector(const Ripterms::Maths::Vector3d& vector);
};