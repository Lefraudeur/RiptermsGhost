#pragma once

#pragma once
#include "../../lang/Object/Object.h"

class Map : public Object {
public:
	using Object::Object;
	Object put(const Object& key, const Object& value);
};