#include "Modules.h"

void Ripterms::Modules::Blink::run()
{
	static CTimer timer = std::chrono::milliseconds(300);
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
		List list = Ripterms::cache->EMPTY_MAP.get<List>(String("blink_packets"));
		list.clear(); //clear the previously intercepted packets
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
