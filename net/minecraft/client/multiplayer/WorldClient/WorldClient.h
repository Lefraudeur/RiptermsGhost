#pragma once
#include "../../../world/World/World.h"

class WorldClient : public World {
public:
	using World::World;
	List getPlayerEntities() override;
};
