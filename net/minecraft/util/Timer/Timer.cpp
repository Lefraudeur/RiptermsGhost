#include "Timer.h"

float Timer::getRenderPartialTicks()
{
	if (!instance) return 0.0f;
	return env->GetFloatField(instance, TimerClass.getFieldID("renderPartialTicks"));
}