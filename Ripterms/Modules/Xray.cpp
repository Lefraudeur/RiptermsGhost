#include "Modules.h"
#include <imgui.h>
#include "../Hook/JavaHook.h"
#include "../Cache/Cache.h"
#include "../../net/minecraft/client/renderer/ActiveRenderInfo/ActiveRenderInfo.h"
#include "../GUI/GUI.h"

void Ripterms::Modules::Xray::renderGUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Xray (crash)", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void Ripterms::Modules::Xray::render()
{
	if (!enabled || !Ripterms::cache->is_valid)
	{
		update_blocks = false;
		return;
	}
	update_blocks = true;

	ImVec2 screenSize = ImGui::GetWindowSize();

	Ripterms::Maths::Matrix modelView = ActiveRenderInfo::get_cached_MODELVIEW();
	Ripterms::Maths::Matrix projection = ActiveRenderInfo::get_cached_PROJECTION();
	Ripterms::Maths::Vector3d cameraPos = ActiveRenderInfo::get_cached_cameraPos();

	std::lock_guard lock{ renderData_mutex };
	for (RenderData& renderData : renderDatas)
	{
		for (RenderData::Quad& quad : renderData.quads)
		{
			Ripterms::Maths::Vector2d p1{}, p2{}, p3{}, p4{};
			if
			(
				!Ripterms::Maths::worldToScreen(quad.p1 - cameraPos, modelView, projection, (int)screenSize.x, (int)screenSize.y, p1)
				|| !Ripterms::Maths::worldToScreen(quad.p2 - cameraPos, modelView, projection, (int)screenSize.x, (int)screenSize.y, p2)
				|| !Ripterms::Maths::worldToScreen(quad.p3 - cameraPos, modelView, projection, (int)screenSize.x, (int)screenSize.y, p3)
				|| !Ripterms::Maths::worldToScreen(quad.p4 - cameraPos, modelView, projection, (int)screenSize.x, (int)screenSize.y, p4)
			)
				continue;
			ImGui::GetWindowDrawList()->AddQuadFilled(ImVec2((float)p1.x, (float)p1.y), ImVec2((float)p2.x, (float)p2.y), ImVec2((float)p3.x, (float)p3.y), ImVec2((float)p4.x, (float)p4.y), ImColor(209, 100, 245, 40));
		}
	}
}

void Ripterms::Modules::Xray::disable()
{
	thread_running = false;
	blockFinderThread.join();
}

void Ripterms::Modules::Xray::onShouldSideBeRendered(JNIEnv* env, Block& block, bool* cancel)
{
	if (!enabled) return;
	if (!block.instanceOf(Ripterms::JavaClassV2("net/minecraft/block/BlockOre").get_jclass(env)))
		Ripterms::JavaHook::set_return_value<uint64_t>(cancel, 0);
	else
		Ripterms::JavaHook::set_return_value<uint64_t>(cancel, 1);
	*cancel = true;
}

void Ripterms::Modules::Xray::updateRenderData()
{
	JavaVM* jvm = nullptr;
	JNI_GetCreatedJavaVMs(&jvm, 1, nullptr);
	if (!jvm) return;
	JNIEnv* env = nullptr;
	jvm->AttachCurrentThreadAsDaemon((void**)&env, nullptr);
	if (!env) return;

	while (thread_running && (!update_blocks || !Ripterms::cache->is_valid));

	{
		Ripterms::JNIFrame frame(env, 10);
		Minecraft theMinecraft = Minecraft::getTheMinecraft(env);
		jclass BlockOre = Ripterms::JavaClassV2("net/minecraft/block/BlockOre").get_jclass(env);

		while (thread_running)
		{
			static Ripterms::CTimer timer(std::chrono::milliseconds(1000));
			if (!update_blocks || !Ripterms::cache->is_valid || !timer.isElapsed()) continue;
			{
				Ripterms::JNIFrame frame(env, 10);
				World theWorld = theMinecraft.getTheWorld();

				Ripterms::Maths::Vector3d thePlayerPos = theMinecraft.getThePlayer().getPosition();
				thePlayerPos.x = std::floor(thePlayerPos.x);
				thePlayerPos.y = std::floor(thePlayerPos.y);
				thePlayerPos.z = std::floor(thePlayerPos.z);
				int base_x = (int)thePlayerPos.x - RADIUS, base_y = (int)thePlayerPos.y - RADIUS, base_z = (int)thePlayerPos.z - RADIUS;

				std::vector<Ripterms::Maths::Vector3d> positions{};

				for (int x = 0; x < 2 * RADIUS; ++x)
				{
					Ripterms::JNIFrame frame(env, 4 * RADIUS * RADIUS);
					for (int y = 0; y < 2 * RADIUS; ++y)
					{
						for (int z = 0; z < 2 * RADIUS; ++z)
						{
							Ripterms::Maths::Vector3d pos1(base_x + x, base_y + y, base_z + z);
							if (theWorld.getBlock(pos1).instanceOf(BlockOre))
								positions.push_back(pos1);
						}
					}
				}

				std::lock_guard lock{ renderData_mutex };
				renderDatas.clear();
				for (Ripterms::Maths::Vector3d& pos : positions)
					addRenderData(pos);
			}
		}

	}
	jvm->DetachCurrentThread();
}

void Ripterms::Modules::Xray::addRenderData(Ripterms::Maths::Vector3d blockPos)
{
	renderDatas.push_back
	(
		RenderData{
			{
				RenderData::Quad{{blockPos.x, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y, blockPos.z + 1}, {blockPos.x, blockPos.y, blockPos.z + 1}},
				RenderData::Quad{{blockPos.x, blockPos.y + 1, blockPos.z}, {blockPos.x + 1, blockPos.y + 1, blockPos.z}, {blockPos.x + 1, blockPos.y + 1, blockPos.z + 1}, {blockPos.x, blockPos.y + 1, blockPos.z + 1}},
				RenderData::Quad{{blockPos.x, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y + 1, blockPos.z}, {blockPos.x, blockPos.y + 1, blockPos.z}},
				RenderData::Quad{{blockPos.x, blockPos.y, blockPos.z + 1}, {blockPos.x + 1, blockPos.y, blockPos.z + 1}, {blockPos.x + 1, blockPos.y + 1, blockPos.z + 1}, {blockPos.x, blockPos.y + 1, blockPos.z + 1}},
				RenderData::Quad{{blockPos.x, blockPos.y, blockPos.z}, {blockPos.x, blockPos.y, blockPos.z + 1}, {blockPos.x, blockPos.y + 1, blockPos.z + 1}, {blockPos.x, blockPos.y + 1, blockPos.z}},
				RenderData::Quad{{blockPos.x + 1, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y, blockPos.z + 1}, {blockPos.x + 1, blockPos.y + 1, blockPos.z + 1}, {blockPos.x + 1, blockPos.y + 1, blockPos.z}}
			}
		}
	);
}
