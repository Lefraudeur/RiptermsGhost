#pragma once
#include "../../java/lang/Object/Object.h"
#include "../../net/minecraft/client/Minecraft/Minecraft.h"
#include <vector>

namespace Ripterms
{
	class Cache
	{
	public:
		Minecraft theMinecraft{};
		EntityPlayerSP thePlayer{};
		WorldClient theWorld{};
		bool fillCache();
	};
	inline Cache* cache = new Cache();
}