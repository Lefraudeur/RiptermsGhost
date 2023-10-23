#pragma once
#include "../../java/lang/String/String.h"
#include <random>
#include "../Event/Event.h"
#include "../Maths/Maths.h"

namespace Ripterms
{
	namespace Modules
	{
		class IModule
		{
		public:
			virtual void run();
			virtual void renderGUI();
			virtual void render();
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
			void render() override;
		private:
			float max_distance = 6.0f;
			float max_angle = 80.0f;
			float multiplier = 1.0f;
			float multiplierPitch = 0.5f;
			Ripterms::Maths::Vector3d target_pos{};
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

		class HitBoxes : public IModule
		{
		public:
			void run();
			void renderGUI();
		private:
			float x_expand = 0.5f;
			float y_expand = 0.5f;
		};


		//Category Other
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
		};

		class LegitScaffold : public IModule
		{
		public:
			void onEvent(Ripterms::Event* event) override;
			void renderGUI() override;
		private:
			int tickDelay = 0;
		};

		class Sprint : public IModule
		{
		public:
			void run() override;
			void renderGUI() override;
		};

		// Category Render
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
		};

		class ESP : public IModule
		{
		public:
			void render() override;
		};

		inline std::map<std::string, std::vector<IModule*>> categories =
		{
			{"Combat", {new AimAssist(), new Reach(), new LeftClicker(), new WTap(), new HitBoxes()}},
			{"Player", {new Velocity(), new FastPlace(), new Blink(), new LegitScaffold(), new Sprint()}},
			{"Render", {new Xray(), new FullBright(), new ESP()}},
			{"Whatever", {new ClientBrandChanger(), new Test()}}
		};

		void runAll();
		void cleanAll();
	}
}