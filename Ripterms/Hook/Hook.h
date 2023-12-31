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

		static uint8_t* AllocateNearbyMemory(uint8_t* nearby_addr, int size, int access = PAGE_EXECUTE_READWRITE);

	private:
		void hook_RELATIVE_5B_JMP(void* a_detour_function_addr, void** a_original_function_addr);
		void remove_RELATIVE_5B_JMP();

		void hook_JAVA_ENTRY_HOOK(void* a_detour_function_addr, void** a_original_function_addr);
		void remove_JAVA_ENTRY_HOOK();
		int find_bytes_to_replace(const uint8_t* target);

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
			//        |-------------------------------------------------------|

			//        | c_rarg0   c_rarg1  c_rarg2 c_rarg3 c_rarg4 c_rarg5    |

			//        |-------------------------------------------------------|

			//        | rcx       rdx      r8      r9      rdi*    rsi*       | windows (* not a c_rarg)

			//        | rdi       rsi      rdx     rcx     r8      r9         | solaris/linux

			//        |-------------------------------------------------------|

			//        | j_rarg5   j_rarg0  j_rarg1 j_rarg2 j_rarg3 j_rarg4    |

			//        |-------------------------------------------------------|
		typedef void(*callback_t)(void* sp, bool* should_return, void* rbx, void* thread);

		void clean();
		void partial_clean();
		bool init();

		void add_to_java_hook(jmethodID methodID, callback_t interpreted_callback);

		jobject oop_to_jobject(void* oop, void* thread);
		template<typename T> inline void set_primitive_return_value(bool* should_return, T value)
		{
			*(T*)((uint64_t*)should_return + 8) = value;
		}

		//args right to left (including this pointer)
		template<typename T> inline T get_primitive_arg_at(void* sp, int index)
		{
			return *(T*)((uint64_t*)sp + 1 + index);
		}
		jobject get_jobject_arg_at(void* sp, int index, void* thread);

		JNIEnv* get_env_for_thread(void* thread);

		inline bool is_old_java = false;
	}
}