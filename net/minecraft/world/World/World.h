#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../entity/player/EntityPlayer/EntityPlayer.h"

class World : public Object {
public:
	using Object::Object;
	static bool init();
	std::vector<EntityPlayer> getPlayerEntities();
protected:
	inline static Ripterms::JavaClass WorldClass{};
};