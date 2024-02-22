#pragma once
#include "../Object/Object.h"

class Double : public Object {
public:
	using Object::Object;

	static Double newObject(double value, JNIEnv* env = Ripterms::p_env);
	double doubleValue();
protected:
	inline static Ripterms::JavaClassV2 DoubleClass{ "java/lang/Double" };
};