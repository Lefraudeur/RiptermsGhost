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
		class JavaParameters
		{
		public:
			inline JavaParameters(void* sp, void* thread, int r8) :
				sp((uint64_t*)sp),
				thread(thread),
				r8(r8)
			{}
			//primitive type only
			template<typename T> inline T get_primitive_at(int index) const
			{
				return *((T*)(sp + index));
			}
			//index from right to left, 0 is last parameter
			inline jobject get_jobject_at(int index) const
			{
				void* oop = *((void**)(sp + index));
				return make_local(thread, oop, 0);
			}

			void* thread;
			inline static jobject(*make_local)(void* thread, void* oop, int alloc_failure) = nullptr;
			uint64_t* sp;
			int r8;
		};

		void clean();
		bool init();
		void add_to_java_hook(jmethodID methodID, void(*callback)(const JavaParameters& params));
	}
}