#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>
#include "../../net/minecraft/network/play/client/C03PacketPlayer/C03PacketPlayer.h"
#include "../Hook/JavaHook.h"

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

	NetHandlerPlayClient sendQueue(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env);
	Packet packet(Ripterms::JavaHook::get_jobject_param_at(frame, 1), env);

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
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
	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
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

	EntityPlayer this_player(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env);
	Entity entity(Ripterms::JavaHook::get_jobject_param_at(frame, 1), env);

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onAttackTargetEntityWithCurrentItem(env, this_player, entity, cancel);
		}
	}

	return;
}

static void onUpdateWalkingPlayer_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();

	EntityPlayerSP this_player(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env);

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onUpdateWalkingPlayer(env, this_player, cancel);
		}
	}

	return;
}

static void getClientModName_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onGetClientModName(env, cancel);
		}
	}
	return;
}

static void channelRead0_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();

	Packet packet(Ripterms::JavaHook::get_jobject_param_at(frame, 2), env);
	ChannelHandlerContext context(Ripterms::JavaHook::get_jobject_param_at(frame, 1), env);
	NetworkManager this_networkManager(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env);

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
			module->onChannelRead0(env, this_networkManager, context, packet, cancel);
		}
	}
	return;
}

static void clickMouse_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Ripterms::p_env) return;
	JNIEnv* env = thread->get_env();

	Minecraft theMinecraft(Ripterms::JavaHook::get_jobject_param_at(frame, 0), env);

	for (const std::pair<std::string, std::vector<Ripterms::Modules::IModule*>>& category : Ripterms::Modules::categories)
	{
		for (Ripterms::Modules::IModule* module : category.second)
		{
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
	for (const std::pair<std::string, std::vector<IModule*>>& category : categories)
	{
		for (IModule* m : category.second)
		{
			m->disable();
			delete m;
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
		ImGui::SliderInt("Packet Receive delay ms", &delay, 10, 1000, "%d");
		ImGui::EndGroup();
	}
}

void Ripterms::Modules::AttackLag::onChannelRead0(JNIEnv* env, NetworkManager& this_networkManager, ChannelHandlerContext& context, Packet& packet, bool* cancel)
{
	if (lag)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		lag = false;
	}
}

void Ripterms::Modules::AttackLag::onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel)
{
	if (!enabled) return;
	lag = true;
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
	if (theMinecraft.getObjectMouseOver().getType().isEqualTo(MovingObjectType::getType("MISS")))
	{
		Ripterms::JavaHook::set_return_value<uint64_t>(cancel, 0);
		*cancel = true;
	}
}
