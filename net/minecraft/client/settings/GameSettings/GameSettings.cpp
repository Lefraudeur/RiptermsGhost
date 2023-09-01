#include "GameSettings.h"

float GameSettings::getGammaSetting()
{
	if(!instance) return 0.0f;
	if (Ripterms::majorVersion == Ripterms::Version::MAJOR_1_16_5) {
		return (float)env->GetDoubleField(instance, GameSettingsClass.getFieldID("gammaSetting"));
	}
	return env->GetFloatField(instance, GameSettingsClass.getFieldID("gammaSetting"));
}

KeyBinding GameSettings::getKeyBindSneak()
{
	if (!instance) return KeyBinding(env);
	return KeyBinding(env->GetObjectField(instance, GameSettingsClass.getFieldID("keyBindSneak")), env);
}

KeyBinding GameSettings::getKeyBindSprint()
{
	if (!instance) return KeyBinding(env);
	return KeyBinding(env->GetObjectField(instance, GameSettingsClass.getFieldID("keyBindSprint")), env);
}

void GameSettings::setGammaSetting(float value)
{
	if (!instance) return;
	if (Ripterms::majorVersion == Ripterms::Version::MAJOR_1_16_5) {
		env->SetDoubleField(instance, GameSettingsClass.getFieldID("gammaSetting"), (jdouble)value);
		return;
	}
	env->SetFloatField(instance, GameSettingsClass.getFieldID("gammaSetting"), value);
}
