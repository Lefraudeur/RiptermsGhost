#include "Module.h"
#include <iostream>


Ripterms::Module::Module(const char* module_name) :
	Module(GetModuleHandleA(module_name))
{
}

Ripterms::Module::Module(HMODULE a_module) :
	module(a_module)
{
	GetModuleInformation(GetCurrentProcess(), module, &moduleInfo, sizeof(MODULEINFO));
}

uint8_t* Ripterms::Module::pattern_scan(uint8_t pattern[], int size, int access) const
{
	MEMORY_BASIC_INFORMATION memInfo{};
	for (uint8_t* ptr = (uint8_t*)moduleInfo.lpBaseOfDll;
		ptr < (uint8_t*)moduleInfo.lpBaseOfDll + moduleInfo.SizeOfImage && VirtualQuery(ptr, &memInfo, sizeof(MEMORY_BASIC_INFORMATION));
		ptr = (uint8_t*)memInfo.BaseAddress + memInfo.RegionSize
		)
	{
		if (memInfo.Protect != access)
			continue;
		uint8_t* region_end_addr = (uint8_t*)memInfo.BaseAddress + memInfo.RegionSize;
		for (uint8_t* rg_ptr = (uint8_t*)memInfo.BaseAddress;
			rg_ptr < region_end_addr;)
		{
			int matches = 0;
			for (int i = 0; i < size; i++)
			{
				if (pattern[i] == rg_ptr[i])
					matches++;
				else
					break;
			}
			if (matches == size)
				return rg_ptr;
			rg_ptr += (matches > 1 ? matches : 1);
		}
	}
	return nullptr;
}

std::vector<uint8_t*> Ripterms::Module::pattern_scan_all(uint8_t pattern[], int size, int access) const
{
	std::vector<uint8_t*> results{};
	MEMORY_BASIC_INFORMATION memInfo{};
	for (uint8_t* ptr = (uint8_t*)moduleInfo.lpBaseOfDll;
		ptr < (uint8_t*)moduleInfo.lpBaseOfDll + moduleInfo.SizeOfImage && VirtualQuery(ptr, &memInfo, sizeof(MEMORY_BASIC_INFORMATION));
		ptr = (uint8_t*)memInfo.BaseAddress + memInfo.RegionSize
		)
	{
		if (memInfo.Protect != access)
			continue;
		uint8_t* region_end_addr = (uint8_t*)memInfo.BaseAddress + memInfo.RegionSize;
		for (uint8_t* rg_ptr = (uint8_t*)memInfo.BaseAddress;
			rg_ptr < region_end_addr;)
		{
			int matches = 0;
			for (int i = 0; i < size; i++)
			{
				if (pattern[i] == rg_ptr[i])
					matches++;
				else
					break;
			}
			if (matches == size)
			{
				results.push_back(rg_ptr);
			}
			rg_ptr += (matches > 1 ? matches : 1);
		}
	}
	return results;
}

uint8_t* Ripterms::Module::pattern_scan_text_section(uint8_t* const pattern_start, const int pattern_size, const uint8_t wildcard) const
{
	if (!module) return nullptr;

	for (PIMAGE_SECTION_HEADER section : get_section_headers())
	{
		if (!(section->Characteristics & (IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_CNT_CODE))) continue;
		uint8_t* search_start = (uint8_t*)module + section->VirtualAddress;
		uint8_t* search_end = search_start + section->SizeOfRawData;
		for (uint8_t* curr = search_start; curr < search_end; ++curr)
		{
			for (int i = 0; i < pattern_size; ++i)
			{
				if (curr[i] != pattern_start[i] && pattern_start[i] != wildcard)
					break;
				if (i == pattern_size - 1)
					return curr;
			}
		}
	}
	return nullptr;
}

void* Ripterms::Module::getProcAddress(const char* name)
{
	return GetProcAddress(module, name);
}

Ripterms::Module::operator bool() const
{
	return module && moduleInfo.lpBaseOfDll;
}

uint8_t* Ripterms::Module::allocate_nearby_memory(uint8_t* nearby_addr, int size, int access)
{
	for (int i = 65536;
		i < 0x7FFFFFFF;
		i += 65536)
	{
		uint8_t* allocated = (uint8_t*)VirtualAlloc(nearby_addr + i, size, MEM_COMMIT | MEM_RESERVE, access);
		if (allocated)
			return allocated;
		allocated = (uint8_t*)VirtualAlloc(nearby_addr - i, size, MEM_COMMIT | MEM_RESERVE, access);
		if (allocated)
			return allocated;
	}
	return nullptr;
}

PIMAGE_NT_HEADERS Ripterms::Module::get_nt_headers() const
{
	PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)module;
	return (PIMAGE_NT_HEADERS)((uint8_t*)module + dos_header->e_lfanew);
}

std::vector<PIMAGE_SECTION_HEADER> Ripterms::Module::get_section_headers() const
{
	PIMAGE_NT_HEADERS nt_headers = get_nt_headers();
	int number_of_sections = nt_headers->FileHeader.NumberOfSections;
	std::vector<PIMAGE_SECTION_HEADER> section_headers{};
	section_headers.reserve(number_of_sections);

	PIMAGE_OPTIONAL_HEADER optional_header = &nt_headers->OptionalHeader;
	PIMAGE_SECTION_HEADER section = (PIMAGE_SECTION_HEADER)((uint8_t*)optional_header + nt_headers->FileHeader.SizeOfOptionalHeader);

	for (int i = 0; i < number_of_sections; ++i, ++section)
	{
		section_headers.push_back(section);
	}

	return section_headers;
}
