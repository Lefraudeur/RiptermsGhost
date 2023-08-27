#pragma once
#include "../Collection/Collection.h"

class List : public Collection {
public:
	using Collection::Collection;
	static List newObject(JNIEnv* env = Ripterms::p_env);
protected:
	inline static Ripterms::JavaClassV2 ListClass{ "java/util/List" };
};