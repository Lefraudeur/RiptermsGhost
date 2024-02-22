#include "JavaClass.h"
#include <iostream>
#include "../../java/lang/ClassLoader/ClassLoader.h"


std::unordered_map<std::string, Ripterms::JavaClassV2::JavaClassData> Ripterms::JavaClassV2::data{};

Ripterms::JavaClassV2::JClassCache& Ripterms::JavaClassV2::get_JClass_cache(JNIEnv* env)
{
	//couldn't find a good solution to cache jclass while remaining thread safe and fast
	static std::atomic<bool> is_writing_JClass_caches = false;
	while (is_writing_JClass_caches);

	for (JClassCache& jclass_cache : JClass_caches)
	{
		if (jclass_cache.owning_env != env)
			continue;
		return jclass_cache;
	}

	is_writing_JClass_caches = true;
	JClass_caches.push_back({env, {}});
	JClassCache& jclass_cache = *(JClass_caches.end() - 1);
	is_writing_JClass_caches = false;
	return jclass_cache;
}


bool Ripterms::JavaClassV2::init()
{
	JClass_caches.reserve(50);
	JNIFrame jni_frame(Ripterms::p_env, 100);
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
		jclass javaClass = findClass(classContent["obfuscated"], Ripterms::p_env);
		if (!javaClass) continue;
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
				std::cerr << "Failed to find field ID: " + std::string(field["name"]) << '\n'
					<< "For class: " << className << '\n';
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
				std::cerr << "Failed to find method ID: " + std::string(method["name"]) << '\n'
					<< "For class: " << className << '\n';
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
	if (Ripterms::p_env) //can't think of a way to clear cache of other envs
	{
		JClassCache& env_JClass_cache = get_JClass_cache(Ripterms::p_env);
		for (std::pair<const std::string, jclass>& entry : env_JClass_cache.cached_classes)
		{
			Ripterms::p_env->DeleteGlobalRef(entry.second);
		}
	}
}

Ripterms::JavaClassV2::JavaClassV2(const std::string& class_path) :
	class_path(class_path)
{
}

Ripterms::JavaClassV2::JavaClassV2(const JavaClassV2& otherJavaClass) :
	JavaClassV2(otherJavaClass.class_path)
{
}

jclass Ripterms::JavaClassV2::get_jclass(JNIEnv* env) const
{
	JClassCache& env_JClass_cache = get_JClass_cache(env);
	if (!env_JClass_cache.cached_classes.contains(class_path))
	{
		jclass global_ref = (jclass)env->NewGlobalRef(findClass(getObfuscatedClassName(), env));
		env_JClass_cache.cached_classes.insert({ class_path,  global_ref });
		return global_ref;
	}
	return env_JClass_cache.cached_classes.at(class_path);
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

void Ripterms::JavaClassV2::reload()
{
	JNIFrame jni_frame(Ripterms::p_env, 1);
	auto& classMapping = Ripterms::JavaClassV2::mappings[class_path];
	jclass javaClass = findClass(classMapping["obfuscated"], Ripterms::p_env);
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