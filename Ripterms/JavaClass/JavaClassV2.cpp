#include "JavaClass.h"

std::unordered_map<std::string, Ripterms::JavaClassV2::JavaClassData> Ripterms::JavaClassV2::data{};
std::unordered_map<JNIEnv*, std::unordered_map<std::string, Ripterms::JavaClassV2::JClass>> Ripterms::JavaClassV2::jclassCache{};

bool Ripterms::JavaClassV2::init()
{
	auto& mappings = Ripterms::JavaClass::mappings[0];
	if (mappings.empty())
		return false;
	for (auto& [className, classContent] : mappings.items())
	{
		JClass javaClass = findClass(classContent["obfuscated"]);
		if (!javaClass.isValid()) continue;
		JavaClassData classData{};
		for (auto& field : classContent["fields"])
		{
			jfieldID fieldID = nullptr;
			if (field["static"] == true)
			{
				fieldID = Ripterms::p_env->GetStaticFieldID(javaClass, std::string(field["obfuscated"]).c_str(), std::string(field["signature"]).c_str());
			}
			else
			{
				fieldID = Ripterms::p_env->GetFieldID(javaClass, std::string(field["obfuscated"]).c_str(), std::string(field["signature"]).c_str());
			}
			if (!fieldID) continue;
			classData.fields.insert({ field["name"], fieldID });
		}
		for (auto& method : classContent["methods"])
		{
			jmethodID methodID = nullptr;
			if (method["static"] == true)
			{
				methodID = Ripterms::p_env->GetStaticMethodID(javaClass, std::string(method["obfuscated"]).c_str(), std::string(method["signature"]).c_str());
			}
			else
			{
				methodID = Ripterms::p_env->GetMethodID(javaClass, std::string(method["obfuscated"]).c_str(), std::string(method["signature"]).c_str());
			}
			if (!methodID) continue;
			classData.methods.insert({ method["name"], methodID });
		}
		data.insert({className, classData});
	}
	return true;
}

void Ripterms::JavaClassV2::clean()
{
	jclassCache.clear();
}

Ripterms::JavaClassV2::JavaClassV2(const std::string& class_path)
{
	this->class_path = class_path;
}

Ripterms::JavaClassV2::JavaClassV2(const JavaClassV2& otherJavaClass) :
	JavaClassV2(otherJavaClass.class_path)
{
}

Ripterms::JavaClassV2::JClass Ripterms::JavaClassV2::getJClass(JNIEnv* env)
{
	try
	{
		return jclassCache[env][class_path];
	}
	catch (...)
	{
		JClass a(findClass(class_path, env), env);
		jclassCache[env].insert({ class_path, a });
		return a;
	}
	return JClass(findClass(class_path, env), env);
}

jfieldID Ripterms::JavaClassV2::getFieldID(const std::string& name)
{
	try
	{
		return data[class_path].fields[name];
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}

jmethodID Ripterms::JavaClassV2::getMethodID(const std::string& name)
{
	try
	{
		return data[class_path].methods[name];
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}

jclass Ripterms::JavaClassV2::findClass(const std::string& class_path, JNIEnv* env)
{
	jint class_count = 0;
	jclass* classes = nullptr;
	jclass foundclass = nullptr;
	Ripterms::p_tienv->GetLoadedClasses(&class_count, &classes);
	for (int i = 0; i < class_count; ++i)
	{
		char* signature_buffer = nullptr;
		Ripterms::p_tienv->GetClassSignature(classes[i], &signature_buffer, nullptr);
		std::string signature = signature_buffer;
		Ripterms::p_tienv->Deallocate((unsigned char*)signature_buffer);
		signature = signature.substr(1);
		signature.pop_back();
		if (signature == class_path)
		{
			foundclass = (jclass)env->NewLocalRef(classes[i]);
		}
		env->DeleteLocalRef(classes[i]);
	}
	Ripterms::p_tienv->Deallocate((unsigned char*)classes);
	return foundclass;
}

Ripterms::JavaClassV2::JClass::JClass()
{
}

Ripterms::JavaClassV2::JClass::JClass(jclass javaClass, JNIEnv* env)
{
	if (javaClass)
	{
		this->javaClass = (jclass)env->NewGlobalRef(javaClass);
		if (env->GetObjectRefType(javaClass) == JNILocalRefType)
			env->DeleteLocalRef(javaClass);
	}
	else
	{
		this->javaClass = nullptr;
	}
	this->env = env;
}

Ripterms::JavaClassV2::JClass::JClass(const JClass& other) :
	JClass(other.javaClass, other.env)
{
}

Ripterms::JavaClassV2::JClass::~JClass()
{
	clear();
}

void Ripterms::JavaClassV2::JClass::clear()
{
	if (isValid()) env->DeleteGlobalRef(javaClass);
	this->javaClass = nullptr;
}

bool Ripterms::JavaClassV2::JClass::isValid()
{
	return javaClass != nullptr;
}

bool Ripterms::JavaClassV2::JClass::isEqualTo(const JClass& other)
{
	if (this->javaClass == other.javaClass)
		return true;
	return this->javaClass && other.javaClass
		&& env->IsSameObject(javaClass, other.javaClass) == JNI_TRUE;
}

Ripterms::JavaClassV2::JClass::operator jclass()
{
	return javaClass;
}
