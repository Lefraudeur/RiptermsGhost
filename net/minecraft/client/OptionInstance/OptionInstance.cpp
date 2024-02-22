#include "OptionInstance.h"

void OptionInstance::setValue(const Object& value)
{
	if (!instance) return;
	env->SetObjectField(instance, OptionInstanceClass.getFieldID("value"), value.getInstance());
}

Object OptionInstance::getValue()
{
	if (!instance)
		return Object(nullptr, env);
	return Object(env->GetObjectField(instance, OptionInstanceClass.getFieldID("value")), env);
}
