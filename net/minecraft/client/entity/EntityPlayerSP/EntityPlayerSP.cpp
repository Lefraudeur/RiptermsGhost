#include "EntityPlayerSP.h"

NetHandlerPlayClient EntityPlayerSP::getSendQueue()
{
	if (Ripterms::version == Ripterms::Version::FORGE_1_7_10 || Ripterms::version == Ripterms::Version::LUNAR_1_7_10)
		return NetHandlerPlayClient(env->GetObjectField(instance, EntityPlayerMPClass.getFieldID("sendQueue")), env);
	return NetHandlerPlayClient(env->GetObjectField(instance, EntityPlayerSPClass.getFieldID("sendQueue")), env);
}
