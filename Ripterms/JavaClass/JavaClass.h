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
		void clear();
		static bool init();
		bool fill(const std::string& class_path);
		std::string getObfuscatedMethodName(const std::string& unobf_name);
		jclass javaClass = nullptr;
		std::unordered_map<std::string, jfieldID> fields{};
		std::unordered_map<std::string, jmethodID> methods{};
		static jclass findClass(const std::string& path);
	private:
		std::string class_path{};
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
		JavaClass ClassLoaderClass{};
		JavaClass EntityRendererClass{};
		JavaClass ClassPatcherClass{};
	};

	inline JavaClassCache* classcache = new JavaClassCache();
}