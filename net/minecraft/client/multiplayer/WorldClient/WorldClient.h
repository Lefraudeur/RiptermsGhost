#pragma once
#include "../../../world/World/World.h"

class WorldClient : public World {
public:
	using World::World;
	static bool init();
protected:
	inline static Ripterms::JavaClass WorldClientClass{};
};
