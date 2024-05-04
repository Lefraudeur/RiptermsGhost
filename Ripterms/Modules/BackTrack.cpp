#include "Modules.h"
#include "../Cache/Cache.h"
#include "../../net/minecraft/network/play/server/S19PacketEntityStatus/S19PacketEntityStatus.h"
#include "../../net/minecraft/network/protocol/game/ClientboundDamageEventPacket/ClientboundDamageEventPacket.h"
#include "../../net/minecraft/network/play/server/S14PacketEntity/S14PacketEntity.h"
#include "../../net/minecraft/network/play/server/S12PacketEntityVelocity/S12PacketEntityVelocity.h"

void Ripterms::Modules::BackTrack::renderGUI()
{
	ImGui::CustomSliderInt("Packet ReceiveDelay ms", &delay, 10, 1000, "%d", 0);
	ImGui::IOSToggle("disableOnHit", &disableOnHit);
	ImGui::IOSToggle("targetPacketsOnly", &targetPacketsOnly);
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
		if (targetPacketsOnly && !isTargetPositionPacket(packet, env)) return;
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
	saved_target_entity_id = entity.getEntityId();
	lag = true;
}

bool Ripterms::Modules::BackTrack::isAttackPacket(Packet& packet, JNIEnv* env)
{
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_19_4)
	{
		if (!packet.instanceOf(Ripterms::JavaClassV2("net/minecraft/network/protocol/game/ClientboundDamageEventPacket").get_jclass(env))) return false;
		ClientboundDamageEventPacket damagePacket(packet, env);
		return damagePacket.getEntityId() == Minecraft::getTheMinecraft(env).getThePlayer().getEntityId();
	}
	if (!packet.instanceOf(Ripterms::JavaClassV2("net/minecraft/network/play/server/S19PacketEntityStatus").get_jclass(env))) return false;
	S19PacketEntityStatus statusPacket(packet, env);
	if (statusPacket.getEntityId() != Minecraft::getTheMinecraft(env).getThePlayer().getEntityId()) return false;

	jbyte opcode = statusPacket.getLogicOpcode();

	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5)
		return Ripterms::is_any_of(opcode, 2, 33, 36, 37, 44);

	return opcode == (jbyte)2;
}

bool Ripterms::Modules::BackTrack::isTargetPositionPacket(Packet& packet, JNIEnv* env)
{
	if (packet.instanceOf(Ripterms::JavaClassV2("net/minecraft/network/play/server/S14PacketEntity").get_jclass(env)))
	{
		S14PacketEntity entityPacket(packet, env);
		return entityPacket.getEntityId() == saved_target_entity_id;
	}
	if (packet.instanceOf(Ripterms::JavaClassV2("net/minecraft/network/play/server/S12PacketEntityVelocity").get_jclass(env)))
	{
		S12PacketEntityVelocity velocityPacket(packet, env);
		return velocityPacket.getEntityID() == saved_target_entity_id;
	}
	if (packet.instanceOf(Ripterms::JavaClassV2("net/minecraft/network/play/server/S19PacketEntityStatus").get_jclass(env)))
	{
		S19PacketEntityStatus statusPacket(packet, env);
		return statusPacket.getEntityId() == saved_target_entity_id;
	}
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_19_4 && packet.instanceOf(Ripterms::JavaClassV2("net/minecraft/network/play/server/S19PacketEntityStatus").get_jclass(env)))
	{
		ClientboundDamageEventPacket damagePacket(packet, env);
		return damagePacket.getEntityId() == saved_target_entity_id;
	}
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