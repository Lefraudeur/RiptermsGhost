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
		List playerEntities{};
		GameSettings gameSettings{};
		Map BUILT_IN_MODELS{};
		bool fillCache();
	private:
		EntityPlayerSP prev_thePlayer{};
	};
	inline Cache* cache = new Cache();
}