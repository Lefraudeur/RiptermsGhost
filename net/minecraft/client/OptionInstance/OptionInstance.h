#pragma once
#include "../../../../java/lang/Object/Object.h"


class OptionInstance : public Object
{
public:
	using Object::Object;

	void setValue(const Object& value);
	Object getValue();

protected:
	inline static Ripterms::JavaClassV2 OptionInstanceClass{ "net/minecraft/client/OptionInstance" };
};