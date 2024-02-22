#include "ActiveRenderInfo.h"
#include "../../../util/Vec3/Vec3.h"
#include "../../../../../Ripterms/Cache/Cache.h"

FloatBuffer ActiveRenderInfo::getMODELVIEW(JNIEnv* env)
{
	return FloatBuffer
	(
		env->GetStaticObjectField(ActiveRenderInfoClass.get_jclass(env), ActiveRenderInfoClass.getFieldID("MODELVIEW")),
		env
	);
}

FloatBuffer ActiveRenderInfo::getPROJECTION(JNIEnv* env)
{
	return FloatBuffer
	(
		env->GetStaticObjectField(ActiveRenderInfoClass.get_jclass(env), ActiveRenderInfoClass.getFieldID("PROJECTION")),
		env
	);
}

void ActiveRenderInfo::update_cache(JNIEnv* env)
{
	MODELVIEW = ActiveRenderInfo::getMODELVIEW(env).toMatrix(4, 4);
	PROJECTION = ActiveRenderInfo::getPROJECTION(env).toMatrix(4, 4);
	cameraPos = Ripterms::cache->theMinecraft.getRenderViewEntity().getRenderPos(Ripterms::cache->timer.getRenderPartialTicks());
}

Ripterms::Maths::Matrix ActiveRenderInfo::get_cached_MODELVIEW()
{
	return MODELVIEW;
}

Ripterms::Maths::Matrix ActiveRenderInfo::get_cached_PROJECTION()
{
	return PROJECTION;
}

Ripterms::Maths::Vector3d ActiveRenderInfo::get_cached_cameraPos()
{
	return cameraPos;
}
