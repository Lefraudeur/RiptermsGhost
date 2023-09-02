#include "JavaClass.h"
#include "../Mappings/mappings_lunar_1_7_10.h"
#include "../Mappings/mappings_forge_1_7_10.h"
#include "../Mappings/mappings_lunar_1_8_9.h"
#include "../Mappings/mappings_vanilla_1_8_9.h"
#include "../Mappings/mappings_lunar_1_16_5.h"

std::unordered_map<std::string, Ripterms::JavaClassV2::JavaClassData> Ripterms::JavaClassV2::data{};
std::unordered_map<JNIEnv*, std::unordered_map<std::string, Ripterms::JavaClassV2::JClass>> Ripterms::JavaClassV2::jclassCache{};

bool Ripterms::JavaClassV2::init()
{
	bool isSuccess = true;
	int selected_version_index = -1;
	const nlohmann::json* const allmaps[] =
	{
		Mappings::mappings_lunar_1_8_9,
		Mappings::mappings_vanilla_1_8_9,
		Mappings::mappings_lunar_1_7_10,
		Mappings::mappings_lunar_1_16_5,
		Mappings::mappings_forge_1_7_10
	};
	switch (version)
	{
	case LUNAR_1_8_9:
	{
		Ripterms::JavaClassV2::mappings = Mappings::mappings_lunar_1_8_9;
		selected_version_index = 0;
		break;
	}
	case VANILLA_1_8_9:
	{
		Ripterms::JavaClassV2::mappings = Mappings::mappings_vanilla_1_8_9;
		selected_version_index = 1;
		break;
	}
	case LUNAR_1_7_10:
	{
		Ripterms::JavaClassV2::mappings = Mappings::mappings_lunar_1_7_10;
		selected_version_index = 2;
		break;
	}
	case LUNAR_1_16_5:
	{
		Ripterms::JavaClassV2::mappings = Mappings::mappings_lunar_1_16_5;
		selected_version_index = 3;
		break;
	}
	case FORGE_1_7_10:
	{
		Ripterms::JavaClassV2::mappings = Mappings::mappings_forge_1_7_10;
		selected_version_index = 4;
		break;
	}
	default:
	{
		std::cerr << "Cannot find mappings for the specified version" << std::endl;
		isSuccess = false;
	}
	}
	for (int i = 0; i < sizeof(allmaps) / sizeof(nlohmann::json*); ++i)
	{
		if (i == selected_version_index) continue;
		delete allmaps[i];
	}
	if (!isSuccess) return false;

	auto& mappings = Ripterms::JavaClassV2::mappings[0];
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
		jclassCache[Ripterms::p_env].clear();
	delete mappings;
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
		return mappings[0][class_path]["obfuscated"];
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
		for (auto& field : mappings[0][class_path]["fields"])
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
		for (auto& method : mappings[0][class_path]["methods"])
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
		for (auto& field : mappings[0][class_path]["fields"])
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
		for (auto& method : mappings[0][class_path]["methods"])
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
	auto& classMapping = Ripterms::JavaClassV2::mappings[0][class_path];
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
