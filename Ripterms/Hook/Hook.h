#pragma once
#include <windows.h>
#include <Psapi.h>
#include <iostream>
#include <JNI/jni.h>
#include <vector>
#include <capstone/capstone.h>

namespace Ripterms
{
	class Hook
	{
	public:
		enum Mode
		{
			RELATIVE_5B_JMP,
			JAVA_ENTRY_HOOK
		};
		Hook(int a_bytes_to_replace, void* a_target_function_addr, void* a_detour_function_addr, void** a_original_function_addr, Mode a_mode);
		~Hook();
		void remove();

		static bool init();
		static void clean();

	private:
		void hook_RELATIVE_5B_JMP(void* a_detour_function_addr, void** a_original_function_addr);
		void remove_RELATIVE_5B_JMP();

		void hook_JAVA_ENTRY_HOOK(void* a_detour_function_addr, void** a_original_function_addr);
		void remove_JAVA_ENTRY_HOOK();
		int find_bytes_to_replace(const uint8_t* target);

		uint8_t* AllocateNearbyMemory(uint8_t* nearby_addr, int size);

		int bytes_to_replace;
		void* target_function_addr;
		uint8_t* our_tmp_instructions;
		uint8_t* allocated_instructions;
		Mode mode;
		inline static csh handle = 0;
	};

	class Module
	{
	public:
		Module(const char* module_name);
		Module(HMODULE a_module);

		uint8_t* pattern_scan(uint8_t pattern[], int size, int access = PAGE_EXECUTE_READ) const;
		std::vector<uint8_t*> pattern_scan_all(uint8_t pattern[], int size, int access = PAGE_EXECUTE_READ) const;
		void* getProcAddress(const char* name);

		operator bool() const;
	private:
		MODULEINFO moduleInfo{};
		HMODULE module = nullptr;
	};

	namespace JavaHook
	{
		void clean();
		bool init();
		void add_to_java_hook(jmethodID methodID, void(*callback)(void* sp, void* j_rarg0, void* j_rarg1, void* j_rarg2, void* j_rarg3, void* j_rarg4, void* j_rarg5));
		jobject j_rarg_to_jobject(void* j_rarg);
	}
}