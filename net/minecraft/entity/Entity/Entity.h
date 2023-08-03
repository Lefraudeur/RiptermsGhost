#pragma once
#include "../../../../java/lang/Object/Object.h"

class Entity : public Object {
public:
	using Object::Object;
	static bool init();
	Ripterms::Maths::Vector3d getPosition();
	Ripterms::Maths::Vector2d getRotation();
	void setRotation(const Ripterms::Maths::Vector2d& yawPitch);
protected:
	inline static Ripterms::JavaClass* EntityClass = nullptr;
};