#pragma once
#include "../../../../../java/lang/Object/Object.h"
#include "../../../entity/player/EntityPlayer/EntityPlayer.h"

class PlayerControllerMP : public Object
{
public:
	using Object::Object;
	void attackEntity(const EntityPlayer& player, const Entity& targetEntity);
protected:
	inline static Ripterms::JavaClassV2 PlayerControllerMPClass{ "net/minecraft/client/multiplayer/PlayerControllerMP" };
};