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
	sendPackets(Ripterms::p_env);
}

void Ripterms::Modules::Blink::onAddToSendQueue(JNIEnv* env, NetHandlerPlayClient& sendQueue, Packet& packet, bool* cancel)
{
	if (!enabled)
	{
		if (!packets.empty())
			sendPackets(env);
		return;
	}
	*cancel = true;
	packets.push_back(Packet(packet, env, true));
}

void Ripterms::Modules::Blink::sendPackets(JNIEnv* env)
{
	onAddToSendQueueNoEvent = true;
	Minecraft theMinecraft = Minecraft::getTheMinecraft(env);
	EntityPlayerSP thePlayer = theMinecraft.getThePlayer();
	NetHandlerPlayClient sendQueue = thePlayer.getSendQueue();
	for (Packet& packet : packets)
	{
		sendQueue.addToSendQueue(packet);
	}
	packets.clear();
	onAddToSendQueueNoEvent = false;
}
