#pragma once
#include "../Object/Object.h"

class System : public Object {
public:
	using Object::Object;
	static void gc(JNIEnv* env = Ripterms::p_env);
protected:
	inline static Ripterms::JavaClassV2 SystemClass{ "java/lang/System" };
};
