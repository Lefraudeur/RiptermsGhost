#pragma once
#include "../../lang/Object/Object.h"
#include <vector>

class Collection : public Object {
public:
	using Object::Object;
	void clear();
	bool add(const Object& element);
	template<class T>
	std::vector<T> toVector();
protected:
	inline static Ripterms::JavaClassV2 CollectionClass{ "java/util/Collection" };
};

template<class T>
inline std::vector<T> Collection::toVector()
{
	if (!this->instance) return {};
	jobjectArray array = (jobjectArray)env->CallObjectMethod(instance, CollectionClass.getMethodID("toArray"));
	if (!array) return {};
	jsize size = env->GetArrayLength(array);
	if (size == 0) return {};
	std::vector<T> vector(size);
	for (jsize i = 0; i < size; ++i) {
		vector.push_back(T(env->GetObjectArrayElement(array, i), env));
	}
	env->DeleteLocalRef(array);
	return vector;
}
