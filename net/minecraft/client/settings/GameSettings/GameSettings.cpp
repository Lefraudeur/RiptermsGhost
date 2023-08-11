#include "GameSettings.h"

float GameSettings::getGammaSetting()
{
	if(!instance) return 0.0f;
	if (Ripterms::majorVersion == Ripterms::Version::MAJOR_1_16_5) {
		return (float)Ripterms::p_env->GetDoubleField(instance, Ripterms::classcache->GameSettingsClass.fields["gammaSetting"]);
	}
	return Ripterms::p_env->GetFloatField(instance, Ripterms::classcache->GameSettingsClass.fields["gammaSetting"]);
}

void GameSettings::setGammaSetting(float value)
{
	if (!instance) return;
	if (Ripterms::majorVersion == Ripterms::Version::MAJOR_1_16_5) {
		Ripterms::p_env->SetDoubleField(instance, Ripterms::classcache->GameSettingsClass.fields["gammaSetting"], (jdouble)value);
		return;
	}
	Ripterms::p_env->SetFloatField(instance, Ripterms::classcache->GameSettingsClass.fields["gammaSetting"], value);
}
