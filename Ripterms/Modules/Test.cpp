#include "Modules.h"
#include <ImGui/imgui.h>
#include <iostream>
#include "../../net/minecraft/network/Packet/Packet.h"
#include "../../net/minecraft/network/play/client/C03PacketPlayer/C03PacketPlayer.h"
#include <thread>
#include "../../net/minecraft/client/Minecraft/Minecraft.h"
#include "../Hook/JavaHook.h"


static void callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	jclass cl = thread->get_env()->FindClass("java/lang/Object");
	thread->get_env()->DeleteLocalRef(cl);
	std::this_thread::sleep_for(std::chrono::milliseconds(2));
	return;
}

void Ripterms::Modules::Test::renderGUI()
{
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	if (ImGui::Button("Run Test"))
	{
		//jclass lol2 = Ripterms::JavaClassV2::findClass("net/minecraft/client/gui/GuiScreen");
		//jmethodID mid = Ripterms::p_env->GetMethodID(lol2, "mouseClicked", "(III)V");

		//Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/client/entity/EntityPlayerSP"));
		//jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "swingItem", "()V");

		//Ripterms::JavaClassV2 lol2("net/minecraft/network/NetworkManager");
		//jmethodID mid = lol2.getMethodID("sendPacket");

		//Ripterms::JavaClassV2 lol2("net/minecraft/block/Block");
		//jmethodID mid = lol2.getMethodID("shouldSideBeRendered");

		//Ripterms::JavaClassV2 lol2("net/minecraft/client/renderer/EntityRenderer");
		//jmethodID mid = lol2.getMethodID("getMouseOver");

		//Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/client/gui/GuiScreen"));
		//jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "func_73864_a", "(III)V");

		//jclass lol2 = Ripterms::JavaClassV2::findClass("pr");
		//jmethodID mid = Ripterms::p_env->GetMethodID(lol2, "bw", "()V");
		
		jclass lol2(Ripterms::JavaClassV2::findClass("biv"));
		jmethodID mid = Ripterms::p_env->GetMethodID(lol2, "a", "(Lpk;DDDFF)V");
		HotSpot::Method* method = *(HotSpot::Method**)mid;

		uint8_t* i2i = (uint8_t*)method->get_i2i_entry();
		std::cout << (void*)i2i << '\n';

		Ripterms::JavaHook::hook(mid, callback);


		//00000000031210E0
		//0000000003121341
		//0x261

		/*
		std::thread a([mid] {
			JNIEnv* env = Ripterms::get_current_thread_env();
			while (true)
			{
				Minecraft theMinecraft = Minecraft::getTheMinecraft(env);
				EntityPlayerSP thePlayer = theMinecraft.getThePlayer();
				env->CallVoidMethod(thePlayer.getInstance(), mid);

				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}
		});
		a.detach();
		*/
	}
}