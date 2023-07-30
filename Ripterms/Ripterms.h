#pragma once
#include <JNI/jni.h>
#include <vector>
#include <string>

namespace Ripterms
{
	inline JNIEnv* p_env = nullptr;

	class JavaClass
	{
		public:
			JavaClass(const std::string& class_path);
			JavaClass(JavaClass& otherJavaClass);
			~JavaClass();
			jclass javaClass;
			std::vector<jfieldID> fields;
			std::vector<jmethodID> methods;
	};

	void init();
	void clean();
}