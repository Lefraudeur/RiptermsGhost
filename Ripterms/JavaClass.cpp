#include "Ripterms.h"
#include "Mappings/mappings_lunar_1_8_9.h"
#include <iostream>
#include "../java/lang/Object/Object.h"
#include "../net/minecraft/client/Minecraft/Minecraft.h"
#include "../net/minecraft/client/entity/EntityPlayerSP/EntityPlayerSP.h"
#include "../net/minecraft/client/multiplayer/WorldClient/WorldClient.h"

Ripterms::JavaClass::JavaClass(const std::string& class_path)
{
	fill(class_path);
}

Ripterms::JavaClass::JavaClass()
{
}

Ripterms::JavaClass::JavaClass(const JavaClass& otherJavaClass)
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
		return false;
	}
	this->javaClass = findClass(classjson["obfuscated"]);
	if (!this->javaClass) {
		std::cerr << "Can't find class " << std::string(classjson["obfuscated"]) << std::endl;
		return false;
	}
	for (auto& field : classjson["fields"]) {
		jfieldID fieldID = nullptr;
		if (field["static"] == true) {
			fieldID = p_env->GetStaticFieldID(this->javaClass, std::string(field["obfuscated"]).c_str(), std::string(field["signature"]).c_str());
		}
		else {
			fieldID = p_env->GetFieldID(this->javaClass, std::string(field["obfuscated"]).c_str(), std::string(field["signature"]).c_str());
		}
		if (!fieldID) {
			std::cerr << "Failed to find field " << std::string(field["obfuscated"]) << std::endl;
			return false;
		}
		this->fields.insert({ std::string(field["name"]), fieldID });
	}
	for (auto& method : classjson["methods"]) {
		jmethodID methodID = nullptr;
		if (method["static"] == true) {
			methodID = p_env->GetStaticMethodID(this->javaClass, std::string(method["obfuscated"]).c_str(), std::string(method["signature"]).c_str());
		}
		else {
			methodID = p_env->GetMethodID(this->javaClass, std::string(method["obfuscated"]).c_str(), std::string(method["signature"]).c_str());
		}
		if (!methodID) {
			std::cerr << "Failed to find field " << std::string(method["obfuscated"]) << std::endl;
			return false;
		}
		this->methods.insert({ std::string(method["name"]), methodID });
	}
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
	if (!(
		Object::init() &&
		Minecraft::init() &&
		Entity::init() &&
		EntityLivingBase::init() &&
		EntityPlayer::init() &&
		AbstractClientPlayer::init() &&
		EntityPlayerSP::init() &&
		World::init() &&
		WorldClient::init()
	)) {
		return false;
	}
	return true;
}

jclass Ripterms::JavaClass::findClass(const std::string& path)
{
	jint class_count = 0;
	jclass* classes = nullptr;
	jclass foundclass = nullptr;
	p_tienv->GetLoadedClasses(&class_count, &classes);
	for (int i = 0; i < class_count; ++i) {
		char* signature_buffer = nullptr;
		p_tienv->GetClassSignature(classes[i], &signature_buffer, nullptr);
		std::string signature = signature_buffer;
		p_tienv->Deallocate((unsigned char*)signature_buffer);
		signature = signature.substr(1);
		signature.pop_back();
		if (signature == path) {
			foundclass = classes[i];
			break;
		}
		p_env->DeleteLocalRef(classes[i]);
	}
	p_tienv->Deallocate((unsigned char*)classes);
	return foundclass;
}