#include "Event.h"
#include "../Modules/Modules.h"

Ripterms::Event::Event(JNIEnv* env, int mask)
{
	if (mask >= 13371337)
	{
		this->type = (Type)mask;
		this->env = env;
		Ripterms::JavaClassV2 ThreadContext("org/apache/logging/log4j/ThreadContext");
		this->EMPTY_MAP.setInstance(env->GetStaticObjectField(ThreadContext.getJClass(env), ThreadContext.getFieldID("EMPTY_MAP")), env);
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
	this->EMPTY_MAP.put(String("cancel" + std::to_string((int)type), env), String("1", env));
}
