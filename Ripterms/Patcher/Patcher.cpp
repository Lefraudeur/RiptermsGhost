#include "Patcher.h"
#include "../Ripterms.h"
#include "../Cache/Cache.h"
#include "../Event/Event.h"
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
		Ripterms::JavaClassV2 EntityRendererClass("net/minecraft/client/renderer/EntityRenderer");
		Ripterms::JavaClassV2 ClientBrandRetrieverClass("net/minecraft/client/ClientBrandRetriever");
		Ripterms::JavaClassV2 NetworkManagerClass("net/minecraft/network/NetworkManager");
		Ripterms::JavaClassV2 EntityPlayerSPClass
		(
			(
				Ripterms::version == Ripterms::Version::FORGE_1_7_10
				|| Ripterms::version == Ripterms::Version::LUNAR_1_7_10
				? "net/minecraft/client/entity/EntityClientPlayerMP"
				: "net/minecraft/client/entity/EntityPlayerSP"
				)
		);
		Ripterms::JavaClassV2 EntityPlayerClass("net/minecraft/entity/player/EntityPlayer");

		jclass classes[] = 
		{
			EntityRendererClass.getJClass(),
			ClientBrandRetrieverClass.getJClass(),
			NetworkManagerClass.getJClass(),
			EntityPlayerSPClass.getJClass(),
			EntityPlayerClass.getJClass()
		};
		errCheck(Ripterms::p_tienv->RetransformClasses(sizeof(classes) / sizeof(jclass), classes));
		if (Ripterms::majorVersion != Ripterms::Version::MAJOR_1_16_5)
		{
			Ripterms::JavaClassV2 BlockClass("net/minecraft/block/Block");
			Ripterms::JavaClassV2 GL11Class("org/lwjgl/opengl/GL11");
			errCheck(Ripterms::p_tienv->RetransformClasses(1, &BlockClass.getJClass().getInstance()));
			errCheck(Ripterms::p_tienv->RetransformClasses(1, &GL11Class.getJClass().getInstance())); //patch GL11 for older versions to skip some code and avoid errors
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
		Ripterms::JavaClassV2 EntityRendererClass("net/minecraft/client/renderer/EntityRenderer");
		Ripterms::JavaClassV2 ClientBrandRetrieverClass("net/minecraft/client/ClientBrandRetriever");
		Ripterms::JavaClassV2 NetworkManagerClass("net/minecraft/network/NetworkManager");
		Ripterms::JavaClassV2 BlockClass("net/minecraft/block/Block");
		Ripterms::JavaClassV2 GL11Class("org/lwjgl/opengl/GL11");
		Ripterms::JavaClassV2 EntityPlayerSPClass
		(
			(
				Ripterms::version == Ripterms::Version::FORGE_1_7_10
				|| Ripterms::version == Ripterms::Version::LUNAR_1_7_10
				? "net/minecraft/client/entity/EntityClientPlayerMP"
				: "net/minecraft/client/entity/EntityPlayerSP"
			)
		);
		Ripterms::JavaClassV2 EntityPlayerClass("net/minecraft/entity/player/EntityPlayer");

		std::function<void(const std::string&, const std::string&, const std::vector<jobject>&)> patchClass = 
		[=](const std::string& patchMethod, const std::string& methodToPatch, const std::vector<jobject>& additional)
		{
			Ripterms::JavaClassV2 ClassPatcherClass("io/github/lefraudeur/ClassPatcher");
			Ripterms::JavaClassV2 ThreadContextClass("org/apache/logging/log4j/ThreadContext");

			jbyteArray original_class_bytes = jni_env->NewByteArray(class_data_len);
			jni_env->SetByteArrayRegion(original_class_bytes, 0, class_data_len, (const jbyte*)class_data);

			String methodToPatch_str(methodToPatch, jni_env);
			String ThreadContext(ThreadContextClass.getObfuscatedClassName(), jni_env);
			String EMPTY_MAP(ThreadContextClass.getObfuscatedFieldName("EMPTY_MAP"), jni_env);

			jobject* args = new jobject[additional.size() + 4];
			args[0] = original_class_bytes;
			args[1] = methodToPatch_str.getInstance();
			args[2] = ThreadContext.getInstance();
			args[3] = EMPTY_MAP.getInstance();

			if(!additional.empty())
				std::copy(additional.begin(), additional.end(), args + 4);

			jbyteArray new_class_bytes = (jbyteArray)jni_env->CallStaticObjectMethodA(
				ClassPatcherClass.getJClass(jni_env),
				ClassPatcherClass.getMethodID(patchMethod),
				(jvalue*)args
			);

			delete[] args;
			jni_env->DeleteLocalRef(original_class_bytes);
			*new_class_data_len = jni_env->GetArrayLength(new_class_bytes);
			jvmti_env->Allocate(*new_class_data_len, new_class_data);
			jni_env->GetByteArrayRegion(new_class_bytes, 0, *new_class_data_len, (jbyte*)*new_class_data);
			/*
			std::ofstream file("c:/Dump/dump.class", std::ios::binary);
			file.write((const char*)*new_class_data, *new_class_data_len);
			file.close();
			*/
			
			jni_env->DeleteLocalRef(new_class_bytes);
		};

		std::function<void(const std::string&, const std::string&, Ripterms::Event::Type, Ripterms::Event::Type)> patchMethod = 
		[=](const std::string& methodName, const std::string& methodSig, Ripterms::Event::Type preEvent, Ripterms::Event::Type postEvent)
		{
			Ripterms::JavaClassV2 ClassPatcherClass("io/github/lefraudeur/ClassPatcher");

			jbyteArray original_class_bytes = jni_env->NewByteArray(class_data_len);
			jni_env->SetByteArrayRegion(original_class_bytes, 0, class_data_len, (const jbyte*)class_data);

			jbyteArray new_class_bytes = (jbyteArray)jni_env->CallStaticObjectMethod
			(
				ClassPatcherClass.getJClass(jni_env),
				ClassPatcherClass.getMethodID("patchMethod"),
				original_class_bytes,
				String(methodName, jni_env).getInstance(),
				String(methodSig, jni_env).getInstance(),
				String(GL11Class.getObfuscatedClassName(), jni_env).getInstance(),
				(int)preEvent,
				(int)postEvent
			);

			jni_env->DeleteLocalRef(original_class_bytes);
			*new_class_data_len = jni_env->GetArrayLength(new_class_bytes);
			jvmti_env->Allocate(*new_class_data_len, new_class_data);
			jni_env->GetByteArrayRegion(new_class_bytes, 0, *new_class_data_len, (jbyte*)*new_class_data);
			jni_env->DeleteLocalRef(new_class_bytes);
		};

		Ripterms::JavaClassV2::JClass redefinedClass(class_being_redefined, jni_env);

		if (redefinedClass.isEqualTo(EntityRendererClass.getJClass(jni_env)))
		{
			patchClass("patchEntityRenderer", EntityRendererClass.getObfuscatedMethodName("getMouseOver"), {});
		}
		else if (redefinedClass.isEqualTo(ClientBrandRetrieverClass.getJClass(jni_env)))
		{
			patchClass("patchClientBrandRetriever", ClientBrandRetrieverClass.getObfuscatedMethodName("getClientModName"), {});
		}
		else if (redefinedClass.isEqualTo(NetworkManagerClass.getJClass(jni_env)))
		{
			Ripterms::JavaClassV2 PacketClass("net/minecraft/network/Packet");

			String Packet(PacketClass.getObfuscatedClassName(), jni_env);
			String NetworkManager(NetworkManagerClass.getObfuscatedClassName(), jni_env);
			patchClass("patchNetworkManager", NetworkManagerClass.getObfuscatedMethodName("sendPacket"), 
			{
				Packet.getInstance(),
				NetworkManager.getInstance()
			});
		}
		else if (Ripterms::majorVersion != Ripterms::Version::MAJOR_1_16_5 && redefinedClass.isEqualTo(BlockClass.getJClass(jni_env)))
		{
			Ripterms::JavaClassV2 RegistryClass("net/minecraft/util/registry/Registry");
			Ripterms::JavaClassV2 RegistryNamespacedClass("net/minecraft/util/RegistryNamespaced");

			String BlockRegistryOwner(RegistryClass.getObfuscatedClassName(), jni_env);
			String blockRegistry(RegistryClass.getObfuscatedFieldName("blockRegistry"), jni_env);
			String blockRegistrySig(RegistryClass.getObfuscatedFieldSig("blockRegistry"), jni_env);
			String RegistryNamespaced(RegistryNamespacedClass.getObfuscatedClassName(), jni_env);
			String getNameForObject(RegistryNamespacedClass.getObfuscatedMethodName("getNameForObject"), jni_env);
			String RessourceLocation
			(
				(
					Ripterms::version == Ripterms::Version::LUNAR_1_7_10 ||
					Ripterms::version == Ripterms::Version::FORGE_1_7_10
					? "none"
					: Ripterms::JavaClassV2("net/minecraft/util/ResourceLocation").getObfuscatedClassName()
				), jni_env
			);
			patchClass("patchBlock", BlockClass.getObfuscatedMethodName("shouldSideBeRendered"), 
			{
					BlockRegistryOwner.getInstance(),
					blockRegistry.getInstance(),
					blockRegistrySig.getInstance(),
					RegistryNamespaced.getInstance(),
					getNameForObject.getInstance(),
					RessourceLocation.getInstance()
			});
		}
		else if (Ripterms::majorVersion != Ripterms::Version::MAJOR_1_16_5 && redefinedClass.isEqualTo(GL11Class.getJClass(jni_env)))
		{
			Ripterms::JavaClassV2 ClassPatcherClass("io/github/lefraudeur/ClassPatcher");

			jbyteArray original_class_bytes = jni_env->NewByteArray(class_data_len);
			jni_env->SetByteArrayRegion(original_class_bytes, 0, class_data_len, (const jbyte*)class_data);

			jbyteArray new_class_bytes = (jbyteArray)jni_env->CallStaticObjectMethod
			(
				ClassPatcherClass.getJClass(jni_env),
				ClassPatcherClass.getMethodID("patchGL11"),
				original_class_bytes
			);

			jni_env->DeleteLocalRef(original_class_bytes);
			*new_class_data_len = jni_env->GetArrayLength(new_class_bytes);
			jvmti_env->Allocate(*new_class_data_len, new_class_data);
			jni_env->GetByteArrayRegion(new_class_bytes, 0, *new_class_data_len, (jbyte*)*new_class_data);
			jni_env->DeleteLocalRef(new_class_bytes);
		}
		else if (redefinedClass.isEqualTo(EntityPlayerSPClass.getJClass(jni_env)))
		{
			//setup Events
			patchMethod
			(
				EntityPlayerSPClass.getObfuscatedMethodName("onUpdateWalkingPlayer"),
				EntityPlayerSPClass.getObfuscatedMethodSig("onUpdateWalkingPlayer"),
				Ripterms::Event::Type::PRE_MOTION,
				Ripterms::Event::Type::POST_MOTION
			);
		}
		else if (redefinedClass.isEqualTo(EntityPlayerClass.getJClass(jni_env)))
		{
			patchMethod
			(
				EntityPlayerClass.getObfuscatedMethodName("attackTargetEntityWithCurrentItem"),
				EntityPlayerClass.getObfuscatedMethodSig("attackTargetEntityWithCurrentItem"),
				Ripterms::Event::Type::PRE_ATTACK,
				Ripterms::Event::Type::POST_ATTACK
			);
		}
	}
}

bool Ripterms::Patcher::init()
{
	Ripterms::JavaClassV2 ThreadContextClass("org/apache/logging/log4j/ThreadContext");
	//here I am using an empty map, already in th game, to hide and store my cheat data, the getMouseOver than accesses this map (see asm folder)
	original_EmptyMap = Ripterms::p_env->GetStaticObjectField(ThreadContextClass.getJClass(), ThreadContextClass.getFieldID("EMPTY_MAP"));
	Object hashmapClass = Ripterms::p_env->FindClass("java/util/HashMap");
	jmethodID constructor = Ripterms::p_env->GetMethodID((jclass)hashmapClass.getInstance(), "<init>", "()V");
	jobject hashmap = Ripterms::p_env->NewObject((jclass)hashmapClass.getInstance(), constructor);
	Ripterms::p_env->SetStaticObjectField(ThreadContextClass.getJClass(), ThreadContextClass.getFieldID("EMPTY_MAP"), hashmap);
	Ripterms::cache->EMPTY_MAP = hashmap;

	Ripterms::cache->EMPTY_MAP.put(String("reach_distance"), String("3.0"));
	Ripterms::JavaClassV2 ClientBrandRetrieverClass("net/minecraft/client/ClientBrandRetriever");
	Ripterms::cache->EMPTY_MAP.put
	(
		String("client_brand"),
		String(Ripterms::p_env->CallStaticObjectMethod(ClientBrandRetrieverClass.getJClass(), ClientBrandRetrieverClass.getMethodID("getClientModName")))
	);
	Ripterms::cache->EMPTY_MAP.put(String("blink_enabled"), String("0"));
	Ripterms::cache->EMPTY_MAP.put(String("blink_send"),String("0"));
	Ripterms::cache->EMPTY_MAP.put(String("blink_packets"),List::newObject());
	Ripterms::cache->EMPTY_MAP.put(String("xray_enabled"),String("0"));
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
	Ripterms::cache->EMPTY_MAP.put(String("xray_blocks"), blocks);

	ClassLoader classLoader(ClassLoader::newObject());
	if(!classLoader.loadJar(ClassPatcherJar.data(), ClassPatcherJar.size()))
		return false;
	Ripterms::JavaClassV2 ClassPatcherClass("io/github/lefraudeur/ClassPatcher");
	ClassPatcherClass.reload();

	jvmtiCapabilities capabilities{};
	capabilities.can_retransform_classes = JVMTI_ENABLE;
	if (!errCheck(Ripterms::p_tienv->AddCapabilities(&capabilities)))
		return false;

	jvmtiEventCallbacks callbacks{};
	callbacks.ClassFileLoadHook = &ClassFileLoadHook;
	if (!errCheck(Ripterms::p_tienv->SetEventCallbacks(&callbacks, sizeof(jvmtiEventCallbacks))))
		return false;

	if (!errCheck(Ripterms::p_tienv->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_CLASS_FILE_LOAD_HOOK, NULL)))
		return false;
	retransformClasses();

	Ripterms::p_tienv->SetEventNotificationMode(JVMTI_DISABLE, JVMTI_EVENT_CLASS_FILE_LOAD_HOOK, NULL);
	ClassPatcherClass.removeFromJClassCache(); //delete all references to loaded class
	classLoader.clear(); //delete reference to classLoader
	System::gc(); //call garbage collector to destroy the loaded classes
	return true;
}

void Ripterms::Patcher::clean()
{
	Ripterms::JavaClassV2 ThreadContextClass("org/apache/logging/log4j/ThreadContext");
	//restoring old classes
	retransformClasses();
	Ripterms::p_env->SetStaticObjectField(ThreadContextClass.getJClass(), ThreadContextClass.getFieldID("EMPTY_MAP"), original_EmptyMap.getInstance());
	original_EmptyMap.clear();
}