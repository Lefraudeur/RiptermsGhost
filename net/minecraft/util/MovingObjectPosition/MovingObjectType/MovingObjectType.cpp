#include "MovingObjectType.h"

MovingObjectType MovingObjectType::getType(const std::string& name, JNIEnv* env)
{
	return MovingObjectType
	(
		env->GetStaticObjectField
		(
			MovingObjectTypeClass.get_jclass(env),
			MovingObjectTypeClass.getFieldID(name)
		), env
	);
}
