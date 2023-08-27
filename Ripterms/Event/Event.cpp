#include "Event.h"
#include "../Modules/Modules.h"

Event::Event(JNIEnv* env, int mask)
{
	std::unordered_map<int, Type>::iterator pos = events.find(mask);
	if (pos != events.end())
	{
		this->type = pos->second;
	}
	else
	{
		this->type = UNKNOWN;
		return;
	}
	this->env = env;
	Ripterms::JavaClassV2 ThreadContext("org/apache/logging/log4j/ThreadContext");
	this->EMPTY_MAP = env->GetStaticObjectField(ThreadContext.getJClass(env), ThreadContext.getFieldID("EMPTY_MAP"));
}

void Event::dispatch()
{
	for (auto& category : Ripterms::Modules::categories)
	{
		for (auto module : category.second)
		{
			module->onEvent(this);
		}
	}
}

bool Event::isEvent()
{
	return type != UNKNOWN;
}

void Event::cancel()
{
	isCanceled = true;
	this->EMPTY_MAP.put(String("cancel"), String("1"));
}
