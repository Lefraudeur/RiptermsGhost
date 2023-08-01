#pragma once
#include "../../../Ripterms/Ripterms.h"

class Object {
public:
	Object(jobject instance);
	Object(const Object& other_Object);
	Object();
	virtual Object& operator=(const Object& other_Object);
	virtual Object& operator=(jobject instance);
	virtual bool operator==(const Object& other_Object);
	virtual bool operator!();
	virtual ~Object();
	static bool init();
protected:
	inline static Ripterms::JavaClass ObjectClass{};
	jobject instance = nullptr;
};