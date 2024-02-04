#pragma once
#include "../../../java/lang/Object/Object.h"
#include "../../../java/lang/String/String.h"

class Block : public Object
{
public:
	using Object::Object;
	String toString();
	std::string getName();
protected:
	inline static Ripterms::JavaClassV2 BlockClass{ "net/minecraft/block/Block" };
};