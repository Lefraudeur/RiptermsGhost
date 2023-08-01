#pragma once
#include "../../../Ripterms/Ripterms.h"

class Object {
public:
	Object(jobject instance);
	Object(const Object& other_Object);
	Object();
	Object& operator=(const Object& other_Object);
	Object& operator=(jobject instance);
	bool operator==(const Object& other_Object);
	~Object();
	static bool init();
protected:
	inline static Ripterms::JavaClass ObjectClass{};
	jobject instance = nullptr;
};