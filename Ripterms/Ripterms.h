#pragma once
#include <JNI/jni.h>
#include <JNI/jvmti.h>
#include <chrono>
#include <Windows.h>
#include <json.hpp>
#include "Hook/Hook.h"
#include <type_traits>

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
			MAJOR_1_16_5,
			MAJOR_1_19_4
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
	JNIEnv* get_ct_env_nocache();

	class JNIFrame
	{
	public:
		JNIFrame(JNIEnv* env = Ripterms::p_env, int ref_count = 10);
		~JNIFrame();

		void pop();
		operator bool();
	private:
		JNIEnv* env;
		bool is_success;
	};


	template<std::equality_comparable T, typename... Values, typename = std::enable_if_t<(std::equality_comparable_with<T, Values> && ...)>>
	inline bool is_any_of(T val, Values... values)
	{
		return ((val == values) || ...);
	}
}