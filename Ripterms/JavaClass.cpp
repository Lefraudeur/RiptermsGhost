#include "Ripterms.h"
#include "Mappings/mappings_lunar_1_8_9.h"
#include "../java/lang/Object/Object.h"
#include "../net/minecraft/client/Minecraft/Minecraft.h"
#include <iostream>

Ripterms::JavaClass::JavaClass(const std::string& class_path)
{
	fill(class_path);
}

Ripterms::JavaClass::JavaClass()
{
}

Ripterms::JavaClass::JavaClass(JavaClass& otherJavaClass)
{
	if (otherJavaClass.javaClass) this->javaClass = (jclass)p_env->NewLocalRef(otherJavaClass.javaClass);
	else this->javaClass = nullptr;
	this->fields = otherJavaClass.fields;
	this->methods = otherJavaClass.methods;
}

Ripterms::JavaClass::~JavaClass()
{
	if (javaClass) p_env->DeleteLocalRef(javaClass);
}

bool Ripterms::JavaClass::fill(const std::string& class_path)
{
	auto classjson = mappings[class_path];
	if (classjson.empty()) {
		std::cerr << "Can not find info for class " << class_path << " in mappings" << std::endl;
	}
	this->javaClass = findClass(classjson["obfuscated"]);
	return true;
}

bool Ripterms::JavaClass::fillAll()
{
	if (mappings.empty()) {
		try {
			switch (version) {
			case LUNAR_1_8_9:
				mappings = nlohmann::json::parse(mappings_lunar_1_8_9);
				break;
			default:
				std::cerr << "Cannot find mappings for the specified version" << std::endl;
				return false;
			}
		}
		catch (const nlohmann::json::exception& e) {
			std::cerr << e.what() << std::endl;
			return false;
		}
	}
	Object::init();
	Minecraft::init();
	return true;
}

jclass Ripterms::JavaClass::findClass(const std::string& path)
{
	return jclass();
}