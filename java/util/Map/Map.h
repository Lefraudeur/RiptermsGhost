#pragma once

#pragma once
#include "../../lang/Object/Object.h"

class Map : public Object {
public:
	using Object::Object;
	Object put(const Object& key, const Object& value);
	template<class T>
	T get(const Object& key);
};

template<class T>
inline T Map::get(const Object& key)
{
	if (!instance) return T();
	return T(Ripterms::p_env->CallObjectMethod(instance, Ripterms::classcache->MapClass.methods["get"], key.getInstance()));
}