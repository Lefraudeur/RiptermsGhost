#pragma once
#include "../../net/minecraft/client/Minecraft/Minecraft.h"
#include "../../java/util/Map/Map.h"
#include "../../net/minecraft/util/Timer/Timer.h"
#include "../../java/nio/FloatBuffer/FloatBuffer.h"
#include "../../java/nio/IntBuffer/IntBuffer.h"

namespace Ripterms
{
	class Cache
	{
	public:
		Cache();
		~Cache();
		Minecraft theMinecraft{};
		EntityPlayerSP thePlayer{};
		PlayerControllerMP playerController{};
		WorldClient theWorld{};
		List playerEntities{};
		GameSettings gameSettings{};
		Timer timer{};
		NetHandlerPlayClient sendQueue{};

		bool fillCache();
	private:
		EntityPlayerSP prev_thePlayer{};
	};
	inline Cache* cache = new Cache();
}