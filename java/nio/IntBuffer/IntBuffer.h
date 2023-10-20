#pragma once
#include "../../lang/Object/Object.h"
#include "../../../Ripterms/Maths/Maths.h"

class IntBuffer : public Object {
public:
	using Object::Object;
	int get(int index);
	Ripterms::Maths::Matrix toMatrix(int lines, int columns);

protected:
	inline static Ripterms::JavaClassV2 IntBufferClass{ "java/nio/IntBuffer" };
};