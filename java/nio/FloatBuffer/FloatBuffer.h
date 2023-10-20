#pragma once
#include "../../lang/Object/Object.h"
#include "../../../Ripterms/Maths/Maths.h"

class FloatBuffer : public Object {
public:
	using Object::Object;
	float get(int index);
	Ripterms::Maths::Matrix toMatrix(int lines, int columns);

protected:
	inline static Ripterms::JavaClassV2 FloatBufferClass{ "java/nio/FloatBuffer" };
};
