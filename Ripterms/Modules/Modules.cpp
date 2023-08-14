#include "Modules.h"

void Ripterms::Modules::IModule::run()
{
}

void Ripterms::Modules::IModule::renderGUI()
{
}

void Ripterms::Modules::IModule::disable()
{
}

void Ripterms::Modules::runAll()
{
	IModule* allModules[(sizeof(combat) + sizeof(misc)) / sizeof(IModule*)] = { nullptr };
	memcpy(allModules, combat, sizeof(combat));
	memcpy(allModules + sizeof(combat) / sizeof(IModule*), misc, sizeof(misc));

	for (IModule* module : allModules)
	{
		module->run();
	}
}

void Ripterms::Modules::cleanAll()
{
	IModule* allModules[(sizeof(combat) + sizeof(misc)) / sizeof(IModule*)] = { nullptr };
	memcpy(allModules, combat, sizeof(combat));
	memcpy(allModules + sizeof(combat) / sizeof(IModule*), misc, sizeof(misc));

	for (IModule* module : allModules)
	{
		if (Ripterms::p_env) module->disable();
		delete module;
	}
}
