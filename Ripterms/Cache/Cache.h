#pragma once
#include "../../java/lang/Object/Object.h"
#include "../../net/minecraft/client/Minecraft/Minecraft.h"
#include "../../java/util/Map/Map.h"
#include "../../net/minecraft/util/Timer/Timer.h"

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
		Timer timer{};

		Map EMPTY_MAP{};
		bool fillCache();
	private:
		EntityPlayerSP prev_thePlayer{};
	};
	inline Cache* cache = new Cache();
}