#pragma once
#include "../../HotSpot/HotSpot.hpp"
#include "../../java/lang/String/String.h"
#include <random>
#include "../Maths/Maths.h"
#include "../../net/minecraft/network/Packet/Packet.h"
#include "../../net/minecraft/entity/Entity/Entity.h"
#include "../../net/minecraft/entity/player/EntityPlayer/EntityPlayer.h"
#include "../../net/minecraft/util/BlockPos/BlockPos.h"
#include "../../net/minecraft/client/network/NetHandlerPlayClient/NetHandlerPlayClient.h"
#include "../../net/minecraft/world/World/World.h"
#include "../../net/minecraft/client/entity/EntityPlayerSP/EntityPlayerSP.h"
#include <thread>
#include <imgui.h>
#include <type_traits>
#include <memory>
#include "../../net/minecraft/network/NetworkManager/NetworkManager.h"
#include "../../net/minecraft/client/Minecraft/Minecraft.h"
#include "../GUI/gyro_gui/gyro_gui.h"

namespace Ripterms
{
	namespace Modules
	{
		class IModule
		{
		public:
			IModule(const char* name = "Unnamed Module", const char* description = "No description");
			virtual void run();
			virtual void renderGUI();
			virtual void render();
			virtual void disable(); // called when the cheat is uninjected

			const char* get_name();
			const char* get_description();

			inline static std::atomic<bool> onAddToSendQueueNoEvent = false;
			virtual void onAddToSendQueue(JNIEnv* env, NetHandlerPlayClient& sendQueue, Packet& packet, bool* cancel);

			virtual void onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel);
			virtual void onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel);
			virtual void onGetMouseOver(JNIEnv* env, float partialTicks, bool* cancel);
			virtual void onGetClientModName(JNIEnv* env, bool* cancel);

			inline static std::atomic<bool> onChannelRead0NoEvent = false;
			virtual void onChannelRead0(JNIEnv* env, NetworkManager& this_networkManager, ChannelHandlerContext& context, Packet& packet, bool* cancel);

			virtual void onClickMouse(JNIEnv* env, Minecraft& theMinecraft, bool* cancel);

			void onKeyBind(int keyBind);

			bool enabled = false;
			bool display_options = false;
			int keyBind = 0;

		protected:
			inline static std::random_device rd{};
			inline static std::mt19937 gen{rd()};

		private:
			const char* name;
			const char* description;
		};


		// Category Combat
		class AimAssist : public IModule
		{
		public:
			AimAssist() : IModule("Aim assist", "Aims at the closest player, relative to your crosshair") {}
			void run() override;
			void renderGUI() override;
			void render() override;
			void disable() override;
		private:
			float max_distance = 6.0f;
			float max_angle = 80.0f;
			float multiplier = 1.0f;
			float multiplierPitch = 0.4f;
			EntityPlayer prev_selected_target{ Ripterms::p_env, true };
		};

		class Reach : public IModule
		{
		public:
			Reach() : IModule("Reach", "Allows you to hit entities further away") {}
			void renderGUI() override;
			void disable() override;
			void onGetMouseOver(JNIEnv* env, float partialTicks, bool* cancel) override;
		private:
			float reach_distance = 4.0f;
			HotSpot::ConstantPool* original_constant_pool = nullptr;
			HotSpot::ConstantPool* new_constant_pool = nullptr;
			double* cp_reach_addr = nullptr;
			HotSpot::ConstMethod* _constMethod = nullptr;
		};

		class LeftClicker : public IModule
		{
		public:
			LeftClicker() : IModule("Left clicker", "Clicks for you when holding left click") {}
			void run() override;
			void renderGUI() override;
		private:
			int min_cps = 7;
			int max_cps = 14;
		};

		class WTap : public IModule
		{
		public:
			WTap() : IModule("WTap", "Resets sprint after attacking someone") {}
			void onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel) override;
			void onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel) override;
		private:
			int ticks = 0;
		};

		class HitBoxes : public IModule
		{
		public:
			HitBoxes() : IModule("Hitboxes", "Extends enemies hitbox") {}
			void renderGUI();
			void run() override;
		private:
			float x_expand = 0.1f;
			float y_expand = 0.1f;
		};


		//Category Other
		class ClientBrandChanger : public IModule
		{
		public:
			ClientBrandChanger() : IModule("Clientbrand changer", "Changes the client brand sent to the server on login") {}
			void renderGUI() override;
			void onGetClientModName(JNIEnv* env, bool* cancel) override;
		private:
			char client_name[256] = { '\0' };
			String getClientModName();
		};

		class Test : public IModule
		{
		public:
			Test() : IModule("Test") {}
			void renderGUI() override;
		};

		//Category Player
		class Velocity : public IModule
		{
		public:
			Velocity() : IModule("Velocity", "Modifies the knockback you take when you get damaged") {}
			void run() override;
			void renderGUI() override;
		private:
			float motionX = 0.0f;
			float motionY = 0.0f;
			float motionZ = 0.0f;
			int tickDelay = 1;
		};

		class FastPlace : public IModule
		{
		public:
			FastPlace() : IModule("Fast place", "Allows you to place blocks faster while holding right click") {}
			void run() override;
			void renderGUI() override;
		private:
			int tickDelay = 0;
		};

		class Blink : public IModule
		{
		public:
			Blink() : IModule("Blink", "Stop receiving packets from the server, process all the stopped packets once disabled") {}
			void run() override;
			void renderGUI() override;
			void disable() override;
			void onAddToSendQueue(JNIEnv* env, NetHandlerPlayClient& sendQueue, Packet& packet, bool* cancel) override;
			void onChannelRead0(JNIEnv* env, NetworkManager& this_networkManager, ChannelHandlerContext& context, Packet& packet, bool* cancel);
		private:
			void sendPackets(NetHandlerPlayClient& sendQueue);
			bool delay_sent_packets = true;
			bool delay_received_packets = false;

			std::vector<Packet> packets{};

			struct PacketData
			{
				NetworkManager this_networkManager;
				ChannelHandlerContext context;
				Packet packet;
			};
			std::mutex rpackets_mutex{};
			std::vector<PacketData> rpackets{};
			void sendrPackets(JNIEnv* env);
			void addrPacket(const PacketData& data);
		};

		class LegitScaffold : public IModule
		{
		public:
			LegitScaffold() : IModule("Legit scaffold", "Auomatically sneak at the edge of blocks when you are holding the 'S' key") {}
			void onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel) override;
			void renderGUI() override;
		private:
			int tickDelay = 0;
		};

		class Sprint : public IModule
		{
		public:
			Sprint() : IModule("Sprint", "Same as constantly holding your sprint key") {}
			void run() override;
		};

		// Category Render
		class FullBright : public IModule
		{
		public:
			FullBright() : IModule("Full bright", "See in the dark") {}
			void run() override;
			void disable() override;
		private:
			double old_gamma = -1.0;
		};

		class Xray : public IModule
		{
		public:
			Xray() : IModule("Xray", "See ores through blocks") {}
			void renderGUI() override;
			void render() override;
			void disable() override;
		private:
			struct RenderData
			{
				RenderData(const Ripterms::Maths::Vector3d& blockPos, const std::string& blockName, Xray* xray);
				struct Quad
				{
					Ripterms::Maths::Vector3d p1, p2, p3, p4;
				} quads[6];
				ImColor color{ 209, 100, 245, 40 };
				bool render = true;
			};

			static void updateRenderData(Xray* xray);

			int RADIUS = 20;
			bool coal = false;
			bool redstone = false;
			bool diamond = true;
			bool gold = true;
			bool iron = true;
			bool emerald = true;
			bool lapis = true;
			bool other = true;

			std::vector<RenderData> renderDatas{};
			std::mutex renderData_mutex{};
			volatile bool thread_running = true;
			volatile bool update_blocks = false;
			std::thread blockFinderThread{ updateRenderData, this };
		};

		class ESP : public IModule
		{
		public:
			ESP() : IModule("ESP") {}
			void render() override;
		};

		class NoFall : public IModule
		{
		public:
			NoFall() : IModule("No fall", "Don't take fall damage") {}
			void onAddToSendQueue(JNIEnv* env, NetHandlerPlayClient& sendQueue, Packet& packet, bool* cancel) override;
		};

		class Glide : public IModule
		{
		public:
			Glide() : IModule("Glide", "Fall slowly") {}
			void onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel) override;
		};

		class VelocityFly : public IModule
		{
		public:
			VelocityFly() : IModule("Velocity fly", "Modifies your velocity so you can stay in the air and fly") {}
			void renderGUI() override;
			void onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel) override;
		private:
			float speed = 0.1f;
		};

		class Speed : public IModule
		{
		public:
			Speed() : IModule("Speed", "Go brrrrrrrrrrrrr") {}
			void renderGUI() override;
			void onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel) override;
		private:
			float speed = 0.1f;
		};

		class BackTrack : public IModule
		{
		public:
			BackTrack() : IModule("BackTrack", "Delays packets when you hit someone") {}
			void renderGUI() override;
			void onChannelRead0(JNIEnv* env, NetworkManager& this_networkManager, ChannelHandlerContext& context, Packet& packet, bool* cancel) override;
			void onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel) override;
		private:
			std::atomic<bool> lag = false;
			std::atomic<int> saved_target_entity_id = 0;
			bool disableOnHit = true;
			bool targetPacketsOnly = false;
			int delay = 450;

			struct PacketData
			{
				NetworkManager this_networkManager;
				ChannelHandlerContext context;
				Packet packet;
			};
			std::mutex packets_mutex{};
			std::vector<PacketData> packets{};
			void sendPackets(JNIEnv* env);
			void addPacket(const PacketData& data);

			bool isAttackPacket(Packet& packet, JNIEnv* env);
			bool isTargetPositionPacket(Packet& packet, JNIEnv* env);
		};

		class NoMiss : public IModule
		{
		public:
			NoMiss() : IModule("NoMiss", "Prevents you from attacking if no enemy is on your crosshair") {}
			void onClickMouse(JNIEnv* env, Minecraft& theMinecraft, bool* cancel) override;
		};

		class BlockOnAttack : public IModule
		{
		public: 
			BlockOnAttack() : IModule("BlockOnAttack", "Right click when you attack someone") {}
			void onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel) override;
		};

		class VelocityPacket : public IModule
		{
		public:
			VelocityPacket() : IModule("VelocityPacket", "Changes velocity by editing received velocity packets") {}
			void renderGUI() override;
			void onChannelRead0(JNIEnv* env, NetworkManager& this_networkManager, ChannelHandlerContext& context, Packet& packet, bool* cancel) override;
		private:
			float motionX_multiplier = 0.0f;
			float motionY_multiplier = 0.0f;
			float motionZ_multiplier = 0.0f;
		};


		class Category
		{
		public:
			Category(const Category& cat) = delete;
			~Category() { for (IModule* module : modules) delete module; }

			template<typename... T, typename = std::enable_if_t<((std::is_base_of_v<IModule, T> && ...))>>
			inline static Category create(const char* name)
			{
				std::vector<IModule*> modules{};
				modules.reserve(sizeof...(T));
				(modules.push_back(new T()), ...);
				return Category(name, std::move(modules));
			}

			const char* name;
			std::vector<IModule*> modules;
		private:
			Category(const char* name, std::vector<IModule*>&& modules) : name(name), modules(std::move(modules)) {}
		};

		inline Category categories[] =
		{
			Category::create<AimAssist, Reach, LeftClicker, WTap, HitBoxes, BackTrack, NoMiss, BlockOnAttack>("Combat"),
			Category::create<FastPlace, Blink, LegitScaffold, NoFall>("Player"),
			Category::create<Velocity, VelocityPacket, Sprint, Glide, VelocityFly, Speed>("Movement"),
			Category::create<Xray, FullBright, ESP>("Render"),
			Category::create<ClientBrandChanger, Test>("Misc")
		};

		void setupEventHooks();
		void runAll();
		void cleanAll();
	}
}