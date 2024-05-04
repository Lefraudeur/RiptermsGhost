#include "Modules.h"
#include "../Hook/JavaHook.h"

void Ripterms::Modules::NoMiss::onClickMouse(JNIEnv* env, Minecraft& theMinecraft, bool* cancel)
{
	if (!enabled) return;
	if (theMinecraft.getObjectMouseOver().getType().isEqualTo(MovingObjectType::getType("MISS", env)))
	{
		Ripterms::JavaHook::set_return_value<uint64_t>(cancel, 0);
		*cancel = true;
	}
}