#pragma once
#include "../../java/lang/Object/Object.h"
#include "../../net/minecraft/client/Minecraft/Minecraft.h"

namespace Ripterms
{
	class Cache
	{
	public:
		Cache();
		~Cache();
		Minecraft theMinecraft{};
		EntityPlayerSP thePlayer{};
		WorldClient theWorld{};
		bool fillCache();
	};
	inline Cache* cache = new Cache();
}