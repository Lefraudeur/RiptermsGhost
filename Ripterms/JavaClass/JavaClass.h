#pragma once
#include "../Ripterms/Ripterms.h"
#include <json.hpp>

namespace Ripterms
{
	class JavaClass
	{
	public:
		JavaClass(const std::string& class_path);
		JavaClass();
		JavaClass(const JavaClass& otherJavaClass);
		~JavaClass();
		static bool init();
		bool fill(const std::string& class_path);
		jclass javaClass = nullptr;
		std::unordered_map<std::string, jfieldID> fields{};
		std::unordered_map<std::string, jmethodID> methods{};
	private:
		static jclass findClass(const std::string& path);
		inline static nlohmann::json mappings{};
	};

	class JavaClassCache
	{
	public:
		JavaClassCache();
		bool fillCache();
		JavaClass ObjectClass{};
		JavaClass CollectionClass{};
		JavaClass ListClass{};
		JavaClass AbstractClientPlayerClass{};
		JavaClass EntityPlayerSPClass{};
		JavaClass MinecraftClass{};
		JavaClass WorldClientClass{};
		JavaClass EntityClass{};
		JavaClass EntityLivingBaseClass{};
		JavaClass EntityPlayerClass{};
		JavaClass Vec3Class{};
		JavaClass WorldClass{};
	};

	inline JavaClassCache* classcache = new JavaClassCache();
}