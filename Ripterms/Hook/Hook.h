#pragma once
#include <windows.h>
#include <Psapi.h>
#include <iostream>

namespace Ripterms
{
	class Hook
	{
	public:
		enum Mode
		{
			ABSOLUTE_12B_JMP,
			RELATIVE_5B_JMP
		};
		Hook(int a_bytes_to_replace, void* a_target_function_addr, void* a_detour_function_addr, void** a_original_function_addr, Mode a_mode);
		~Hook();
		void remove();

	private:
		void hook_ABSOLUTE_12B_JMP(void* a_detour_function_addr, void** a_original_function_addr);
		void remove_ABSOLUTE_12B_JMP();

		void hook_RELATIVE_5B_JMP(void* a_detour_function_addr, void** a_original_function_addr);
		void remove_RELATIVE_5B_JMP();

		uint8_t* AllocateNearbyMemory(uint8_t* nearby_addr, int size);

		int bytes_to_replace;
		void* target_function_addr;
		uint8_t* our_tmp_instructions;
		uint8_t* allocated_instructions;
		Mode mode;
	};

	class Module
	{
	public:
		Module(const char* module_name);
		Module(HMODULE a_module);

		uint8_t* pattern_scan(uint8_t pattern[], int size) const;
		void* getProcAddress(const char* name);

		operator bool() const;
	private:
		MODULEINFO moduleInfo{};
		HMODULE module = nullptr;
	};

}