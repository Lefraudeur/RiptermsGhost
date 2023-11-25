#include "Hook.h"

Ripterms::Hook::Hook(int a_bytes_to_replace, void* a_target_function_addr, void* a_detour_function_addr, void** a_original_function_addr, Mode a_mode) :
    bytes_to_replace(a_bytes_to_replace),
    target_function_addr(a_target_function_addr),
    our_tmp_instructions(nullptr),
    mode(a_mode),
    allocated_instructions(nullptr)
{
    switch (mode)
    {
    case RELATIVE_5B_JMP:
        hook_RELATIVE_5B_JMP(a_detour_function_addr, a_original_function_addr);
        break;
    case JAVA_ENTRY_HOOK:
        hook_JAVA_ENTRY_HOOK(a_detour_function_addr, a_original_function_addr);
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
    case JAVA_ENTRY_HOOK:
        remove_JAVA_ENTRY_HOOK();
        break;
    case RELATIVE_5B_JMP:
        remove_RELATIVE_5B_JMP();
        break;
    }
}

bool Ripterms::Hook::init()
{
    return cs_open(CS_ARCH_X86, CS_MODE_64, &handle) == CS_ERR_OK;
}

void Ripterms::Hook::clean()
{
    cs_close(&handle);
}

void Ripterms::Hook::hook_RELATIVE_5B_JMP(void* a_detour_function_addr, void** a_original_function_addr)
{
    if (bytes_to_replace == 0)
    {
        bytes_to_replace = find_bytes_to_replace((uint8_t*)target_function_addr);
    }

    DWORD original_protection = 0;
    VirtualProtect(target_function_addr, bytes_to_replace, PAGE_EXECUTE_READWRITE, &original_protection);
    our_tmp_instructions = AllocateNearbyMemory((uint8_t*)target_function_addr, 22);
    if (!our_tmp_instructions)
        throw std::exception("Failed to allocate memory for the hook");

    uint8_t shell_code1[] = { 0x48, 0x89, 0x44, 0x24, 0xf0, 0x48, 0xb8 };
    uint8_t shell_code2[] = { 0x50, 0x48, 0x8B, 0x44, 0x24, 0xF8, 0xC3 };

    //jmp from our_tmp_instructions to detour function
    memcpy(our_tmp_instructions, shell_code1, 7);
    *((uint64_t*)(our_tmp_instructions + 7)) = (uint64_t)a_detour_function_addr;
    memcpy(our_tmp_instructions + 15, shell_code2, 7);


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
    memcpy(allocated_instructions + bytes_to_replace, shell_code1, 7);
    *((uint64_t*)(allocated_instructions + bytes_to_replace + 7)) = (uint64_t)target_function_addr + bytes_to_replace;
    memcpy(allocated_instructions + bytes_to_replace + 15, shell_code2, 7);


    // relative jump from target_function_addr to our_tmp_instructions
    int32_t jmp_offset = int32_t(our_tmp_instructions - (uint8_t*)target_function_addr - 5); //relative to the rsp, to the end of the jmp so +5
    ((uint8_t*)target_function_addr)[0] = '\xE9'; // jmp
    *((int32_t*)((uint8_t*)target_function_addr + 1)) = jmp_offset;

    if (bytes_to_replace > 5)
        memset(((uint8_t*)target_function_addr) + 5, 0x90, bytes_to_replace - 5); // fill the remaining bytes with NOPs

    VirtualProtect(target_function_addr, bytes_to_replace, original_protection, &original_protection);
    VirtualProtect(our_tmp_instructions, 22, PAGE_EXECUTE_READ, &original_protection);
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

void Ripterms::Hook::hook_JAVA_ENTRY_HOOK(void* a_detour_function_addr, void** a_original_function_addr)
{
    uint8_t* target = (uint8_t*)target_function_addr;
    if (bytes_to_replace == 0)
    {
        bytes_to_replace = find_bytes_to_replace(target);
    }

    DWORD original_protection = 0;
    allocated_instructions = AllocateNearbyMemory(target, 73 + bytes_to_replace);
    if (!allocated_instructions || !VirtualProtect(target, bytes_to_replace, PAGE_EXECUTE_READWRITE, &original_protection))
        throw std::exception("shit");
    int32_t target_allocated_offset = int32_t(allocated_instructions - (target + 5));

    uint8_t pre_call[] = //assembly code, save registers, move params to the corresponding registers, prepare stack to call detour
    {
        0x50, 0x51, 0x52, 0x41, 0x50, 0x41, 0x51, 0x41, 0x52, 0x41, 0x53, 0x55, 0x6A, 
        0x00, 0x48, 0x89, 0xE5, 0x48, 0x8D, 0x45, 0x00, 0x50, 0x51, 0x56, 0x57, 0x48, 
        0x8D, 0x4D, 0x48, 0x48, 0x83, 0xEC, 0x20, 0x48, 0xB8
    };
    memcpy(allocated_instructions, pre_call, sizeof(pre_call));
    *((uint64_t*)(allocated_instructions + sizeof(pre_call))) = (uint64_t)a_detour_function_addr;
    uint8_t post_call[] = //assembly code, call detour, restore registers and stack, and return or jmp back to continue execution
    {
        0xFF, 0xD0, 0x48, 0x89, 0xEC, 0x58, 0x48, 0x83, 0xF8, 0x00, 0x5D, 0x41, 
        0x5B, 0x41, 0x5A, 0x41, 0x59, 0x41, 0x58, 0x5A, 0x59, 0x58, 0x74, 0x01, 0xC3
    };
    memcpy(allocated_instructions + sizeof(pre_call) + 8, post_call, sizeof(post_call));
    memcpy(allocated_instructions + sizeof(pre_call) + 8 + sizeof(post_call), target, bytes_to_replace);
    allocated_instructions[sizeof(pre_call) + 8 + sizeof(post_call) + bytes_to_replace] = '\xE9';
    int32_t allocated_target_offset = int32_t((target + bytes_to_replace) - (allocated_instructions + sizeof(pre_call) + 8 + sizeof(post_call) + bytes_to_replace + 5));
    *((int32_t*)(allocated_instructions + sizeof(pre_call) + 8 + sizeof(post_call) + bytes_to_replace + 1)) = allocated_target_offset;

    target[0] = '\xE9';
    *((int32_t*)(target + 1)) = target_allocated_offset;

    if (bytes_to_replace > 5)
        memset(target + 5, 0x90, bytes_to_replace - 5); // fill the remaining bytes with NOPs

    if (!VirtualProtect(target, bytes_to_replace, original_protection, &original_protection)
        || !VirtualProtect(allocated_instructions, 73 + bytes_to_replace, PAGE_EXECUTE_READ, &original_protection))
        throw std::exception("shit");
}

void Ripterms::Hook::remove_JAVA_ENTRY_HOOK()
{
    DWORD original_protection = 0;
    VirtualProtect(target_function_addr, bytes_to_replace, PAGE_EXECUTE_READWRITE, &original_protection);
    memcpy(target_function_addr, allocated_instructions + 68, bytes_to_replace);
    VirtualProtect(target_function_addr, bytes_to_replace, original_protection, &original_protection);
    VirtualFree(allocated_instructions, 0, MEM_RELEASE);
}

int Ripterms::Hook::find_bytes_to_replace(const uint8_t* target)
{
    cs_insn* insn = nullptr;
    size_t count = cs_disasm(handle, target, 28, 0, 0, &insn);
    if (!count)
        return 0;

    int bytes_to_replace = 0;
    for (size_t i = 0; i < count; ++i)
    {
        bytes_to_replace += insn[i].size;
        if (bytes_to_replace >= 5)
            break;
    }
    cs_free(insn, count);
    return bytes_to_replace;
}

uint8_t* Ripterms::Hook::AllocateNearbyMemory(uint8_t* nearby_addr, int size)
{
    //this is slow, maybe change the value
    int fail = 0;
    for (int i = 65536;
        i < 0x7FFFFFFF;
        i += 65536)
    {
        uint8_t* allocated = (uint8_t*)VirtualAlloc(nearby_addr + i, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (allocated)
        {
            //std::cout << "fails: " << fail << std::endl;
            return allocated;
        }
        allocated = (uint8_t*)VirtualAlloc(nearby_addr - i, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (allocated)
        {
            //std::cout << "fails: " << fail << std::endl;
            return allocated;
        }
        fail++;
    }
    return nullptr;
}