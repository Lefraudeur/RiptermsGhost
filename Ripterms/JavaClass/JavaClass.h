#pragma once
#include "../Ripterms/Ripterms.h"
#include <json.hpp>

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

		struct JClass
		{
			JClass();
			JClass(jclass javaClass, JNIEnv* env = Ripterms::p_env);
			JClass(const JClass& other);
			~JClass();

			void clear(); //delete ref
			bool isValid() const;
			bool isEqualTo(const JClass& other);
			const jclass& getInstance() const;

			operator jclass();
		private:
			jclass javaClass = nullptr;
			JNIEnv* env = Ripterms::p_env;
		};

		void reload(); //refill the data with correct fields / methods

		void removeFromJClassCache();
		JClass& getJClass(JNIEnv* env = Ripterms::p_env) const; // a class reference is env / thread specific
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

		static std::unordered_map<JNIEnv*, std::unordered_map<std::string, JClass>> jclassCache;
		static std::unordered_map<std::string, JavaClassData> data;
		inline static const nlohmann::json* mappings = nullptr;

		std::string class_path{};
	};
}