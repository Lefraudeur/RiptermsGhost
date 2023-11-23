#include "Hook.h"
#include <unordered_map>
#include <winnt.h>

static void* get_current_JavaThread_ptr();

namespace
{
    std::unordered_map<void*, Ripterms::Hook*> hooks{};

    struct MethodHandle
    {
        void* method = nullptr;
        void* thread = nullptr;
    };

    void* (*compile_method)(MethodHandle* method, int osr_bci, int comp_level, MethodHandle* hot_method_handle, int hot_count, int compile_reason, void* thread) = nullptr; //jdk 17

    void* (*compile_method_old)(MethodHandle method, int osr_bci, int comp_level, MethodHandle hot_method_handle, int hot_count, const char* compile_reason, void* thread) = nullptr; //jdk 8

    jobject(*make_local)(void* thread, void* oop, int alloc_failure) = nullptr;
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
    if (!make_local) return false;

    uint8_t compile_method_pattern[] =
    {
        0x48, 0x89, 0x5C, 0x24, 0x10, 0x48, 0x89, 0x6C, 0x24, 0x18, 0x48, 0x89, 0x74, 0x24, 0x20, 0x41, 0x56, 0x48, 0x83, 0xEC, 0x40, 0x80
    };
    compile_method = (void* (*)(MethodHandle*, int, int, MethodHandle*, int, int, void*))jvmdll.pattern_scan(compile_method_pattern, sizeof(compile_method_pattern), PAGE_EXECUTE_READ);

    if (!compile_method)
    {
        uint8_t compile_method_old_pattern[] =
        {
            0x48, 0x89, 0x5C, 0x24, 0x90, 0x56, 0x57, 0x41, 0x54, 0x41, 0x55, 0x41, 0x56, 0x48, 0x81, 0xEC
        };
        compile_method_old = (void* (*)(MethodHandle, int, int, MethodHandle, int, const char*, void*))jvmdll.pattern_scan(compile_method_old_pattern, sizeof(compile_method_old_pattern), PAGE_EXECUTE_READ);
    }
    return compile_method != nullptr || compile_method_old != nullptr;
}


void Ripterms::JavaHook::add_to_java_hook(jmethodID methodID, void(*callback)(void* sp, void* j_rarg0, void* j_rarg1, void* j_rarg2, void* j_rarg3, void* j_rarg4, void* j_rarg5, bool* should_return))
{
    void* Java_thread = get_current_JavaThread_ptr();
    void* method = *((void**)methodID);
    uint8_t* code = *((uint8_t**)((uint8_t*)method + 0x48));
    int* access_flags = (int*)((uint8_t*)method + (compile_method ? 0x28 : 0x20));

    *(access_flags) = *(access_flags) & ~0x01000000; //make sure nothing prevents us from compiling
    *(access_flags) = *(access_flags) & ~0x04000000;
    *(access_flags) = *(access_flags) & ~0x02000000;
    *(access_flags) = *(access_flags) & ~0x08000000;

    MethodHandle handle = { method, Java_thread };
    MethodHandle hot_method = { nullptr, nullptr };
    if (compile_method)
        compile_method(&handle, -1, 4, &hot_method, 0, 6, Java_thread);
    else
        compile_method_old(handle, -1, 4, hot_method, 0, "must_be_compiled", Java_thread);

    while (!code || (*(access_flags) & 0x01000000) != 0) //wait for compilation to complete
    {
        method = *((void**)methodID);
        if (method)
        {
            code = *((uint8_t**)((uint8_t*)method + 0x48));
            access_flags = (int*)((uint8_t*)method + (compile_method ? 0x28 : 0x20));
        }
    }

    *(access_flags) |= 0x01000000; // fake put the method on compile queue, to disable recompilation
    *(access_flags) |= 0x04000000; //disable every compiler level
    *(access_flags) |= 0x02000000;
    *(access_flags) |= 0x08000000;

    void* begin = *((void**)(code + (compile_method ? 0xE0 : 0x80))); // verified_entry_point of nmethod (should be used almost all the time)
    if (begin && !hooks.contains(begin))
        hooks.insert({ begin, new Hook(0,begin, callback, nullptr, Hook::JAVA_ENTRY_HOOK) });
    std::cout << begin << '\n';

    begin = *((void**)(code + (compile_method ? 0xD8 : 0x78))); // _entry_point of nmethod
    if (begin && !hooks.contains(begin))
        hooks.insert({ begin, new Hook(0,begin, callback, nullptr, Hook::JAVA_ENTRY_HOOK) });
    std::cout << begin << '\n';
}


jobject Ripterms::JavaHook::j_rarg_to_jobject(void* j_rarg)
{
    return make_local(get_current_JavaThread_ptr(), j_rarg, 0);
}

static void* get_current_JavaThread_ptr()
{
    if (compile_method)
    { //jdk 17
        struct tb
        {
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
        }*teb = (tb*)NtCurrentTeb();

        uint8_t* tls = *((uint8_t**)teb->Reserved1[11] + 9);
        return *((void**)(tls + 32));
    }
    return TlsGetValue(22); //jdk 8
}