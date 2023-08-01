#pragma once
#include "../../java/lang/Object/Object.h"
#include "../../net/minecraft/client/Minecraft/Minecraft.h"
#include <vector>

namespace Ripterms
{
	namespace Cache
	{
		inline Minecraft theMinecraft{};
		inline EntityPlayerSP thePlayer{};
		inline WorldClient theWorld{};
		inline std::vector<EntityPlayer> playerEntities;
		bool fillCache();
	}
}