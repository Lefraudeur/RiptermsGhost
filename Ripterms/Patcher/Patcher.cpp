#include "Patcher.h"
#include "../Ripterms.h"
#include "../Cache/Cache.h"
#include "ClassPatcherJar.h"
#include "../../java/lang/ClassLoader/ClassLoader.h"
#include "../../java/lang/System/System.h"
#include "../../java/lang/String/String.h"
#include <fstream>

namespace
{
	Object original_EmptyMap{};

	void retransformClasses()
	{
		jclass classes[] = { Ripterms::classcache->EntityRendererClass.javaClass };
		jvmtiError error = Ripterms::p_tienv->RetransformClasses(sizeof(classes) / sizeof(jclass), classes);
		if (error) {
			char* err = nullptr;
			Ripterms::p_tienv->GetErrorName(error, &err);
			std::cout << err << std::endl;
			std::cout << "Failed Retransform" << std::endl;
			Ripterms::p_tienv->Deallocate((unsigned char*)err);
		}
	}

	void JNICALL ClassFileLoadHook
	(
		jvmtiEnv* jvmti_env, 
		JNIEnv* jni_env, 
		jclass class_being_redefined, 
		jobject loader, 
		const char* name, 
		jobject protection_domain, 
		jint class_data_len, 
		const unsigned char* class_data, 
		jint* new_class_data_len, 
		unsigned char** new_class_data
	)
	{
		if (jni_env->IsSameObject(class_being_redefined, Ripterms::classcache->EntityRendererClass.javaClass)) {
			std::cout << "Patching EntityRenderer class" << std::endl;
			Ripterms::JavaClass ClassPatcherClass("io/github/lefraudeur/ClassPatcher");
			jbyteArray original_class_bytes = jni_env->NewByteArray(class_data_len);
			jni_env->SetByteArrayRegion(original_class_bytes, 0, class_data_len, (const jbyte*)class_data);

			jbyteArray new_class_bytes = (jbyteArray)jni_env->CallStaticObjectMethod(
				ClassPatcherClass.javaClass,
				ClassPatcherClass.methods["patchEntityRenderer"],
				original_class_bytes,
				String(Ripterms::classcache->EntityRendererClass.getObfuscatedMethodName("getMouseOver")).getInstance(),
				String(Ripterms::classcache->ThreadContextClass.getObfuscatedClassName()).getInstance(),
				String(Ripterms::classcache->ThreadContextClass.getObfuscatedFieldName("EMPTY_MAP")).getInstance()
			);

			jni_env->DeleteLocalRef(original_class_bytes);
			*new_class_data_len = jni_env->GetArrayLength(new_class_bytes);
			jvmti_env->Allocate(*new_class_data_len, new_class_data);
			jni_env->GetByteArrayRegion(new_class_bytes, 0, *new_class_data_len, (jbyte*)*new_class_data);
			std::ofstream file("c:/Dump/dump.class", std::ios::binary);
			file.write((const char*)*new_class_data, *new_class_data_len);
			file.close();
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

	//here I am using an empty map, already in th game, to hide and store my cheat data, the getMouseOver than accesses this map (see asm folder)
	original_EmptyMap = Ripterms::p_env->GetStaticObjectField(Ripterms::classcache->ThreadContextClass.javaClass, Ripterms::classcache->ThreadContextClass.fields["EMPTY_MAP"]);
	Object hashmapClass = Ripterms::p_env->FindClass("java/util/HashMap");
	jmethodID constructor = Ripterms::p_env->GetMethodID((jclass)hashmapClass.getInstance(), "<init>", "()V");
	jobject hashmap = Ripterms::p_env->NewObject((jclass)hashmapClass.getInstance(), constructor);
	Ripterms::p_env->SetStaticObjectField(Ripterms::classcache->ThreadContextClass.javaClass, Ripterms::classcache->ThreadContextClass.fields["EMPTY_MAP"], hashmap);
	Ripterms::cache->EMPTY_MAP = hashmap;
	Ripterms::cache->EMPTY_MAP.put(String("reach_distance"), String("3.0"));

	ClassLoader classLoader(ClassLoader::newObject());
	if(!classLoader.loadJar(ClassPatcherJar, sizeof(ClassPatcherJar))) return false;
	retransformClasses();
	classLoader.clear();
	System::gc();
	return true;
}

void Ripterms::Patcher::clean()
{
	//cleaning the data we stored
	Ripterms::p_env->SetStaticObjectField(Ripterms::classcache->ThreadContextClass.javaClass, Ripterms::classcache->ThreadContextClass.fields["EMPTY_MAP"], original_EmptyMap.getInstance());
	original_EmptyMap.clear();
	//restoring old classes
	Ripterms::p_tienv->SetEventNotificationMode(JVMTI_DISABLE, JVMTI_EVENT_CLASS_FILE_LOAD_HOOK, NULL);
	retransformClasses();
}