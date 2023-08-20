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
		std::string getObfuscatedFieldName(const std::string& unobf_name);
		std::string getObfuscatedClassName();
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
		JavaClass GameSettingsClass{};
		JavaClass ClientBrandRetrieverClass{};
		JavaClass MapClass{};
		JavaClass StringClass{};
		JavaClass ThreadContextClass{};
		JavaClass SystemClass{};
		JavaClass NetworkManagerClass{};
		JavaClass PacketClass{};
		JavaClass MovingObjectPositionClass{};
		JavaClass MovingObjectTypeClass{};
	};

	inline JavaClassCache* classcache = new JavaClassCache();
}