#include "Modules.h"
#include "../../net/minecraft/network/play/server/S12PacketEntityVelocity/S12PacketEntityVelocity.h"

void Ripterms::Modules::VelocityPacket::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("VelocityPacket", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();

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
		ImGui::SliderFloat("motionX multiplier", &motionX_multiplier, -2.0f, 2.0f, "%.2f");
		ImGui::SliderFloat("motionY multiplier", &motionY_multiplier, -2.0f, 2.0f, "%.2f");
		ImGui::SliderFloat("motionZ multiplier", &motionZ_multiplier, -2.0f, 2.0f, "%.2f");
		ImGui::EndGroup();
	}
}

void Ripterms::Modules::VelocityPacket::onChannelRead0(JNIEnv* env, NetworkManager& this_networkManager, ChannelHandlerContext& context, Packet& packet, bool* cancel)
{
	if (!enabled) return;
	if (!packet.isValid()) return;
	if (!packet.instanceOf(Ripterms::JavaClassV2("net/minecraft/network/play/server/S12PacketEntityVelocity").get_jclass(env))) return;

	S12PacketEntityVelocity velocityPacket(packet, env);
	if (velocityPacket.getEntityID() != Minecraft::getTheMinecraft(env).getThePlayer().getEntityId()) return;
	velocityPacket.setMotionX(int(velocityPacket.getMotionX() * motionX_multiplier));
	velocityPacket.setMotionY(int(velocityPacket.getMotionY() * motionY_multiplier));
	velocityPacket.setMotionZ(int(velocityPacket.getMotionZ() * motionZ_multiplier));
}