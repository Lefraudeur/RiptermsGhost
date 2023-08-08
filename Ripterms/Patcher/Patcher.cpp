#include "Patcher.h"
#include "../Ripterms.h"
#include "ClassPatcherJar.h"
#include "../../java/lang/ClassLoader/ClassLoader.h"
#include <fstream>

namespace
{
	bool should_patchGetMouseOver = false;
	double desired_reach = 0.0;
	ClassLoader classLoader{};
	void JNICALL ClassFileLoadHook
	(
		jvmtiEnv* jvmti_env, 
		JNIEnv* jni_env, jclass 
		class_being_redefined, 
		jobject loader, 
		const char* name, 
		jobject protection_domain, 
		jint class_data_len, 
		const unsigned char* class_data, 
		jint* new_class_data_len, 
		unsigned char** new_class_data
	)
	{
		if (should_patchGetMouseOver && jni_env->IsSameObject(class_being_redefined, Ripterms::classcache->EntityRendererClass.javaClass)) {
			std::cout << "Patching getMouseOver" << std::endl;
				std::ofstream file("c:/Dump/dump.class", std::ios::binary);
				file.write((const char*)class_data, class_data_len);
				file.close();
			should_patchGetMouseOver = false;
			jbyteArray original_class_bytes = jni_env->NewByteArray(class_data_len);
			jni_env->SetByteArrayRegion(original_class_bytes, 0, class_data_len, (const jbyte*)class_data);
			jstring methodName = jni_env->NewStringUTF(Ripterms::classcache->EntityRendererClass.getObfuscatedMethodName("getMouseOver").c_str());
			jbyteArray new_class_bytes = (jbyteArray)jni_env->CallStaticObjectMethod(
				Ripterms::classcache->ClassPatcherClass.javaClass,
				Ripterms::classcache->ClassPatcherClass.methods["patchGetMouseOver"],
				original_class_bytes,
				methodName,
				(jdouble)desired_reach
			);
			jni_env->DeleteLocalRef(original_class_bytes);
			jni_env->DeleteLocalRef(methodName);
			*new_class_data_len = jni_env->GetArrayLength(new_class_bytes);
			jvmti_env->Allocate(*new_class_data_len, new_class_data);
			jni_env->GetByteArrayRegion(new_class_bytes, 0, *new_class_data_len, (jbyte*)*new_class_data);
			jni_env->DeleteLocalRef(new_class_bytes);
		}
	}
}

bool Ripterms::Patcher::init()
{
	jvmtiCapabilities capabilities{};
	capabilities.can_retransform_classes = JVMTI_ENABLE;
	jvmtiError error = Ripterms::p_tienv->AddCapabilities(&capabilities);
	if (error) {
		char* errstr = nullptr;
		Ripterms::p_tienv->GetErrorName(error, &errstr);
		std::cerr << errstr << std::endl;
		Ripterms::p_tienv->Deallocate((unsigned char*)errstr);
		return false;
	}
	jvmtiEventCallbacks callbacks{};
	callbacks.ClassFileLoadHook = &ClassFileLoadHook;
	error = Ripterms::p_tienv->SetEventCallbacks(&callbacks, sizeof(jvmtiEventCallbacks));
	if (error) {
		char* errstr = nullptr;
		Ripterms::p_tienv->GetErrorName(error, &errstr);
		std::cerr << errstr << std::endl;
		Ripterms::p_tienv->Deallocate((unsigned char*)errstr);
		return false;
	}
	error = Ripterms::p_tienv->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_CLASS_FILE_LOAD_HOOK, NULL);
	if (error) {
		char* errstr = nullptr;
		Ripterms::p_tienv->GetErrorName(error, &errstr);
		std::cerr << errstr << std::endl;
		Ripterms::p_tienv->Deallocate((unsigned char*)errstr);
		return false;
	}
	classLoader = ClassLoader::newObject();
	if(!classLoader.loadJar(ClassPatcherJar, sizeof(ClassPatcherJar))) return false;
	Ripterms::classcache->ClassPatcherClass.fill("io/github/lefraudeur/ClassPatcher");
	return true;
}

void Ripterms::Patcher::clean()
{
	Ripterms::p_tienv->SetEventNotificationMode(JVMTI_DISABLE, JVMTI_EVENT_CLASS_FILE_LOAD_HOOK, NULL);
	Ripterms::p_tienv->RetransformClasses(1, &Ripterms::classcache->EntityRendererClass.javaClass);
	classLoader.clear();
}

void Ripterms::Patcher::patchGetMouseOver(double reach)
{
	should_patchGetMouseOver = true;
	desired_reach = reach;
	Ripterms::p_tienv->RetransformClasses(1, &Ripterms::classcache->EntityRendererClass.javaClass);
	should_patchGetMouseOver = false;
}
