#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>

void Ripterms::Modules::FullBright::run()
{
	if (!enabled)
	{
		disable();
		return;
	}
	double gamma = Ripterms::cache->gameSettings.getGammaSetting();
	if ( gamma != 50.0)
	{
		Ripterms::cache->gameSettings.setGammaSetting(50.0);
		old_gamma = gamma;
	}
}

void Ripterms::Modules::FullBright::disable()
{
	if (!Ripterms::p_env) return;
	if (old_gamma >= 0.0)
	{
		Ripterms::cache->gameSettings.setGammaSetting(old_gamma);
		old_gamma = -1.0;
	}
}
