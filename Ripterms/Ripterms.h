#pragma once
#include <JNI/jni.h>
#include <JNI/jvmti.h>
#include <chrono>
#include <Windows.h>
#include <iostream>

namespace Ripterms
{
	inline HINSTANCE module = nullptr;
	inline HWND window = nullptr;
	enum Version
	{
		UNDEFINED,
		LUNAR_1_7_10,
		LUNAR_1_8_9,
		VANILLA_1_8_9,
		LUNAR_1_16_5,
		FORGE_1_7_10,
		MAJOR_1_8_9,
		MAJOR_1_16_5
	};
	inline Version version = UNDEFINED;
	inline Version majorVersion = UNDEFINED;
	inline JavaVM* p_jvm = nullptr;
	inline JNIEnv* p_env = nullptr;
	inline jvmtiEnv* p_tienv = nullptr;

	class CTimer {
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