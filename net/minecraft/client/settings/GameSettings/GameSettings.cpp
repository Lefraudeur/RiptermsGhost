#include "GameSettings.h"

double GameSettings::getGammaSetting()
{
	if(!instance)
		return 0.0;
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5)
		return env->GetDoubleField(instance, GameSettingsClass.getFieldID("gammaSetting"));
	return env->GetFloatField(instance, GameSettingsClass.getFieldID("gammaSetting"));
}

KeyBinding GameSettings::getKeyBindSneak()
{
	if (!instance)
		return KeyBinding(env);
	return KeyBinding(env->GetObjectField(instance, GameSettingsClass.getFieldID("keyBindSneak")), env);
}

KeyBinding GameSettings::getKeyBindSprint()
{
	if (!instance)
		return KeyBinding(env);
	return KeyBinding(env->GetObjectField(instance, GameSettingsClass.getFieldID("keyBindSprint")), env);
}

void GameSettings::setGammaSetting(double value)
{
	if (!instance)
		return;
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5)
	{
		env->SetDoubleField(instance, GameSettingsClass.getFieldID("gammaSetting"), (jdouble)value);
		return;
	}
	env->SetFloatField(instance, GameSettingsClass.getFieldID("gammaSetting"), (jfloat)value);
}
