#pragma once
#include <windows.h>
#include <iostream>
#include <type_traits>
#include <cstdint>
#include "Module.h"
#include "Capstone.h"

namespace Ripterms
{
	template<typename T, typename = typename std::enable_if<std::is_function_v<T>>>
	class Hook
	{
	public:

		Hook(T a_target_function, T a_detour_function, T* a_p_original_function, uint8_t a_bytes_to_replace = 0U) :
			target_function(a_target_function),
			detour_function(a_detour_function),
			original_function(nullptr),
			bytes_to_replace(a_bytes_to_replace),
			target_detour_tramp(nullptr),
			JMP_ABSOLUTE
			{
				0xff, 0x25, 0x00, 0x00, 0x00, 0x00,
				0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
			}
		{
			if (this->bytes_to_replace < RELATIVE_JMP_SIZE)
				this->bytes_to_replace = Capstone::find_bytes_to_replace((uint8_t*)a_target_function);

			target_detour_tramp = Module::allocate_nearby_memory((uint8_t*)target_function, sizeof(JMP_ABSOLUTE), PAGE_EXECUTE_READWRITE);
			if (!target_detour_tramp)
			{
				std::cerr << "Hook: Failed to allocate memory\n";
				return;
			}
			*(T*)(JMP_ABSOLUTE + JMP_ABSOLUTE_DEST_INDEX) = detour_function;
			memcpy(target_detour_tramp, JMP_ABSOLUTE, sizeof(JMP_ABSOLUTE));

			original_function = (T)VirtualAlloc(nullptr, bytes_to_replace + sizeof(JMP_ABSOLUTE), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			if (!original_function)
			{
				std::cerr << "Hook: Failed to allocate memory\n";
				return;
			}
			*a_p_original_function = original_function;
			memcpy(original_function, target_function, bytes_to_replace);
			uint8_t* jmp_back_addr = (uint8_t*)target_function + bytes_to_replace;
			*(uint8_t**)(JMP_ABSOLUTE + JMP_ABSOLUTE_DEST_INDEX) = jmp_back_addr;
			memcpy((uint8_t*)original_function + bytes_to_replace, JMP_ABSOLUTE, sizeof(JMP_ABSOLUTE));

			int32_t jmp_offset = (int32_t)((uint8_t*)target_detour_tramp - ((uint8_t*)target_function + RELATIVE_JMP_SIZE));
			DWORD original_prot = 0;
			if (!VirtualProtect(target_function, 5, PAGE_EXECUTE_READWRITE, &original_prot))
			{
				std::cerr << "Hook: Failed to change target function protection\n";
				return;
			}
			*(uint8_t*)target_function = 0xE9U;
			*(int32_t*)((uint8_t*)target_function + 1) = jmp_offset;
			VirtualProtect(target_function, 5, original_prot, &original_prot);

			is_error = false;
		}

		~Hook()
		{
			if (is_error)
				return;
			DWORD original_prot = 0;
			if (*(uint8_t*)target_function == 0xE9U && VirtualProtect(target_function, bytes_to_replace, PAGE_EXECUTE_READWRITE, &original_prot))
			{
				memcpy(target_function, original_function, bytes_to_replace);
				VirtualProtect(target_function, bytes_to_replace, original_prot, &original_prot);
			}
			VirtualFree(target_detour_tramp, 0, MEM_RELEASE);
			VirtualFree(original_function, 0, MEM_RELEASE);
		}

		bool is_error = true;

	private:

		static const uint8_t RELATIVE_JMP_SIZE = 5U;
		static const uint8_t JMP_ABSOLUTE_DEST_INDEX = 6U;

		uint8_t bytes_to_replace;
		T detour_function;
		T target_function;
		T original_function;
		uint8_t* target_detour_tramp;
		uint8_t JMP_ABSOLUTE[14];
	};
}