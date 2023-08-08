#pragma once
#include "../Cache/Cache.h"
#include "../GUI/GUI.h"
#include <ImGui/imgui.h>
#include <iostream>
#include <random>

namespace Ripterms
{
	namespace Modules
	{
		inline std::random_device rd{};
		namespace AimAssist
		{
			void run();
			void renderGUI();
		}
		namespace Test
		{
			void run();
			void renderGUI();
		}
		namespace Reach
		{
			void run();
			void renderGUI();
		}
	}
}