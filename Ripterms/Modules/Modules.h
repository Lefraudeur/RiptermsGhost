#pragma once
#include "../Cache/Cache.h"
#include "../GUI/GUI.h"
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
	}
}