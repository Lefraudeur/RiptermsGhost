#include "Hook.h"
#include <unordered_map>
#include <winnt.h>

namespace //unique coding style lmao
{
    std::unordered_map<void*, Ripterms::Hook*> hooks{};

    struct MethodHandle
    {
        void* method = nullptr;
        void* thread = nullptr;
    };

    const char* (*get_thread_name)(void* the_thread) = nullptr;
    void* (*compile_method)(MethodHandle* method, int osr_bci, int comp_level, MethodHandle* hot_method_handle, int hot_count, int compile_reason, void* thread) = nullptr;

    int tls_index = 0;
}

void Ripterms::JavaHook::clean()
{
    for (const std::pair<void*, Ripterms::Hook*> hook : hooks)
    {
        delete hook.second;
    }
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
    JavaParameters::make_local = (jobject(*)(void*, void*, int))
        jvmdll.pattern_scan(make_local_pattern, sizeof(make_local_pattern), PAGE_EXECUTE_READ);
    if (!JavaParameters::make_local)
    {
        //try second pattern, for lower jvm versions
        uint8_t make_local_pattern2[] =
        {
            0x48, 0x85, 0xD2, 0x75, 0x03, 0x33, 0xC0, 0xC3, 0x48, 0x8B, 0x49
        };
        JavaParameters::make_local = (jobject(*)(void*, void*, int))
            jvmdll.pattern_scan(make_local_pattern2, sizeof(make_local_pattern2), PAGE_EXECUTE_READ);
    }
    if (!JavaParameters::make_local) return false;

    uint8_t tls_off_pattern[] =
    {
        0x48, 0x85, 0xC0, 0x74, 0x61, 0x8B, 0x15
    };
    uint8_t* tls_off = jvmdll.pattern_scan(tls_off_pattern, sizeof(tls_off_pattern), PAGE_EXECUTE_READ);
    uint8_t* rip = tls_off + 7 + 4;
    int32_t rip_offset = *((int32_t*)(tls_off + 7));
    tls_index = *((int*)(rip + rip_offset));

    uint8_t get_thread_name_pattern[] =
    {
        0x48, 0x89, 0x5C, 0x24, 0x08, 0x57, 0x48, 0x83, 0xEC, 0x20, 0x8B, 0x05, 0x90, 0x90, 0x90, 0x90, 0x48, 0x8B, 0xF9, 0x83, 0xF8, 0x02
    };
    get_thread_name = (const char*(*)(void*))jvmdll.pattern_scan(get_thread_name_pattern, sizeof(get_thread_name_pattern), PAGE_EXECUTE_READ);


    uint8_t compile_method_pattern[] =
    {
        0x48, 0x89, 0x5C, 0x24, 0x10, 0x48, 0x89, 0x6C, 0x24, 0x18, 0x48, 0x89, 0x74, 0x24, 0x20, 0x41, 0x56, 0x48, 0x83, 0xEC, 0x40, 0x80
    };
    compile_method = (void* (*)(MethodHandle*, int, int, MethodHandle*, int, int, void*))jvmdll.pattern_scan(compile_method_pattern, sizeof(compile_method_pattern), PAGE_EXECUTE_READ);

    return true;
}

void Ripterms::JavaHook::add_to_java_hook(jmethodID methodID, void(*callback)(uint64_t sp, uint64_t j_rarg0, uint64_t j_rarg1, uint64_t j_rarg2))
{
    void* Java_thread = get_current_JavaThread_ptr();
    void* method = *((void**)methodID);


    MethodHandle handle = { method, Java_thread };
    MethodHandle hot_method = { nullptr, nullptr };
    compile_method(&handle, -1, 1, &hot_method, 0, 6, Java_thread);
    uint8_t* code = nullptr;
    while (code == nullptr)
    {
        method = *((void**)methodID);
        if (method)
            code = *((uint8_t**)((uint8_t*)method + 0x48));
    }

    void* begin = *((void**)(code + 0xE0)); // verified_entry_point of nmethod or 0xD8
    if (begin && !hooks.contains(begin))
    {
        hooks.insert({ begin, new Hook(0,begin, callback, nullptr, Hook::JAVA_ENTRY_HOOK) });
        std::cout << begin << std::endl;
    }

    void* begin2 = *((void**)(code + 0xD8)); // verified_entry_point of nmethod or 0xD8
    if (begin2 && !hooks.contains(begin2))
    {
        hooks.insert({ begin2, new Hook(0,begin2, callback, nullptr, Hook::JAVA_ENTRY_HOOK) });
        std::cout << begin2 << std::endl;
    }
}

void* Ripterms::JavaHook::get_current_JavaThread_ptr()
{
    struct tb {
        PVOID Reserved1[12];
        PVOID  ProcessEnvironmentBlock;
        PVOID Reserved2[399];
        BYTE  Reserved3[1952];
        PVOID TlsSlots[64];
        BYTE  Reserved4[8];
        PVOID Reserved5[26];
        PVOID ReservedForOle;
        PVOID Reserved6[4];
        PVOID TlsExpansionSlots;
    }* teb = (tb*)NtCurrentTeb();
    uint8_t* tls = *((uint8_t**)teb->Reserved1[11] + tls_index);
    return *((void**)(tls + 32));
}