#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../entity/player/EntityPlayer/EntityPlayer.h"

class World : public Object {
public:
	using Object::Object;
	virtual std::vector<EntityPlayer> getPlayerEntities();
};