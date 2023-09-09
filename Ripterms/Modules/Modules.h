#pragma once
#include "../Cache/Cache.h"
#include "../GUI/GUI.h"
#include "../../java/lang/String/String.h"
#include <ImGui/imgui.h>
#include <iostream>
#include <random>
#include "../Event/Event.h"

namespace Ripterms
{
	namespace Modules
	{
		class IModule
		{
		public:
			virtual void run();
			virtual void renderGUI();
			virtual void disable();
			virtual void onEvent(Ripterms::Event* event);
		protected:
			inline static std::random_device rd{};
			inline static std::mt19937 gen{rd()};
			bool enabled = false;
		};


		// Category Combat
		class AimAssist : public IModule
		{
		public:
			void run() override;
			void renderGUI() override;
		private:
			float max_distance = 6.0f;
			float max_angle = 80.0f;
			float multiplier = 1.0f;
			float multiplierPitch = 0.5f;
		};

		class Reach : public IModule
		{
		public:
			void run() override;
			void renderGUI() override;
		private:
			float reach_distance = 4.0f;
		};

		class LeftClicker : public IModule
		{
		public:
			void run() override;
			void renderGUI() override;
		private:
			int min_cps = 7;
			int max_cps = 14;
		};

		class WTap : public IModule
		{
		public:
			void onEvent(Ripterms::Event* event) override;
			void renderGUI() override;
		};


		//Category MISC
		class FullBright : public IModule
		{
		public:
			void run() override;
			void renderGUI() override;
			void disable() override;
		private:
			float old_gamma = -1.0f;
		};

		class Xray : public IModule
		{
		public:
			void run() override;
			void renderGUI() override;
			void disable() override;
		private:
			int keyBind = VK_NUMPAD2;
		};

		class ClientBrandChanger : public IModule
		{
		public:
			void renderGUI() override;
			void disable() override;
		private:
			char name[128] = { 0 };
			String old_ClientModName{};
			String getClientModName();
		};

		class Test : public IModule
		{
		public:
			void renderGUI() override;
		};

		//Category Player
		class Velocity : public IModule
		{
		public:
			void run() override;
			void renderGUI() override;
		private:
			float motionX = 0.0f;
			float motionY = 0.0f;
			float motionZ = 0.0f;
			int tickDelay = 1;
			bool only_facing = false;
		};

		class FastPlace : public IModule
		{
		public:
			void run() override;
			void renderGUI() override;
		private:
			int tickDelay = 0;
		};

		class Blink : public IModule
		{
		public:
			void run() override;
			void renderGUI() override;
			void disable() override;
		private:
			int keyBind = VK_NUMPAD1;
		};

		class LegitScaffold : public IModule
		{
		public:
			void onEvent(Ripterms::Event* event) override;
			void renderGUI() override;
		private:
			int keyBind = VK_NUMPAD1;
			int tickDelay = 0;
		};

		class Sprint : public IModule
		{
		public:
			void run() override;
			void renderGUI() override;
		};

		inline std::map<std::string, std::vector<IModule*>> categories =
		{
			{"Combat", {new AimAssist(), new Reach(), new LeftClicker(), new WTap()}},
			{"Player", {new Velocity(), new FastPlace(), new Blink(), new LegitScaffold(), new Sprint()}},
			{"Misc", {new FullBright(), new Xray(), new ClientBrandChanger(), new Test()}}
		};

		void runAll();
		void cleanAll();
	}
}