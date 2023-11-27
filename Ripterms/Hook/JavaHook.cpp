#include "Hook.h"
#include <unordered_map>
#include <winnt.h>
#include <thread>

static uint8_t* generate_detour_code(Ripterms::JavaHook::callback_t callback, uint8_t* original_addr);
static jobject(*make_local)(void* thread, void* oop, int alloc_failure) = nullptr;
struct HookedJavaMethodCache
{
    jmethodID methodID;
    Ripterms::JavaHook::callback_t interpreted_callback;
    uint8_t* prev_i2i_entry = nullptr;
    uint8_t* original_i2i_entry = nullptr;
};

static std::thread JavaHookThread{};
static volatile bool should_run_thread = true; //compiler is dumb so use volatile
static volatile bool request_write_vector = false; //man doesn't know what mutex are
static volatile bool can_write_vector = false;
static std::vector<HookedJavaMethodCache> hookedMethods{}; //man overusing global variables

void Ripterms::JavaHook::clean()
{
    should_run_thread = false;
    if (JavaHookThread.joinable())
        JavaHookThread.join();
}

bool Ripterms::JavaHook::init()
{
    Module jvmdll("jvm.dll");
    uint8_t make_local_pattern[] =
    {
        0x48, 0x85, 0xD2, 0x75, 0x03, 0x33, 0xC0, 0xC3,
        0x48, 0x8B, 0x89, 0xD8, 0x00, 0x00, 0x00, 0xE9,
        0x6C, 0xF7, 0xFF, 0xFF
    };
    make_local = (jobject(*)(void*, void*, int))
        jvmdll.pattern_scan(make_local_pattern, sizeof(make_local_pattern), PAGE_EXECUTE_READ);
    if (!make_local)
    {
        //try second pattern, for lower jvm versions
        uint8_t make_local_pattern2[] =
        {
            0x48, 0x85, 0xD2, 0x75, 0x03, 0x33, 0xC0, 0xC3, 0x48, 0x8B, 0x49
        };
        make_local = (jobject(*)(void*, void*, int))
            jvmdll.pattern_scan(make_local_pattern2, sizeof(make_local_pattern2), PAGE_EXECUTE_READ);
    }
    if (!make_local)
        return false;
    JavaHookThread = std::thread([]
        {
            while (should_run_thread)
            {
                if (request_write_vector)
                {
                    can_write_vector = true;
                    continue;
                }
                can_write_vector = false;
                for (HookedJavaMethodCache& m : hookedMethods)
                {
                    uint8_t* method = *((uint8_t**)m.methodID);
                    if (!method)
                        continue;
                    *((uint8_t**)(method + 0x48)) = nullptr;
                    unsigned short* _flags = (unsigned short*)(method + 0x32);
                    if ((*(_flags) & (1 << 2)) == 0)
                        *_flags |= (1 << 2); //don't inline

                    int* access_flags = (int*)((uint8_t*)method + 0x28);
                    if ((*(access_flags) & 0x01000000) == 0) // no compile
                        *access_flags |= 0x01000000;
                    if ((*(access_flags) & 0x02000000) == 0)
                        *access_flags |= 0x02000000;
                    if ((*(access_flags) & 0x04000000) == 0)
                        *access_flags |= 0x04000000;
                    if ((*(access_flags) & 0x08000000) == 0)
                        *access_flags |= 0x08000000;

                    {
                        uint8_t** p_i2i_entry = (uint8_t**)(method + 0x38);
                        uint8_t* _i2i_entry = *p_i2i_entry;
                        if (_i2i_entry && _i2i_entry != m.prev_i2i_entry)
                        {
                            uint8_t* new_i2i_entry = generate_detour_code(m.interpreted_callback, _i2i_entry);
                            m.original_i2i_entry = _i2i_entry;
                            *p_i2i_entry = new_i2i_entry;
                            if (m.prev_i2i_entry)
                                VirtualFree(m.prev_i2i_entry, 0, MEM_RELEASE);
                            m.prev_i2i_entry = new_i2i_entry;
                        }
                        uint8_t** p_from_interpreted_entry = (uint8_t**)(method + 0x50);
                        *p_from_interpreted_entry = *p_i2i_entry;
                    }
                }
            }

            for (HookedJavaMethodCache& m : hookedMethods)
            {
                uint8_t* method = *((uint8_t**)m.methodID);
                uint8_t** p_i2i_entry = (uint8_t**)(method + 0x38);
                uint8_t** p_from_interpreted_entry = (uint8_t**)(method + 0x50);
                if (m.original_i2i_entry)
                {
                    *p_from_interpreted_entry = m.original_i2i_entry;
                    *p_i2i_entry = m.original_i2i_entry;
                }
                if (m.prev_i2i_entry)
                    VirtualFree(m.prev_i2i_entry, 0, MEM_RELEASE);
            }
        });
    return true;
}


void Ripterms::JavaHook::add_to_java_hook(jmethodID methodID, callback_t interpreted_callback)
{
    for (const HookedJavaMethodCache& m : hookedMethods)
    {
        if (m.methodID == methodID)
            return;
    }
    request_write_vector = true;
    while (!can_write_vector);
    hookedMethods.push_back({ methodID, interpreted_callback });
    request_write_vector = false;
    return;
}


jobject Ripterms::JavaHook::j_rarg_to_jobject(void* j_rarg, void* thread)
{
    return make_local(thread, j_rarg, 0);
}

static uint8_t* generate_detour_code(Ripterms::JavaHook::callback_t callback, uint8_t* original_addr)
{
    DWORD original_protection = 0;
    uint8_t* allocated_instructions = Ripterms::Hook::AllocateNearbyMemory(original_addr, 80);
    if (!allocated_instructions)
        return nullptr;

    uint8_t pre_call[] = //assembly code, save registers, move params to the corresponding registers, prepare stack to call detour
    {
        0x50, 0x51, 0x52, 0x41, 0x50, 0x41, 0x51, 0x41, 0x52, 0x41, 
        0x53, 0x55, 0x6A, 0x00, 0x48, 0x89, 0xE5, 0x48, 0x83, 0xE4, 
        0xF0, 0x6A, 0x00, 0x41, 0x55, 0x41, 0x57, 0x53, 0x55, 0x51, 
        0x56, 0x57, 0x48, 0x8D, 0x4D, 0x48, 0x48, 0x83, 0xEC, 0x20, 0x48, 0xB8
    };
    memcpy(allocated_instructions, pre_call, sizeof(pre_call));
    *((uint64_t*)(allocated_instructions + sizeof(pre_call))) = (uint64_t)callback;
    uint8_t post_call[] = //assembly code, call detour, restore registers and stack, and return or jmp back to continue execution
    {
        0xFF, 0xD0, 0x48, 0x89, 0xEC, 0x58, 0x48, 0x83, 0xF8, 0x00, 0x5D, 0x41,
        0x5B, 0x41, 0x5A, 0x41, 0x59, 0x41, 0x58, 0x5A, 0x59, 0x58, 0x74, 0x01, 0xC3
    };
    memcpy(allocated_instructions + sizeof(pre_call) + 8, post_call, sizeof(post_call));
    allocated_instructions[sizeof(pre_call) + 8 + sizeof(post_call)] = '\xE9';
    int32_t allocated_target_offset = int32_t(original_addr - (allocated_instructions + sizeof(pre_call) + 8 + sizeof(post_call) + 5));
    *((int32_t*)(allocated_instructions + sizeof(pre_call) + 8 + sizeof(post_call) + 1)) = allocated_target_offset;

    if (!VirtualProtect(allocated_instructions, 80, PAGE_EXECUTE_READ, &original_protection))
        return nullptr;

    return allocated_instructions;
}
