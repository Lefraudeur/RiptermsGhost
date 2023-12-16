#include "JavaClass.h"
#include <iostream>
#include "../../java/lang/ClassLoader/ClassLoader.h"


std::unordered_map<std::string, Ripterms::JavaClassV2::JavaClassData> Ripterms::JavaClassV2::data{};
std::unordered_map<JNIEnv*, std::unordered_map<std::string, Ripterms::JavaClassV2::JClass>> Ripterms::JavaClassV2::jclassCache{};

bool Ripterms::JavaClassV2::init()
{
	try
	{
		Ripterms::JavaClassV2::mappings = nlohmann::json::parse(version.mappings_text);
	}
	catch (const nlohmann::json::exception& e)
	{
		std::cout << "Failed to parse mapping file" << '\n';
		std::cerr << e.what() << '\n';
		return false;
	}

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
			if (!fieldID)
			{
				std::cerr << "Failed to find field ID: " + std::string(field["name"]) << std::endl;
				continue;
			}
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
			if (!methodID)
			{
				std::cerr << "Failed to find method ID: " + std::string(method["name"]) << std::endl;
				continue;
			}
			classData.methods.insert({ method["name"], methodID });
		}
		data.insert({className, classData});
	}
	return true;
}

void Ripterms::JavaClassV2::clean()
{
	if (Ripterms::p_env)
	{
		jclassCache[Ripterms::p_env].clear();
	}
}

Ripterms::JavaClassV2::JavaClassV2(const std::string& class_path)
{
	this->class_path = class_path;
}

Ripterms::JavaClassV2::JavaClassV2(const JavaClassV2& otherJavaClass) :
	JavaClassV2(otherJavaClass.class_path)
{
}

Ripterms::JavaClassV2::JClass& Ripterms::JavaClassV2::getJClass(JNIEnv* env) const
{
	try
	{
		return jclassCache[env].at(class_path);
	}
	catch (...)
	{
		jclassCache[env].insert({ class_path, JClass(findClass(getObfuscatedClassName(), env), env)});
		return jclassCache[env].at(class_path);
	}
}

jfieldID Ripterms::JavaClassV2::getFieldID(const std::string& name) const
{
	try
	{
		return data.at(class_path).fields.at(name);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "Failed to get field ID " << name << std::endl;
		std::cerr << "for class " << class_path << std::endl;
		std::cin.ignore();
		return nullptr;
	}
}

jmethodID Ripterms::JavaClassV2::getMethodID(const std::string& name) const
{
	try
	{
		return data.at(class_path).methods.at(name);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "Failed to get method ID " << name << std::endl;
		std::cerr << "for class " << class_path << std::endl;
		std::cin.ignore();
		return nullptr;
	}
}

std::string Ripterms::JavaClassV2::getObfuscatedClassName() const
{
	try
	{
		return mappings[class_path]["obfuscated"];
	}
	catch (...)
	{
		return class_path;
	}
}

std::string Ripterms::JavaClassV2::getObfuscatedFieldName(const std::string& name) const
{
	try
	{
		for (auto& field : mappings[class_path]["fields"])
		{
			if (name == std::string(field["name"]))
				return field["obfuscated"];
		}
	}
	catch (...)
	{
	}
	return name;
}

std::string Ripterms::JavaClassV2::getObfuscatedMethodName(const std::string& name) const
{
	try
	{
		for (auto& method : mappings[class_path]["methods"])
		{
			if (name == std::string(method["name"]))
				return method["obfuscated"];
		}
	}
	catch (...)
	{
	}
	return name;
}

std::string Ripterms::JavaClassV2::getObfuscatedFieldSig(const std::string& name) const
{
	try
	{
		for (auto& field : mappings[class_path]["fields"])
		{
			if (name == std::string(field["name"]))
				return field["signature"];
		}
	}
	catch (...)
	{
	}
	return name;
}

std::string Ripterms::JavaClassV2::getObfuscatedMethodSig(const std::string& name) const
{
	try
	{
		for (auto& method : mappings[class_path]["methods"])
		{
			if (name == std::string(method["name"]))
				return method["signature"];
		}
	}
	catch (...)
	{
	}
	return name;
}

jclass Ripterms::JavaClassV2::findClass(const std::string& class_path, JNIEnv* env)
{
	jclass* loaded_classes = nullptr;
	jint loaded_classes_count = 0;
	jclass found_class = nullptr;
	jobject minecraft_classloader = nullptr;
	jvmtiEnv* tienv = Ripterms::p_tienv;
	tienv->GetLoadedClasses(&loaded_classes_count, &loaded_classes);
	for (jint i = 0; i < loaded_classes_count; ++i)
	{
		char* signature_buffer = nullptr;
		tienv->GetClassSignature(loaded_classes[i], &signature_buffer, nullptr);
		std::string signature = signature_buffer;
		tienv->Deallocate((unsigned char*)signature_buffer);
		signature = signature.substr(1);
		signature.pop_back();
		if (signature == class_path)
		{
			found_class = (jclass)env->NewLocalRef(loaded_classes[i]);
			break;
		}
		if (signature == Ripterms::JavaClassV2("net/minecraft/client/Minecraft").getObfuscatedClassName())
		{
			Ripterms::p_tienv->GetClassLoader(loaded_classes[i], &minecraft_classloader);
		}
	}
	for (jint i = 0; i < loaded_classes_count; ++i)
	{
		env->DeleteLocalRef(loaded_classes[i]);
	}
	tienv->Deallocate((unsigned char*)loaded_classes);

	if (!found_class)
	{
		ClassLoader classLoader(minecraft_classloader, env);
		found_class = classLoader.findClass(class_path);
	}
	env->DeleteLocalRef(minecraft_classloader);
	return found_class;
}

void Ripterms::JavaClassV2::removeFromJClassCache()
{
	for (auto& entry : jclassCache)
	{
		entry.second.erase(class_path);
	}
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

void Ripterms::JavaClassV2::reload()
{
	auto& classMapping = Ripterms::JavaClassV2::mappings[class_path];
	JClass javaClass = findClass(classMapping["obfuscated"]);
	Ripterms::JavaClassV2::JavaClassData classData{};
	for (auto& field : classMapping["fields"])
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
	for (auto& method : classMapping["methods"])
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
	data[class_path] = classData;
}

void Ripterms::JavaClassV2::JClass::clear()
{
	if (!Ripterms::p_env) return; //process termination scenario
	if (isValid()) env->DeleteGlobalRef(javaClass);
	this->javaClass = nullptr;
}

bool Ripterms::JavaClassV2::JClass::isValid() const
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

const jclass& Ripterms::JavaClassV2::JClass::getInstance() const
{
	return javaClass;
}

Ripterms::JavaClassV2::JClass::operator jclass()
{
	return getInstance();
}
