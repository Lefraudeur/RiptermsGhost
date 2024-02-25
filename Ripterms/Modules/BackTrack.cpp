#include "Modules.h"
#include "../Cache/Cache.h"
#include "../../net/minecraft/network/play/server/S19PacketEntityStatus/S19PacketEntityStatus.h"

void Ripterms::Modules::BackTrack::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("BackTrack", &enabled);
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("BackTrackOpt", ImGuiDir_Down))
		display_options = !display_options;
	if (display_options)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		ImGui::SliderInt("Packet ReceiveDelay ms", &delay, 10, 1000, "%d");
		ImGui::Checkbox("disableOnHit", &disableOnHit);
		ImGui::EndGroup();
	}

	ImGui::PopStyleVar();
}

void Ripterms::Modules::BackTrack::onChannelRead0(JNIEnv* env, NetworkManager& this_networkManager, ChannelHandlerContext& context, Packet& packet, bool* cancel)
{
	static Ripterms::CTimer timer{ std::chrono::milliseconds(delay) };
	static int prev_delay = delay;
	if (!enabled)
	{
		lag = false;
		if (!packets.empty()) sendPackets(env);
		return;
	}
	if (lag)
	{
		if (!packet.isValid()) return;
		if (timer.isElapsed() || (disableOnHit && isAttackPacket(packet, env)))
		{
			lag = false;
			if (!packets.empty()) sendPackets(env);
			return;
		}
		*cancel = true;
		addPacket({ this_networkManager , context,  packet });
	}
	if (prev_delay != delay)
	{
		timer.setEvery(std::chrono::milliseconds(delay));
		prev_delay = delay;
	}
}

void Ripterms::Modules::BackTrack::onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel)
{
	if (!enabled) return;
	lag = true;
}

bool Ripterms::Modules::BackTrack::isAttackPacket(Packet& packet, JNIEnv* env)
{
	if (!packet.instanceOf(Ripterms::JavaClassV2("net/minecraft/network/play/server/S19PacketEntityStatus").get_jclass(env))) return false;
	S19PacketEntityStatus statusPacket(packet, env, true);
	if (statusPacket.getEntityId() != Minecraft::getTheMinecraft(env).getThePlayer().getEntityId()) return false;
	if (statusPacket.getLogicOpcode() == (jbyte)2)
		return true;
	return false;
}

void Ripterms::Modules::BackTrack::sendPackets(JNIEnv* env)
{
	onChannelRead0NoEvent = true;
	std::lock_guard lock{ packets_mutex };
	for (PacketData& data : packets)
	{
		data.this_networkManager.set_env(env);
		data.this_networkManager.channelRead0(data.context, data.packet);
	}
	packets.clear();
	onChannelRead0NoEvent = false;
}

void Ripterms::Modules::BackTrack::addPacket(const PacketData& data)
{
	std::lock_guard lock{ packets_mutex };
	packets.push_back(data);
}