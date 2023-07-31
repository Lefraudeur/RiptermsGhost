#pragma once
#include <JNI/jni.h>
#include <JNI/jvmti.h>
#include <vector>
#include <string>
#include <json.hpp>
#include <MinHook.h>
#include <Windows.h>

namespace Ripterms
{
	inline HINSTANCE module = nullptr;
	enum Version
	{
		UNDEFINED,
		LUNAR_1_8_9
	};
	inline Version version = UNDEFINED;
	inline JavaVM* p_jvm = nullptr;
	inline JNIEnv* p_env = nullptr;
	inline jvmtiEnv* p_tienv = nullptr;

	class JavaClass
	{
		public:
			JavaClass(const std::string& class_path);
			JavaClass();
			JavaClass(JavaClass& otherJavaClass);
			~JavaClass();
			static bool fillAll();
			bool fill(const std::string& class_path);
			jclass javaClass = nullptr;
			std::unordered_map<std::string, jfieldID> fields;
			std::unordered_map<std::string, jmethodID> methods;
		private:
			static jclass findClass(const std::string& path);
			inline static nlohmann::json mappings{};
	};

	BOOL init();
	void clean();
}