#include "Modules.h"
#include "../Cache/Cache.h"
#include "../../java/lang/String/String.h"
#include <ImGui/imgui.h>


void Ripterms::Modules::Reach::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Reach", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("opt", ImGuiDir_Down)) display_options = !display_options;
	if (display_options) {
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		ImGui::SliderFloat("Reach Distance", &reach_distance, 3.0f, 4.0f, "%.1f");
		ImGui::EndGroup();
	}
}

void Ripterms::Modules::Reach::disable()
{
	if (!cp_reach_addr) return;
	*cp_reach_addr = (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5 ? 9.0 : 3.0);
	*(void**)(_constMethod + 0x08) = original_constant_pool;
	VirtualFree(new_constant_pool, 0, MEM_RELEASE);
}

void Ripterms::Modules::Reach::onGetMouseOver(JNIEnv* env, float* partialTicks, bool* cancel)
{
	static float prev_reach_distance = -1.0f;
	static bool runonce = true;
	if (!enabled)
	{
		if (!cp_reach_addr) return;
		if (prev_reach_distance != -1.0f)
		{
			*cp_reach_addr = (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5 ? 9.0 : 3.0);
			prev_reach_distance = -1.0f;
		}
		return;
	}

	if (runonce)
	{
		Ripterms::JavaClassV2 EntityRenderer("net/minecraft/client/renderer/EntityRenderer");
		jmethodID mid = EntityRenderer.getMethodID("getMouseOver");
		uint8_t* method = *((uint8_t**)mid);
		_constMethod = *(uint8_t**)(method + 0x08);
		original_constant_pool = *(uint8_t**)(_constMethod + 0x08);

		int cp_length = *(int*)((uint8_t*)original_constant_pool + 0x3C);
		int cp_size = cp_length * 8 + (Ripterms::JavaHook::is_old_java ? 0x50 : 0x48);

		new_constant_pool = Ripterms::Hook::AllocateNearbyMemory((uint8_t*)original_constant_pool, cp_size, PAGE_READWRITE);
		memcpy(new_constant_pool, original_constant_pool, cp_size);
		*(void**)(_constMethod + 0x08) = new_constant_pool;

		uint8_t* constant_pool_base = (uint8_t*)new_constant_pool + (Ripterms::JavaHook::is_old_java ? 0x50 : 0x48);
		for (int i = 0; i < cp_length; ++i)
		{
			double* d = (double*)constant_pool_base + i;
			if (*d == (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5 ? 9.0 : 3.0))
			{
				cp_reach_addr = d;
				break;
			}
		}
		runonce = false;
	}

	if (!cp_reach_addr) return;
	double d = (Ripterms::version.type == Ripterms::Version::MAJOR_1_16_5 ? reach_distance * reach_distance : reach_distance);
	if (prev_reach_distance == d) return;
	*cp_reach_addr = d;
	prev_reach_distance = d;
}
