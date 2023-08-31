#pragma once
#include <iostream>
#include "../../../Ripterms/Ripterms.h"
#include "../../../Ripterms/Maths/Maths.h"
#include "../../../Ripterms/JavaClass/JavaClass.h"

class Object {
public:
	Object(jobject instance, JNIEnv* env = Ripterms::p_env);
	Object(const Object& other_Object);
	Object(JNIEnv* env = Ripterms::p_env);
	~Object();

	Object& operator=(const Object& other_Object);
	Object& operator=(jobject instance);
	operator jobject();

	void setInstance(jobject instance, JNIEnv* env = nullptr);
	bool isEqualTo(const Object& other_Object); //reference check
	bool instanceOf(const Ripterms::JavaClassV2::JClass& classRef);
	bool equals(const Object& other_Object); //content check
	bool isValid();
	void clear(); //delete ref
	const jobject& getInstance() const;
protected:
	inline static Ripterms::JavaClassV2 ObjectClass{ "java/lang/Object" };
	JNIEnv* env = Ripterms::p_env;
	jobject instance = nullptr;
};