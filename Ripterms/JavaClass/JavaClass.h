#pragma once
#include "../Ripterms/Ripterms.h"
#include <json.hpp>

namespace Ripterms
{
	class JavaClass
	{
	public:
		JavaClass(const std::string& class_path);
		JavaClass();
		JavaClass(const JavaClass& otherJavaClass);
		~JavaClass();
		void clear();
		static bool init();
		bool fill(const std::string& class_path);
		std::string getObfuscatedMethodName(const std::string& unobf_name);
		std::string getObfuscatedMethodSig(const std::string& unobf_name);
		std::string getObfuscatedFieldName(const std::string& unobf_name);
		std::string getObfuscatedFieldSig(const std::string& unobf_name);
		std::string getObfuscatedClassName();
		jclass javaClass = nullptr;
		std::unordered_map<std::string, jfieldID> fields{};
		std::unordered_map<std::string, jmethodID> methods{};
		static jclass findClass(const std::string& path);
		inline static const nlohmann::json* mappings = nullptr;
	private:
		std::string class_path{};
	};

	class JavaClassV2
	{ // JavaClassV2 is here to fix the problem of the JNIEnv and all references beeing incorrect because different thread
	public:
		static bool init();
		static void clean();

		JavaClassV2(const std::string& class_path);
		JavaClassV2(const JavaClassV2& otherJavaClass);

		struct JClass
		{
			JClass();
			JClass(jclass javaClass, JNIEnv* env = Ripterms::p_env);
			JClass(const JClass& other);
			~JClass();

			void clear(); //delete ref
			bool isValid();
			bool isEqualTo(const JClass& other);

			operator jclass();
		private:
			jclass javaClass = nullptr;
			JNIEnv* env = Ripterms::p_env;
		};

		JClass getJClass(JNIEnv* env = Ripterms::p_env);
		jfieldID getFieldID(const std::string& name);
		jmethodID getMethodID(const std::string& name);
	private:
		struct JavaClassData
		{
			std::unordered_map<std::string, jfieldID> fields{};
			std::unordered_map<std::string, jmethodID> methods{};
		};

		static std::unordered_map<JNIEnv*, std::unordered_map<std::string, JClass>> jclassCache;
		static std::unordered_map<std::string, JavaClassData> data;
		static jclass findClass(const std::string& class_path, JNIEnv* env = Ripterms::p_env);

		std::string class_path{};
	};

	class JavaClassCache
	{
	public:
		JavaClassCache();
		bool fillCache();
		JavaClass ObjectClass{};
		JavaClass CollectionClass{};
		JavaClass ListClass{};
		JavaClass AbstractClientPlayerClass{};
		JavaClass EntityPlayerSPClass{};
		JavaClass MinecraftClass{};
		JavaClass WorldClientClass{};
		JavaClass EntityClass{};
		JavaClass EntityLivingBaseClass{};
		JavaClass EntityPlayerClass{};
		JavaClass Vec3Class{};
		JavaClass WorldClass{};
		JavaClass ClassLoaderClass{};
		JavaClass EntityRendererClass{};
		JavaClass GameSettingsClass{};
		JavaClass ClientBrandRetrieverClass{};
		JavaClass MapClass{};
		JavaClass StringClass{};
		JavaClass ThreadContextClass{};
		JavaClass SystemClass{};
		JavaClass NetworkManagerClass{};
		JavaClass PacketClass{};
		JavaClass MovingObjectPositionClass{};
		JavaClass MovingObjectTypeClass{};
		JavaClass BlockClass{};
		JavaClass RegistryNamespacedClass{};
	};

	inline JavaClassCache* classcache = new JavaClassCache();
}