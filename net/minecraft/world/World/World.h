#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../../../java/util/List/List.h"

class World : public Object {
public:
	using Object::Object;
	virtual List getPlayerEntities();
protected:
	inline static Ripterms::JavaClassV2 WorldClass{ "net/minecraft/world/World" };
};