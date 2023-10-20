#pragma once
#include "../../../../../java/lang/Object/Object.h"
#include "../../../../../java/nio/FloatBuffer/FloatBuffer.h"
#include "../../../../../java/nio/IntBuffer/IntBuffer.h"

class ActiveRenderInfo : public Object
{
public:
	using Object::Object;
	static FloatBuffer getMODELVIEW(JNIEnv* env = Ripterms::p_env);
	static FloatBuffer getPROJECTION(JNIEnv* env = Ripterms::p_env);
	static IntBuffer getVIEWPORT(JNIEnv* env = Ripterms::p_env);
protected:
	inline static Ripterms::JavaClassV2 ActiveRenderInfoClass{ "net/minecraft/client/renderer/ActiveRenderInfo" };
};