#pragma once
#include "../../../Ripterms/Ripterms.h"

class Object {
public:
	Object(jobject instance);
	Object(Object& other_Object);
	Object();
	~Object();
	static bool init();
private:
	inline static Ripterms::JavaClass ObjectClass;
	jobject instance = nullptr;
};