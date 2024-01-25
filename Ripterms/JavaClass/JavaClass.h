#pragma once
#include "../Ripterms/Ripterms.h"
#include <json.hpp>
#include <mutex>

namespace Ripterms
{
	class JavaClassV2
	{ // JavaClassV2 is here to fix the problem of the JNIEnv and all references beeing incorrect because different thread
	public:
		static bool init();
		static void clean();

		static jclass findClass(const std::string& class_path, JNIEnv* env = Ripterms::p_env);

		JavaClassV2(const std::string& class_path);
		JavaClassV2(const JavaClassV2& otherJavaClass);

		void reload(); //refill the data with correct fields / methods

		jclass get_jclass(JNIEnv* env = Ripterms::p_env) const; // a class reference is env / thread specific
		jfieldID getFieldID(const std::string& name) const;
		jmethodID getMethodID(const std::string& name) const;
		std::string getObfuscatedClassName() const;
		std::string getObfuscatedFieldName(const std::string& name) const;
		std::string getObfuscatedMethodName(const std::string& name) const;
		std::string getObfuscatedFieldSig(const std::string& name) const;
		std::string getObfuscatedMethodSig(const std::string& name) const;
	private:
		struct JavaClassData
		{
			std::unordered_map<std::string, jfieldID> fields{};
			std::unordered_map<std::string, jmethodID> methods{};
		};

		struct JClassCache
		{
			JNIEnv* owning_env;
			std::unordered_map<std::string, jclass> cached_classes;
		};
		inline static std::vector<JClassCache> JClass_caches{};
		static JClassCache& get_JClass_cache(JNIEnv* env);

		static std::unordered_map<std::string, JavaClassData> data;
		inline static nlohmann::json mappings{};
		std::string class_path;
	};
}