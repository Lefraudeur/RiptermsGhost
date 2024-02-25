#pragma once
#include <iostream>
#include "../../../Ripterms/Ripterms.h"
#include "../../../Ripterms/JavaClass/JavaClass.h"

class Object {
public:
	//make global if you want to preserve the reference accross local frames,
	//so if you want to reuse it in another Modules::run() call
	//becareful to set correct env when in hooks
	Object(jobject instance, JNIEnv* env = Ripterms::p_env, bool is_global=false);
	Object(const Object& other_Object);
	//becareful to set correct env when in hooks
	Object(JNIEnv* env = Ripterms::p_env, bool is_global = false);
	~Object();

	Object& operator=(const Object& other_Object);
	Object& operator=(jobject instance);
	operator jobject();

	void setInstance(jobject instance, JNIEnv* env = nullptr);
	bool isEqualTo(const Object& other_Object); //reference check
	bool instanceOf(jclass classRef);
	bool equals(const Object& other_Object); //content check
	bool isValid();
	void clear(); //delete ref
	const jobject& getInstance() const;
	Object& makeGlobal();
	void set_env(JNIEnv* env);
protected:
	inline static Ripterms::JavaClassV2 ObjectClass{ "java/lang/Object" };
	JNIEnv* env = Ripterms::p_env;
	jobject instance = nullptr;
	bool is_global = false;
};