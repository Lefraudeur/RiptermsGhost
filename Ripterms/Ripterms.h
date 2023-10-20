#pragma once
#include <JNI/jni.h>
#include <JNI/jvmti.h>
#include <chrono>
#include <Windows.h>
#include <json.hpp>
#include "Hook/Hook.h"
#include "Mappings/mappings_lunar_1_8_9.h"
#include "Mappings/mappings_lunar_1_7_10.h"
#include "Mappings/mappings_lunar_1_16_5.h"
#include "Mappings/mappings_vanilla_1_8_9.h"
#include "Mappings/mappings_forge_1_7_10.h"

namespace Ripterms
{
	inline HINSTANCE module = nullptr;
	inline HWND window = nullptr;

	struct Version
	{
		std::string name{};
		const char* mappings_text = nullptr;
		enum
		{
			UNDEFINED,
			MAJOR_1_7_10,
			MAJOR_1_8_9,
			MAJOR_1_16_5
		} type = UNDEFINED;
	};
	inline Version versions[] =
	{
		{"Lunar Client 1.18.2", Mappings::mappings_lunar_1_16_5, Version::MAJOR_1_16_5},
		{"Lunar Client 1.17.1", Mappings::mappings_lunar_1_16_5, Version::MAJOR_1_16_5},
		{"Lunar Client 1.16.5", Mappings::mappings_lunar_1_16_5, Version::MAJOR_1_16_5},
		{"Lunar Client 1.8.9", Mappings::mappings_lunar_1_8_9, Version::MAJOR_1_8_9},
		{"Badlion Minecraft Client", Mappings::mappings_vanilla_1_8_9, Version::MAJOR_1_8_9},
		{"Lunar Client 1.7.10", Mappings::mappings_lunar_1_7_10, Version::MAJOR_1_7_10},
		{"Minecraft 1.7.10", Mappings::mappings_forge_1_7_10, Version::MAJOR_1_7_10},
		{"Paladium", Mappings::mappings_forge_1_7_10, Version::MAJOR_1_7_10}
	};
	inline Version version{};

	inline JavaVM* p_jvm = nullptr;
	inline JNIEnv* p_env = nullptr;
	inline jvmtiEnv* p_tienv = nullptr;

	class CTimer
	{
	public:
		CTimer(std::chrono::milliseconds everyXms);
		bool isElapsed();
		void setEvery(std::chrono::milliseconds everyXms);
		void reset();
	private:
		std::chrono::steady_clock::time_point timerBegin;
		std::chrono::milliseconds targetMs;
	};
	
	HWND getCurrentWindow();
	BOOL init(HMODULE dll);
	void clean();
	void partialClean();
}