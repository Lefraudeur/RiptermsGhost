#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>
#include "../Hook/JavaHook.h"

Ripterms::Modules::IModule::IModule(const char* name, const char* description) :
	name(name),
	description(description)
{
}

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

const char* Ripterms::Modules::IModule::get_name()
{
	return name;
}

const char* Ripterms::Modules::IModule::get_description()
{
	return description;
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
	if (!Ripterms::p_env || !Ripterms::cache->is_valid) return;
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
	if (!Ripterms::p_env || !Ripterms::cache->is_valid) return;
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
	if (!Ripterms::p_env || !Ripterms::cache->is_valid) return;
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
	if (!Ripterms::p_env || !Ripterms::cache->is_valid) return;
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
	if (!Ripterms::p_env || !Ripterms::cache->is_valid || Ripterms::Modules::IModule::onChannelRead0NoEvent) return;
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
	if (!Ripterms::p_env || !Ripterms::cache->is_valid) return;
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

void Ripterms::Modules::BlockOnAttack::onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel)
{
	if (!enabled) return;
	POINT cursorPos{};
	GetCursorPos(&cursorPos);
	PostMessageA(Ripterms::window, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
	PostMessageA(Ripterms::window, WM_RBUTTONUP, MK_RBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
}
