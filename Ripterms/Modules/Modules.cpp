#include "Modules.h"
#include <bitset>

void Ripterms::Modules::IModule::run()
{
}

void Ripterms::Modules::IModule::renderGUI()
{
}

void Ripterms::Modules::IModule::disable()
{
}

void Ripterms::Modules::IModule::onEvent(Event* event)
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

void Ripterms::Modules::FastPlace::run()
{
	if (!enabled || !GetAsyncKeyState(VK_RBUTTON)) return;
	if (Ripterms::cache->theMinecraft.getRightClickDelayTimer() == 4)
	{
		Ripterms::cache->theMinecraft.setRightClickDelayTimer(tickDelay);
	}
}

void Ripterms::Modules::FastPlace::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Fast Place", &enabled);
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("fastplaceopt", ImGuiDir_Down)) display_options = !display_options;
	if (display_options)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		{
			ImGui::SliderInt("Tick Delay", &tickDelay, 0, 3);
		}
		ImGui::EndGroup();
	}
	ImGui::PopStyleVar();
}



void Ripterms::Modules::Xray::run()
{
	static Timer timer = std::chrono::milliseconds(300);
	if (GetAsyncKeyState(keyBind) && timer.isElapsed() && GetActiveWindow() == Ripterms::window)
	{
		enabled = !enabled;
	}
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
		Ripterms::cache->EMPTY_MAP.put(String("xray_enabled"), String("1"));
		prev_enabled = true;
	}
}

void Ripterms::Modules::Xray::renderGUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Xray", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void Ripterms::Modules::Xray::disable()
{
	Ripterms::cache->EMPTY_MAP.put(String("xray_enabled"), String("0"));
}