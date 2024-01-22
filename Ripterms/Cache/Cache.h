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
		Minecraft theMinecraft{Ripterms::p_env, true};
		EntityPlayerSP thePlayer{ Ripterms::p_env, true };
		PlayerControllerMP playerController{ Ripterms::p_env, true };
		WorldClient theWorld{ Ripterms::p_env, true };
		List playerEntities{ Ripterms::p_env, true };
		GameSettings gameSettings{ Ripterms::p_env, true };
		Timer timer{ Ripterms::p_env, true };
		NetHandlerPlayClient sendQueue{ Ripterms::p_env, true };

		bool fillCache();
		bool is_valid = false;
	private:
		EntityPlayerSP prev_thePlayer{ Ripterms::p_env, true };
	};
	inline Cache* cache = new Cache();
}