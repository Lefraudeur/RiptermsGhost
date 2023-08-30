#pragma once
#include "../../../../java/lang/Object/Object.h"

class MovingObjectType : public Object
{
public:
	using Object::Object;
	static MovingObjectType getType(const std::string& name, JNIEnv* env = Ripterms::p_env);
protected:
	inline static Ripterms::JavaClassV2 MovingObjectTypeClass{ "net/minecraft/util/MovingObjectPosition$MovingObjectType" };
};
