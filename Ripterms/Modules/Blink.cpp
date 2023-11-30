#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>

void Ripterms::Modules::Blink::run()
{
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
	onSendPacketNoEvent = true;
	for (Packet& packet : packets)
	{
		//TODO: send the packets here
	}
	packets.clear();
	onSendPacketNoEvent = false;
}

void Ripterms::Modules::Blink::onSendPacket(JNIEnv* env, Packet& packet, bool* cancel)
{
	if (!enabled)
	{
		if (!packets.empty())
			disable();
		return;
	}
	*cancel = true;
	packets.push_back(Packet(packet, env, true));
}
