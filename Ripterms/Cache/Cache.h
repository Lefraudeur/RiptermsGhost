#pragma once
#include "../../java/lang/Object/Object.h"
#include "../../net/minecraft/client/Minecraft/Minecraft.h"

namespace Ripterms
{
	namespace Cache
	{
		inline Minecraft theMinecraft{};
		inline EntityPlayerSP thePlayer{};
		inline WorldClient theWorld{};
		bool fillCache();
	}
}