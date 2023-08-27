#include "MovingObjectType.h"

MovingObjectType MovingObjectType::getType(const std::string& name, JNIEnv* env)
{
	return MovingObjectType
	(
		env->GetStaticObjectField
		(
			MovingObjectTypeClass.getJClass(),
			MovingObjectTypeClass.getFieldID(name)
		), env
	);
}
