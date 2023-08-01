#pragma once
#include "../../lang/Object/Object.h"
#include <vector>

class Collection : public Object {
public:
	using Object::Object;
	static bool init();
	template<class T>
	std::vector<T> toArray();
protected:
	inline static Ripterms::JavaClass CollectionClass{};
};

template<class T>
inline std::vector<T> Collection::toArray()
{
	if (!this->instance) return {};
	jobjectArray array = (jobjectArray)Ripterms::p_env->CallObjectMethod(instance, CollectionClass.methods["toArray"]);
	if (!array) return {};
	jsize size = Ripterms::p_env->GetArrayLength(array);
	std::vector<T> vector(size);
	for (jsize i = 0; i < size; ++i) {
		vector.push_back(T(Ripterms::p_env->GetObjectArrayElement(array, i)));
	}
	Ripterms::p_env->DeleteLocalRef(array);
	return vector;
}
