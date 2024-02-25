#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>
#include "../Hook/JavaHook.h"

void Ripterms::Modules::Blink::run()
{
}

void Ripterms::Modules::Blink::renderGUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Blink", &enabled);
	ImGui::PopStyleVar();

	static bool display_options = false;
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("aimopt", ImGuiDir_Down))
		display_options = !display_options;
	if (display_options)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		ImGui::Checkbox("delay sent", &delay_sent_packets);
		ImGui::Checkbox("stop received", &delay_received_packets);
		ImGui::EndGroup();
	}

	ImGui::PopStyleVar();
}

void Ripterms::Modules::Blink::disable()
{
	if (!Ripterms::p_env || !Ripterms::cache || !Ripterms::cache->is_valid) return;
	sendPackets(Ripterms::cache->sendQueue);
}

void Ripterms::Modules::Blink::onAddToSendQueue(JNIEnv* env, NetHandlerPlayClient& sendQueue, Packet& packet, bool* cancel)
{
	if (!enabled || !delay_sent_packets)
	{
		if (!packets.empty())
			sendPackets(sendQueue);
		return;
	}
	if (!packet.isValid()) return;
	*cancel = true;
	packets.push_back(packet);
}

void Ripterms::Modules::Blink::onChannelRead0(JNIEnv* env, NetworkManager& this_networkManager, ChannelHandlerContext& context, Packet& packet, bool* cancel)
{
	if (!enabled || !delay_received_packets) return;
	*cancel = true;
}

void Ripterms::Modules::Blink::sendPackets(NetHandlerPlayClient& sendQueue)
{
	onAddToSendQueueNoEvent = true;
	for (Packet& packet : packets)
		sendQueue.addToSendQueue(packet);
	packets.clear();
	onAddToSendQueueNoEvent = false;
}
