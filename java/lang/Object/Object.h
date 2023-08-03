#pragma once
#include "../../../Ripterms/Ripterms.h"
#include "../../../Ripterms/Maths/Maths.h"

class Object {
public:
	Object(jobject instance);
	Object(const Object& other_Object);
	Object();
	Object& operator=(const Object& other_Object);
	Object& operator=(jobject instance);
	bool isEqualTo(const Object& other_Object);
	bool operator!();
	bool isValid();
	~Object();
	void clear();
	static bool init();
protected:
	inline static Ripterms::JavaClass* ObjectClass = nullptr;
	jobject instance = nullptr;
};