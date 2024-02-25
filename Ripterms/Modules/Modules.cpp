#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>
#include "../../net/minecraft/network/play/client/C03PacketPlayer/C03PacketPlayer.h"
#include "../Hook/JavaHook.h"
#include "../../net/minecraft/network/play/server/S12PacketEntityVelocity/S12PacketEntityVelocity.h"
#include "../../net/minecraft/network/play/server/S19PacketEntityStatus/S19PacketEntityStatus.h"

void Ripterms::Modules::IModule::run()
{
}

void Ripterms::Modules::IModule::renderGUI()
{
}

void Ripterms::Modules::IModule::render()
{
}

void Ripterms::Modules::IModule::disable()
{
	enabled = false;
}

void Ripterms::Modules::IModule::onAddToSendQueue(JNIEnv* env, NetHandlerPlayClient& sendQueue, Packet& packet, bool* cancel)
{
}

void Ripterms::Modules::IModule::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
}

void Ripterms::Modules::IModule::onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel)
{
}

void Ripterms::Modules::IModule::onGetMouseOver(JNIEnv* env, float partialTicks, bool* cancel)
{
}

void Ripterms::Modules::IModule::onGetClientModName(JNIEnv* env, bool* cancel)
{
}

void Ripterms::Modules::IModule::onChannelRead0(JNIEnv* env, NetworkManager& this_networkManager, ChannelHandlerContext& context, Packet& packet, bool* cancel)
{
}

void Ripterms::Modules::IModule::onClickMouse(JNIEnv* env, Minecraft& theMinecraft, bool* cancel)
{
}

void Ripterms::Modules::IModule::onKeyBind(int keyBind)
{
	if (!keyBind || keyBind != this->keyBind) return;
	enabled = !enabled;
}

static void addToSendQueue_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	if (Ripterms::Modules::IModule::onAddToSendQueueNoEvent) return;
	JNIEnv* env = thread->get_env();

	NetHandlerPlayClient sendQueue(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env, true);
	Packet packet(Ripterms::JavaHook::get_jobject_param_at(frame, 1), env, true);

	for (Ripterms::Modules::Category& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.modules)
		{
			Ripterms::JNIFrame frame(env);
			module->onAddToSendQueue(env, sendQueue, packet, cancel);
		}
	}

	return;
}

static void getMouseOver_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();

	float f = Ripterms::JavaHook::get_primitive_param_at<float>(frame, 1);
	for (Ripterms::Modules::Category& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.modules)
		{
			module->onGetMouseOver(env, f, cancel);
		}
	}
	return;
}

static void attackTargetEntityWithCurrentItem_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();

	EntityPlayer this_player(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env, true);
	Entity entity(Ripterms::JavaHook::get_jobject_param_at(frame, 1), env, true);

	for (Ripterms::Modules::Category& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.modules)
		{
			Ripterms::JNIFrame frame(env);
			module->onAttackTargetEntityWithCurrentItem(env, this_player, entity, cancel);
		}
	}

	return;
}

static void onUpdateWalkingPlayer_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();

	EntityPlayerSP this_player(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env, true);

	for (Ripterms::Modules::Category& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.modules)
		{
			Ripterms::JNIFrame frame(env);
			module->onUpdateWalkingPlayer(env, this_player, cancel);
		}
	}

	return;
}

static void getClientModName_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();

	for (Ripterms::Modules::Category& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.modules)
		{
			Ripterms::JNIFrame frame(env);
			module->onGetClientModName(env, cancel);
		}
	}
	return;
}

static void channelRead0_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env || Ripterms::Modules::IModule::onChannelRead0NoEvent) return;
	JNIEnv* env = thread->get_env();

	NetworkManager this_networkManager(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env, true);
	ChannelHandlerContext context(Ripterms::JavaHook::get_jobject_param_at(frame, 1), env, true);
	Packet packet(Ripterms::JavaHook::get_jobject_param_at(frame, 2), env, true);

	for (Ripterms::Modules::Category& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.modules)
		{
			Ripterms::JNIFrame frame(env);
			module->onChannelRead0(env, this_networkManager, context, packet, cancel);
		}
	}
	return;
}

static void clickMouse_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();

	Minecraft theMinecraft(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env, true);

	for (Ripterms::Modules::Category& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.modules)
		{
			Ripterms::JNIFrame frame(env);
			module->onClickMouse(env, theMinecraft, cancel);
		}
	}
	return;
}

void Ripterms::Modules::setupEventHooks()
{
	Ripterms::JavaClassV2 NetHandlerPlayClient("net/minecraft/client/network/NetHandlerPlayClient");
	jmethodID addToSendQueue = NetHandlerPlayClient.getMethodID("addToSendQueue");
	Ripterms::JavaHook::hook(addToSendQueue, addToSendQueue_callback);

	Ripterms::JavaClassV2 EntityRenderer("net/minecraft/client/renderer/EntityRenderer");
	jmethodID getMouseOver = EntityRenderer.getMethodID("getMouseOver");
	Ripterms::JavaHook::hook(getMouseOver, getMouseOver_callback);

	Ripterms::JavaClassV2 EntityPlayer("net/minecraft/entity/player/EntityPlayer");
	jmethodID attackTargetEntityWithCurrentItem = EntityPlayer.getMethodID("attackTargetEntityWithCurrentItem");
	Ripterms::JavaHook::hook(attackTargetEntityWithCurrentItem, attackTargetEntityWithCurrentItem_callback);

	Ripterms::JavaClassV2 EntityPlayerSP
	(
		(Ripterms::version.type == Ripterms::Version::MAJOR_1_7_10 ? "net/minecraft/client/entity/EntityClientPlayerMP" 
			: "net/minecraft/client/entity/EntityPlayerSP")
	);
	jmethodID onUpdateWalkingPlayer = EntityPlayerSP.getMethodID("onUpdateWalkingPlayer");
	Ripterms::JavaHook::hook(onUpdateWalkingPlayer, onUpdateWalkingPlayer_callback);

	Ripterms::JavaClassV2 ClientBrandRetriever("net/minecraft/client/ClientBrandRetriever");
	jmethodID getClientModName = ClientBrandRetriever.getMethodID("getClientModName");
	Ripterms::JavaHook::hook(getClientModName, getClientModName_callback);

	Ripterms::JavaClassV2 NetworkManager("net/minecraft/network/NetworkManager");
	jmethodID channelRead0 = NetworkManager.getMethodID("channelRead0");
	Ripterms::JavaHook::hook(channelRead0, channelRead0_callback);

	Ripterms::JavaClassV2 Minecraft("net/minecraft/client/Minecraft");
	jmethodID clickMouse = Minecraft.getMethodID("clickMouse");
	Ripterms::JavaHook::hook(clickMouse, clickMouse_callback);
}

void Ripterms::Modules::runAll()
{
	for (Ripterms::Modules::Category& category : Ripterms::Modules::categories)
	{
		for (IModule* m : category.modules)
		{
			m->run();
		}
	}
}

void Ripterms::Modules::cleanAll()
{
	for (Ripterms::Modules::Category& category : Ripterms::Modules::categories)
	{
		for (IModule* m : category.modules)
		{
			m->disable();
		}
	}
}


void Ripterms::Modules::ESP::render()
{
}

void Ripterms::Modules::AttackLag::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("AttackLag", &enabled);
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
		ImGui::SliderInt("Packet ReceiveDelay ms", &delay, 10, 1000, "%d");
		ImGui::Checkbox("disableOnHit", &disableOnHit);
		ImGui::EndGroup();
	}

	ImGui::PopStyleVar();
}

void Ripterms::Modules::AttackLag::onChannelRead0(JNIEnv* env, NetworkManager& this_networkManager, ChannelHandlerContext& context, Packet& packet, bool* cancel)
{
	static Ripterms::CTimer timer{ std::chrono::milliseconds(delay) };
	static int prev_delay = delay;
	if (!enabled)
	{
		lag = false;
		if (!packets.empty()) sendPackets();
		return;
	}
	if (lag)
	{
		if (timer.isElapsed() || ( disableOnHit && isAttackPacket(packet, env) ))
		{
			lag = false;
			if (!packets.empty()) sendPackets();
			return;
		}
		*cancel = true;
		addPacket({this_networkManager , context,  packet});
	}
	if (prev_delay != delay)
	{
		timer.setEvery(std::chrono::milliseconds(delay));
		prev_delay = delay;
	}
}

void Ripterms::Modules::AttackLag::onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel)
{
	if (!enabled) return;
	lag = true;
}

bool Ripterms::Modules::AttackLag::isAttackPacket(Packet& packet, JNIEnv* env)
{
	if (!packet.instanceOf(Ripterms::JavaClassV2("net/minecraft/network/play/server/S19PacketEntityStatus").get_jclass(env))) return false;
	S19PacketEntityStatus statusPacket(packet, env, true);
	if (statusPacket.getEntityId() != Minecraft::getTheMinecraft(env).getThePlayer().getEntityId()) return false;
	if (statusPacket.getLogicOpcode() == (jbyte)2)
		return true;
	return false;
}

void Ripterms::Modules::AttackLag::sendPackets()
{
	onChannelRead0NoEvent = true;
	std::lock_guard lock{ packets_mutex };
	for (PacketData& data : packets)
		data.this_networkManager.channelRead0(data.context, data.packet);
	packets.clear();
	onChannelRead0NoEvent = false;
}

void Ripterms::Modules::AttackLag::addPacket(const PacketData& data)
{
	std::lock_guard lock{ packets_mutex };
	packets.push_back(data);
}

void Ripterms::Modules::NoMiss::renderGUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("NoMiss", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void Ripterms::Modules::NoMiss::onClickMouse(JNIEnv* env, Minecraft& theMinecraft, bool* cancel)
{
	if (!enabled) return;
	if (theMinecraft.getObjectMouseOver().getType().isEqualTo(MovingObjectType::getType("MISS", env)))
	{
		*cancel = true;
	}
}

void Ripterms::Modules::BlockOnAttack::renderGUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("BlockOnAttack", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void Ripterms::Modules::BlockOnAttack::onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel)
{
	if (!enabled) return;
	POINT cursorPos{};
	GetCursorPos(&cursorPos);
	PostMessageA(Ripterms::window, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
	PostMessageA(Ripterms::window, WM_RBUTTONUP, MK_RBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
}

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
