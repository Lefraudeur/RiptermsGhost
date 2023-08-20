#include "MovingObjectType.h"

MovingObjectType MovingObjectType::getType(const std::string& name)
{
	return MovingObjectType
	(
		Ripterms::p_env->GetStaticObjectField
		(
			Ripterms::classcache->MovingObjectTypeClass.javaClass,
			Ripterms::classcache->MovingObjectTypeClass.fields[name]
		)
	);
}
