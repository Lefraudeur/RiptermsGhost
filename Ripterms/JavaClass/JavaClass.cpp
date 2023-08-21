#include "JavaClass.h"
#include "../Mappings/mappings_lunar_1_7_10.h"
#include "../Mappings/mappings_forge_1_7_10.h"
#include "../Mappings/mappings_lunar_1_8_9.h"
#include "../Mappings/mappings_vanilla_1_8_9.h"
#include "../Mappings/mappings_lunar_1_16_5.h"
#include <iostream>

Ripterms::JavaClass::JavaClass(const std::string& class_path)
{
	if (!fill(class_path)) throw std::exception(("Failed to parse " + class_path).c_str());
}

Ripterms::JavaClass::JavaClass()
{
}

Ripterms::JavaClass::JavaClass(const JavaClass& otherJavaClass)
{
	if (otherJavaClass.javaClass) this->javaClass = (jclass)p_env->NewGlobalRef(otherJavaClass.javaClass);
	else this->javaClass = nullptr;
	this->fields = otherJavaClass.fields;
	this->methods = otherJavaClass.methods;
}

Ripterms::JavaClass::~JavaClass()
{
	if (!Ripterms::p_env) return;
	if (javaClass) p_env->DeleteGlobalRef(javaClass);
}

void Ripterms::JavaClass::clear()
{
	if (javaClass) p_env->DeleteGlobalRef(javaClass);
	javaClass = nullptr;
}

bool Ripterms::JavaClass::fill(const std::string& class_path)
{
	this->class_path = class_path;
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
			std::cerr << "Failed to find method " << std::string(method["obfuscated"]) << std::endl;
			return false;
		}
		this->methods.insert({ std::string(method["name"]), methodID });
	}
	return true;
}

std::string Ripterms::JavaClass::getObfuscatedMethodName(const std::string& unobf_name)
{
	auto classjson = mappings[class_path];
	for (auto& method : classjson["methods"]) {
		if (method["name"] == unobf_name) return method["obfuscated"];
	}
	return std::string();
}

std::string Ripterms::JavaClass::getObfuscatedMethodSig(const std::string& unobf_name)
{
	auto classjson = mappings[class_path];
	for (auto& method : classjson["methods"]) {
		if (method["name"] == unobf_name) return method["signature"];
	}
	return std::string();
}

std::string Ripterms::JavaClass::getObfuscatedFieldName(const std::string& unobf_name)
{
	auto classjson = mappings[class_path];
	for (auto& method : classjson["fields"]) {
		if (method["name"] == unobf_name) return method["obfuscated"];
	}
	return std::string();
}

std::string Ripterms::JavaClass::getObfuscatedFieldSig(const std::string& unobf_name)
{
	auto classjson = mappings[class_path];
	for (auto& method : classjson["fields"]) {
		if (method["name"] == unobf_name) return method["signature"];
	}
	return std::string();
}

std::string Ripterms::JavaClass::getObfuscatedClassName()
{
	return mappings[class_path]["obfuscated"];
}

bool Ripterms::JavaClass::init()
{
	switch (version)
	{
		case LUNAR_1_8_9:
		{
			mappings = Mappings::mappings_lunar_1_8_9;
			break;
		}
		case VANILLA_1_8_9:
		{
			mappings = Mappings::mappings_vanilla_1_8_9;
			break;
		}
		case LUNAR_1_7_10:
		{
			mappings = Mappings::mappings_lunar_1_7_10;
			break;
		}
		case LUNAR_1_16_5:
		{
			mappings = Mappings::mappings_lunar_1_16_5;
			break;
		}
		case FORGE_1_7_10:
		{
			mappings = Mappings::mappings_forge_1_7_10;
			break;
		}
		default:
		{
			std::cerr << "Cannot find mappings for the specified version" << std::endl;
			return false;
		}
	}
	return true;
}

jclass Ripterms::JavaClass::findClass(const std::string& path)
{
	jint class_count = 0;
	jclass* classes = nullptr;
	jclass foundclass = nullptr;
	p_tienv->GetLoadedClasses(&class_count, &classes);
	for (int i = 0; i < class_count; ++i)
	{
		char* signature_buffer = nullptr;
		p_tienv->GetClassSignature(classes[i], &signature_buffer, nullptr);
		std::string signature = signature_buffer;
		p_tienv->Deallocate((unsigned char*)signature_buffer);
		signature = signature.substr(1);
		signature.pop_back();
		if (signature == path)
		{
			foundclass = (jclass)p_env->NewGlobalRef(classes[i]);
		}
		p_env->DeleteLocalRef(classes[i]);
	}
	p_tienv->Deallocate((unsigned char*)classes);
	return foundclass;
}
