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

	bool errCheck(jvmtiError error)
	{
		if (error == JVMTI_ERROR_NONE)
		{
			return true;
		}
		char* err = nullptr;
		Ripterms::p_tienv->GetErrorName(error, &err);
		std::cout << err << std::endl;
		Ripterms::p_tienv->Deallocate((unsigned char*)err);
		return false;
	}

	void retransformClasses()
	{
		jclass classes[] = 
		{
			Ripterms::classcache->EntityRendererClass.javaClass,
			Ripterms::classcache->ClientBrandRetrieverClass.javaClass,
			Ripterms::classcache->NetworkManagerClass.javaClass,
			Ripterms::classcache->BlockClass.javaClass
		};
		errCheck(Ripterms::p_tienv->RetransformClasses(sizeof(classes) / sizeof(jclass), classes));
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
		std::function<void(const std::string&, const std::string&, const std::vector<jobject>&)> patchClass = 
		[=](const std::string& patchMethod, const std::string& methodToPatch, const std::vector<jobject>& additional)
		{
			Ripterms::JavaClass ClassPatcherClass("io/github/lefraudeur/ClassPatcher");
			jbyteArray original_class_bytes = jni_env->NewByteArray(class_data_len);
			jni_env->SetByteArrayRegion(original_class_bytes, 0, class_data_len, (const jbyte*)class_data);

			String methodToPatch_str(methodToPatch);
			String ThreadContext(Ripterms::classcache->ThreadContextClass.getObfuscatedClassName());
			String EMPTY_MAP(Ripterms::classcache->ThreadContextClass.getObfuscatedFieldName("EMPTY_MAP"));

			jobject* args = new jobject[additional.size() + 4];
			args[0] = original_class_bytes;
			args[1] = methodToPatch_str.getInstance();
			args[2] = ThreadContext.getInstance();
			args[3] = EMPTY_MAP.getInstance();

			if(!additional.empty())
				std::copy(additional.begin(), additional.end(), args + 4);

			jbyteArray new_class_bytes = (jbyteArray)jni_env->CallStaticObjectMethodA(
				ClassPatcherClass.javaClass,
				ClassPatcherClass.methods[patchMethod],
				(jvalue*)args
			);

			delete[] args;
			jni_env->DeleteLocalRef(original_class_bytes);
			*new_class_data_len = jni_env->GetArrayLength(new_class_bytes);
			jvmti_env->Allocate(*new_class_data_len, new_class_data);
			jni_env->GetByteArrayRegion(new_class_bytes, 0, *new_class_data_len, (jbyte*)*new_class_data);
			
			std::ofstream file("c:/Dump/dump.class", std::ios::binary);
			file.write((const char*)*new_class_data, *new_class_data_len);
			file.close();
			
			jni_env->DeleteLocalRef(new_class_bytes);
		};

		if (jni_env->IsSameObject(class_being_redefined, Ripterms::classcache->EntityRendererClass.javaClass))
		{
			patchClass("patchEntityRenderer", Ripterms::classcache->EntityRendererClass.getObfuscatedMethodName("getMouseOver"), {});
		}
		else if (jni_env->IsSameObject(class_being_redefined, Ripterms::classcache->ClientBrandRetrieverClass.javaClass))
		{
			patchClass("patchClientBrandRetriever", Ripterms::classcache->ClientBrandRetrieverClass.getObfuscatedMethodName("getClientModName"), {});
		}
		else if (jni_env->IsSameObject(class_being_redefined, Ripterms::classcache->NetworkManagerClass.javaClass))
		{
			String Packet(Ripterms::classcache->PacketClass.getObfuscatedClassName());
			String NetworkManager(Ripterms::classcache->NetworkManagerClass.getObfuscatedClassName());
			patchClass("patchNetworkManager", Ripterms::classcache->NetworkManagerClass.getObfuscatedMethodName("sendPacket"), 
			{
				Packet.getInstance(),
				NetworkManager.getInstance()
			});
		}
		else if (jni_env->IsSameObject(class_being_redefined, Ripterms::classcache->BlockClass.javaClass))
		{
			Ripterms::JavaClass RegistryClass("net/minecraft/util/registry/Registry");
			String BlockRegistryOwner(RegistryClass.getObfuscatedClassName());
			String blockRegistry(RegistryClass.getObfuscatedFieldName("blockRegistry"));
			String blockRegistrySig(RegistryClass.getObfuscatedFieldSig("blockRegistry"));
			String RegistryNamespaced(Ripterms::classcache->RegistryNamespacedClass.getObfuscatedClassName());
			String getNameForObject(Ripterms::classcache->RegistryNamespacedClass.getObfuscatedMethodName("getNameForObject"));
			String RessourceLocation
			(
				(
					Ripterms::version == Ripterms::Version::LUNAR_1_7_10 ||
					Ripterms::version == Ripterms::Version::FORGE_1_7_10
					? "none"
					: Ripterms::JavaClass("net/minecraft/util/ResourceLocation").getObfuscatedClassName()
				)
			);
			patchClass("patchBlock", Ripterms::classcache->BlockClass.getObfuscatedMethodName("shouldSideBeRendered"), 
			{
					BlockRegistryOwner.getInstance(),
					blockRegistry.getInstance(),
					blockRegistrySig.getInstance(),
					RegistryNamespaced.getInstance(),
					getNameForObject.getInstance(),
					RessourceLocation.getInstance()
			});
		}
	}
}

bool Ripterms::Patcher::init()
{
	jvmtiCapabilities capabilities{};
	capabilities.can_retransform_classes = JVMTI_ENABLE;
	if(!errCheck(Ripterms::p_tienv->AddCapabilities(&capabilities)))
		return false;

	jvmtiEventCallbacks callbacks{};
	callbacks.ClassFileLoadHook = &ClassFileLoadHook;
	if(!errCheck(Ripterms::p_tienv->SetEventCallbacks(&callbacks, sizeof(jvmtiEventCallbacks))))
		return false;

	if(!errCheck(Ripterms::p_tienv->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_CLASS_FILE_LOAD_HOOK, NULL))) return false;

	//here I am using an empty map, already in th game, to hide and store my cheat data, the getMouseOver than accesses this map (see asm folder)
	original_EmptyMap = Ripterms::p_env->GetStaticObjectField(Ripterms::classcache->ThreadContextClass.javaClass, Ripterms::classcache->ThreadContextClass.fields["EMPTY_MAP"]);
	Object hashmapClass = Ripterms::p_env->FindClass("java/util/HashMap");
	jmethodID constructor = Ripterms::p_env->GetMethodID((jclass)hashmapClass.getInstance(), "<init>", "()V");
	jobject hashmap = Ripterms::p_env->NewObject((jclass)hashmapClass.getInstance(), constructor);
	Ripterms::p_env->SetStaticObjectField(Ripterms::classcache->ThreadContextClass.javaClass, Ripterms::classcache->ThreadContextClass.fields["EMPTY_MAP"], hashmap);
	Ripterms::cache->EMPTY_MAP = hashmap;

	Ripterms::cache->EMPTY_MAP.put(String("reach_distance"), String("3.0"));
	Ripterms::cache->EMPTY_MAP.put
	(
		String("client_brand"),
		String(Ripterms::p_env->CallStaticObjectMethod(Ripterms::classcache->ClientBrandRetrieverClass.javaClass, Ripterms::classcache->ClientBrandRetrieverClass.methods["getClientModName"]))
	);
	Ripterms::cache->EMPTY_MAP.put
	(
		String("blink_enabled"),
		String("0")
	);
	Ripterms::cache->EMPTY_MAP.put
	(
		String("blink_send"),
		String("0")
	);
	Ripterms::cache->EMPTY_MAP.put
	(
		String("blink_packets"),
		List::newObject()
	);
	Ripterms::cache->EMPTY_MAP.put
	(
		String("xray_enabled"),
		String("0")
	);
	List blocks = List::newObject();
	blocks.add(String("minecraft:iron_ore"));
	blocks.add(String("minecraft:gold_ore"));
	blocks.add(String("minecraft:coal_ore"));
	blocks.add(String("minecraft:emerald_ore"));
	blocks.add(String("minecraft:quartz_ore"));
	blocks.add(String("minecraft:redstone_ore"));
	blocks.add(String("minecraft:lit_redstone_ore"));
	blocks.add(String("minecraft:lapis_ore"));
	blocks.add(String("minecraft:diamond_ore"));
	blocks.add(String("palamod:tile.paladium.ore"));
	blocks.add(String("palamod:tile.amethyst.ore"));
	blocks.add(String("palamod:tile.titane.ore"));
	blocks.add(String("palamod:tile.trixium.ore"));
	blocks.add(String("palamod:tile.findium.ore"));
	blocks.add(String("palamod:tile.paladium.green.ore"));
	blocks.add(String("palamod:tile.paladium_green.ore"));
	Ripterms::cache->EMPTY_MAP.put
	(
		String("xray_blocks"),
		blocks
	);
	ClassLoader classLoader(ClassLoader::newObject());
	if(!classLoader.loadJar(ClassPatcherJar.data(), ClassPatcherJar.size())) return false;
	retransformClasses();
	Ripterms::p_tienv->SetEventNotificationMode(JVMTI_DISABLE, JVMTI_EVENT_CLASS_FILE_LOAD_HOOK, NULL);
	classLoader.clear();
	System::gc();
	return true;
}

void Ripterms::Patcher::clean()
{
	//restoring old classes
	retransformClasses();
	Ripterms::p_env->SetStaticObjectField(Ripterms::classcache->ThreadContextClass.javaClass, Ripterms::classcache->ThreadContextClass.fields["EMPTY_MAP"], original_EmptyMap.getInstance());
	original_EmptyMap.clear();
}