#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../../../java/util/Map/Map.h"

class PlayerUsageSnooper : public Object {
public:
	using Object::Object;
	Map getSnooperStats();
};