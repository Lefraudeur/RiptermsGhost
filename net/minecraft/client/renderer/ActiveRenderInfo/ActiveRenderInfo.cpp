#include "ActiveRenderInfo.h"

FloatBuffer ActiveRenderInfo::getMODELVIEW(JNIEnv* env)
{
	return FloatBuffer(env->GetStaticObjectField(ActiveRenderInfoClass.getJClass(env), ActiveRenderInfoClass.getFieldID("MODELVIEW")), env);
}

FloatBuffer ActiveRenderInfo::getPROJECTION(JNIEnv* env)
{
	return FloatBuffer(env->GetStaticObjectField(ActiveRenderInfoClass.getJClass(env), ActiveRenderInfoClass.getFieldID("PROJECTION")), env);
}

IntBuffer ActiveRenderInfo::getVIEWPORT(JNIEnv* env)
{
	return IntBuffer(env->GetStaticObjectField(ActiveRenderInfoClass.getJClass(env), ActiveRenderInfoClass.getFieldID("VIEWPORT")), env);
}
