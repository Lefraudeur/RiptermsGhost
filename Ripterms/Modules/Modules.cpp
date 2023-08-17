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
	for (const std::pair<std::string, std::vector<IModule*>>& category : categories)
	{
		for (IModule* m : category.second)
		{
			m->run();
		}
	}
}

void Ripterms::Modules::cleanAll()
{
	bool should_disable = Ripterms::p_env != nullptr;
	for (const std::pair<std::string, std::vector<IModule*>>& category : categories)
	{
		for (IModule* m : category.second)
		{
			if (should_disable)m->disable();
			delete m;
		}
	}
}

void Ripterms::Modules::Blink::run()
{
	static bool prev_enabled = false;
	if (!enabled)
	{
		if (prev_enabled)
		{
			disable();
			prev_enabled = false;
		}
		return;
	}
	if (!prev_enabled)
	{
		List list = Ripterms::cache->EMPTY_MAP.get<List>(String("blink_packets"));
		list.clear();
		Ripterms::cache->EMPTY_MAP.put(String("blink_enabled"), String("1"));
		prev_enabled = true;
	}
}

void Ripterms::Modules::Blink::renderGUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Blink", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void Ripterms::Modules::Blink::disable()
{
	Ripterms::cache->EMPTY_MAP.put(String("blink_enabled"), String("0"));
	Ripterms::cache->EMPTY_MAP.put(String("blink_send"), String("1"));
}
