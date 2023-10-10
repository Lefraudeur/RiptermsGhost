#include "Event.h"
#include "../Modules/Modules.h"

Ripterms::Event::Event(JNIEnv* env, int mask)
{
	if (mask >= 13371337)
	{
		this->type = (Type)mask;
		this->env = env;
	}
	else this->type = UNKNOWN;
}

void Ripterms::Event::dispatch()
{
	for (auto& category : Ripterms::Modules::categories)
	{
		for (auto module : category.second)
		{
			module->onEvent(this);
		}
	}
}

bool Ripterms::Event::isEvent()
{
	return type != UNKNOWN;
}

void Ripterms::Event::cancel()
{
	isCanceled = true;
}
