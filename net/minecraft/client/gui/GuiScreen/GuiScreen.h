#pragma once
#include "../../../../../java/lang/Object/Object.h"

class GuiScreen : public Object
{
public:
	using Object::Object;
protected:
	inline static Ripterms::JavaClassV2 GuiScreenClass{ "net/minecraft/client/gui/GuiScreen" };
};