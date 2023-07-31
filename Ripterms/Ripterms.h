#pragma once
#include <JNI/jni.h>
#include <vector>
#include <string>
#include <json.hpp>
#include <MinHook.h>
#include "Mappings/mappings_lunar_1_8_9.h"

namespace Ripterms
{
	inline HINSTANCE module = nullptr;
	enum Version
	{
		UNDEFINED,
		LUNAR_1_8_9
	};
	inline Version version = UNDEFINED;
	inline JNIEnv* p_env = nullptr;

	class JavaClass
	{
		public:
			JavaClass(const std::string& class_path);
			JavaClass();
			JavaClass(JavaClass& otherJavaClass);
			~JavaClass();
			void fill(const std::string& class_path);
			jclass javaClass = nullptr;
			std::unordered_map<std::string, jfieldID> fields;
			std::unordered_map<std::string, jmethodID> methods;
		private:
			inline static nlohmann::json mappings{};
	};

	void init();
	void clean();
}