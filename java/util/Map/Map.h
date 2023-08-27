#pragma once

#pragma once
#include "../../lang/Object/Object.h"

class Map : public Object {
public:
	using Object::Object;
	Object put(const Object& key, const Object& value);
	template<class T>
	T get(const Object& key);
protected:
	inline static Ripterms::JavaClassV2 MapClass{ "java/util/Map" };
};

template<class T>
inline T Map::get(const Object& key)
{
	if (!instance) return T();
	return T(env->CallObjectMethod(instance, MapClass.getMethodID("get"), key.getInstance()), env);
}