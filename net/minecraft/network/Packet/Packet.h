#pragma once
#include "../../../../java/lang/Object/Object.h"

class Packet : public Object
{
public:
	using Object::Object;
protected:
	inline static Ripterms::JavaClassV2 PacketClass{ "net/minecraft/network/Packet" };
};