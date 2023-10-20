#include "Hook.h"
#include <thread>

Ripterms::Hook::Hook(int a_bytes_to_replace, void* a_target_function_addr, void* a_detour_function_addr, void** a_original_function_addr, Mode a_mode) :
    bytes_to_replace(a_bytes_to_replace),
    target_function_addr(a_target_function_addr),
    our_tmp_instructions(nullptr),
    mode(a_mode),
    allocated_instructions(nullptr)
{
    switch (mode)
    {
    case ABSOLUTE_12B_JMP:
        hook_ABSOLUTE_12B_JMP(a_detour_function_addr, a_original_function_addr);
        break;
    case RELATIVE_5B_JMP:
        hook_RELATIVE_5B_JMP(a_detour_function_addr, a_original_function_addr);
        break;
    }
}

Ripterms::Hook::~Hook()
{
    remove();
}

void Ripterms::Hook::remove()
{
    switch (mode)
    {
    case ABSOLUTE_12B_JMP:
        remove_ABSOLUTE_12B_JMP();
        break;
    case RELATIVE_5B_JMP:
        remove_RELATIVE_5B_JMP();
        break;
    }
}

void Ripterms::Hook::hook_ABSOLUTE_12B_JMP(void* a_detour_function_addr, void** a_original_function_addr)
{
    if (bytes_to_replace < 12)
        throw std::exception("Not enough memory for the jmp instruction");

    DWORD original_protection = 0;
    VirtualProtect(target_function_addr, bytes_to_replace, PAGE_EXECUTE_READWRITE, &original_protection);
    our_tmp_instructions = (uint8_t*)VirtualAlloc(nullptr, bytes_to_replace + 12, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!our_tmp_instructions)
        throw std::exception("Failed to allocate required memory for the hook");

    *a_original_function_addr = our_tmp_instructions;

    // we copy the original instructions to our allocated function, because they are going to be overwritten by the jmp instruction
    memcpy(our_tmp_instructions, target_function_addr, bytes_to_replace);
    // jump back
    our_tmp_instructions[bytes_to_replace] = '\x48'; // mov
    our_tmp_instructions[bytes_to_replace + 1] = '\xB8'; // rax,
    *((uint64_t*)(our_tmp_instructions + bytes_to_replace + 2)) = (uint64_t)target_function_addr + bytes_to_replace;
    our_tmp_instructions[bytes_to_replace + 10] = '\xff'; // jmp
    our_tmp_instructions[bytes_to_replace + 11] = '\xe0'; // rax

    // jump to detour_function_addr
    ((uint8_t*)target_function_addr)[0] = '\x48'; // mov
    ((uint8_t*)target_function_addr)[1] = '\xB8'; // rax
    *((uint64_t*)((uint8_t*)target_function_addr + 2)) = (uint64_t)a_detour_function_addr;
    ((uint8_t*)target_function_addr)[10] = '\xff'; // jmp
    ((uint8_t*)target_function_addr)[11] = '\xe0'; // rax

    if (bytes_to_replace > 12)
        memset(((uint8_t*)target_function_addr) + 12, 0x90, bytes_to_replace - 12); // fill the remaining bytes with NOPs

    VirtualProtect(target_function_addr, bytes_to_replace, original_protection, &original_protection);
    VirtualProtect(our_tmp_instructions, bytes_to_replace + 12, PAGE_EXECUTE, &original_protection);
}

void Ripterms::Hook::remove_ABSOLUTE_12B_JMP()
{
    DWORD original_protection = 0;
    VirtualProtect(our_tmp_instructions, bytes_to_replace + 12, PAGE_EXECUTE_READWRITE, &original_protection);
    VirtualProtect(target_function_addr, bytes_to_replace, PAGE_EXECUTE_READWRITE, &original_protection);
    memcpy(target_function_addr, our_tmp_instructions, bytes_to_replace);
    VirtualProtect(target_function_addr, bytes_to_replace, original_protection, &original_protection);
    VirtualFree(our_tmp_instructions, 0, MEM_RELEASE);
}

void Ripterms::Hook::hook_RELATIVE_5B_JMP(void* a_detour_function_addr, void** a_original_function_addr)
{
    if (bytes_to_replace < 5)
        throw std::exception("Not enough memory for the jmp instruction");

    DWORD original_protection = 0;
    VirtualProtect(target_function_addr, bytes_to_replace, PAGE_EXECUTE_READWRITE, &original_protection);
    our_tmp_instructions = AllocateNearbyMemory((uint8_t*)target_function_addr, 12);
    if (!our_tmp_instructions)
        throw std::exception("Failed to allocate memory for the hook");

    //jmp from our_tmp_instructions to detour function
    our_tmp_instructions[0] = '\x48'; // mov
    our_tmp_instructions[1] = '\xB8'; // rax,
    *((uint64_t*)(our_tmp_instructions + 2)) = (uint64_t)a_detour_function_addr;
    our_tmp_instructions[10] = '\xff'; // jmp
    our_tmp_instructions[11] = '\xe0'; // rax


    allocated_instructions = (uint8_t*)VirtualAlloc(nullptr, bytes_to_replace + 22, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!allocated_instructions)
        throw std::exception("Failed to allocate memory for the hook");
    *a_original_function_addr = allocated_instructions; // where to go once detour returns

    // we copy the original instructions to our allocated instructions, because they are going to be overwritten by the relative jmp instruction
    memcpy(allocated_instructions, target_function_addr, bytes_to_replace);
    // jump back to normal execution flow, by preserving registers and stack
    // mov[rsp - 16], rax
    // mov rax, 0x7e80e42e7d8e1b34
    // push rax
    // mov rax, [rsp - 8]
    // ret
    uint8_t shell_code1[] = { 0x48, 0x89, 0x44, 0x24, 0xf0, 0x48, 0xb8 };
    memcpy(allocated_instructions + bytes_to_replace, shell_code1, 7);
    *((uint64_t*)(allocated_instructions + bytes_to_replace + 7)) = (uint64_t)target_function_addr + bytes_to_replace;
    uint8_t shell_code2[] = { 0x50, 0x48, 0x8B, 0x44, 0x24, 0xF8, 0xC3 };
    memcpy(allocated_instructions + bytes_to_replace + 15, shell_code2, 7);


    // relative jump from target_function_addr to our_tmp_instructions
    uint32_t jmp_offset = uint32_t(our_tmp_instructions - (uint8_t*)target_function_addr - 5); //relative to the rsp, to the end of the jmp so +5
    ((uint8_t*)target_function_addr)[0] = '\xE9'; // jmp
    *((uint32_t*)((uint8_t*)target_function_addr + 1)) = jmp_offset;

    if (bytes_to_replace > 5)
        memset(((uint8_t*)target_function_addr) + 5, 0x90, bytes_to_replace - 5); // fill the remaining bytes with NOPs

    VirtualProtect(target_function_addr, bytes_to_replace, original_protection, &original_protection);
    VirtualProtect(our_tmp_instructions, 12, PAGE_EXECUTE_READ, &original_protection);
    VirtualProtect(allocated_instructions, bytes_to_replace + 22, PAGE_EXECUTE_READ, &original_protection);
}

void Ripterms::Hook::remove_RELATIVE_5B_JMP()
{
    DWORD original_protection = 0;
    VirtualProtect(target_function_addr, bytes_to_replace, PAGE_EXECUTE_READWRITE, &original_protection);

    memcpy(target_function_addr, allocated_instructions, bytes_to_replace);

    VirtualProtect(target_function_addr, bytes_to_replace, original_protection, &original_protection);

    VirtualFree(our_tmp_instructions, 0, MEM_RELEASE);
    VirtualFree(allocated_instructions, 0, MEM_RELEASE);
}

uint8_t* Ripterms::Hook::AllocateNearbyMemory(uint8_t* nearby_addr, int size)
{
    uint8_t* allocated = nullptr;
    uint8_t* max = nearby_addr + 0x7FFFFFFF;
    while (!allocated && (nearby_addr < max))
    {
        allocated = (uint8_t*)VirtualAlloc(nearby_addr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        nearby_addr += 1;
    }
    return allocated;
}
