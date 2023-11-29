#include "Modules.h"
#include <ImGui/imgui.h>
#include <iostream>
#include "../../net/minecraft/network/Packet/Packet.h"
#include "../../net/minecraft/network/play/client/C03PacketPlayer/C03PacketPlayer.h"


static void callback(void* sp, void* j_rarg0, void* j_rarg1, void* j_rarg2, void* j_rarg3, void* j_rarg4, void* j_rarg5, bool* should_return, void* rbx, void* thread, void* r13) //j_rarg0 is this object in non static methods
{
	uint8_t* _constMethod = *(uint8_t**)((uint8_t*)rbx + 0x08);
	uint8_t* _constants = *(uint8_t**)(_constMethod + 0x08);
	uint8_t* constant_pool_base = _constants + 0x48;
	*(double*)((uint64_t*)constant_pool_base + 599) = 10.0;
	//*should_return = true;
	return;
}

void Ripterms::Modules::Test::renderGUI()
{
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	if (ImGui::Button("Run Test"))
	{
		//Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/client/gui/GuiScreen"));
		//jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "mouseClicked", "(III)V");

		//Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/client/entity/EntityPlayerSP"));
		//jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "swingItem", "()V");

		//Ripterms::JavaClassV2 lol2("net/minecraft/network/NetworkManager");
		//jmethodID mid = lol2.getMethodID("sendPacket");

		//Ripterms::JavaClassV2 lol2("net/minecraft/block/Block");
		//jmethodID mid = lol2.getMethodID("shouldSideBeRendered");

		Ripterms::JavaClassV2 lol2("net/minecraft/client/renderer/EntityRenderer");
		jmethodID mid = lol2.getMethodID("getMouseOver");

		Ripterms::JavaHook::add_to_java_hook(mid, callback);
	}
}