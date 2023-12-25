#include "Hook.h"


Ripterms::Module::Module(const char* module_name) :
	Module(GetModuleHandleA(module_name))
{
}

Ripterms::Module::Module(HMODULE a_module)
{
	this->module = a_module;
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
				if (pattern[i] == 0x90 || pattern[i] == rg_ptr[i])
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

void* Ripterms::Module::getProcAddress(const char* name)
{
	return GetProcAddress(module, name);
}

Ripterms::Module::operator bool() const
{
	return module && moduleInfo.lpBaseOfDll;
}
