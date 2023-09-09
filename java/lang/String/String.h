#pragma once
#include "../Object/Object.h"

class String : public Object {
public:
	using Object::Object;
	String(const std::string& str, JNIEnv* env = Ripterms::p_env);
	String(const char* str, JNIEnv* env = Ripterms::p_env);
	int size() const;
	int modifiedUTF8size() const;
	std::string toStdString() const;
protected:
	inline static Ripterms::JavaClassV2 StringClass{ "java/lang/String" };
};
