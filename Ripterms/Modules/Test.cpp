#include "Modules.h"
#include <ImGui/imgui.h>
#include <iostream>
#include "../../net/minecraft/network/Packet/Packet.h"
#include "../../net/minecraft/network/play/client/C03PacketPlayer/C03PacketPlayer.h"
#include <thread>
#include "../../net/minecraft/client/Minecraft/Minecraft.h"


static void callback(void* sp, bool* should_return, void* rbx, void* thread) //j_rarg0 is this object in non static methods
{
	static int call_count = 0;
	call_count++;
	std::cout << "number of calls: " << call_count << '\n';
	*should_return = true;
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

		//Ripterms::JavaClassV2 lol2("net/minecraft/client/renderer/EntityRenderer");
		//jmethodID mid = lol2.getMethodID("getMouseOver");

		//Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/client/gui/GuiScreen"));
		//jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "func_73864_a", "(III)V");

		Ripterms::JavaClassV2::JClass lol2(Ripterms::JavaClassV2::findClass("net/minecraft/entity/player/EntityPlayer"));
		jmethodID mid = Ripterms::p_env->GetMethodID(lol2.getInstance(), "func_70664_aZ", "()V");

		Ripterms::JavaHook::add_to_java_hook(mid, callback);

		return;
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