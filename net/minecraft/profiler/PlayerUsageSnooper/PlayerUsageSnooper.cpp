#include "PlayerUsageSnooper.h"

Map PlayerUsageSnooper::getSnooperStats()
{
	if(!instance) return Map();
	return Map(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->PlayerUsageSnooperClass.fields["snooperStats"]));
}
