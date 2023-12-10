#pragma once
#include <JNI/jni.h>
#include <JNI/jvmti.h>
#include <chrono>
#include <Windows.h>
#include <json.hpp>
#include "Hook/Hook.h"

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
	extern Version versions[];
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

	JNIEnv* get_current_thread_env();
}