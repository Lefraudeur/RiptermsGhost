#include "Hook.h"
#include <unordered_map>
#include <winnt.h>
#include <thread>

static void* get_current_JavaThread_ptr();

namespace
{
    std::unordered_map<void*, Ripterms::Hook*> hooks{};
    struct HookData
    {
        void* verified_code_entry_point;
        Ripterms::JavaHook::callback_t callback;
    };
    std::unordered_map<jmethodID, HookData> hooked_methods{};
    bool runchecker = true;

    struct MethodHandle
    {
        void* method = nullptr;
        void* thread = nullptr;
    };

    std::thread checker{};

    void* (*compile_method)(MethodHandle* method, int osr_bci, int comp_level, MethodHandle* hot_method_handle, int hot_count, int compile_reason, void* thread) = nullptr; //jdk 17

    void* (*compile_method_old)(MethodHandle* method, int osr_bci, int comp_level, MethodHandle* hot_method_handle, int hot_count, const char* compile_reason, void* thread) = nullptr; //jdk 8

    jobject(*make_local)(void* thread, void* oop, int alloc_failure) = nullptr;
}

void Ripterms::JavaHook::clean()
{
    runchecker = false;
    if (checker.joinable())
        checker.join();
    for (const std::pair<void*, Ripterms::Hook*> hook : hooks)
    {
        delete hook.second;
    }
    for (const std::pair<jmethodID, HookData>& entry : hooked_methods)
    {
        void* method = *((void**)entry.first);
        int* access_flags = (int*)((uint8_t*)method + (compile_method ? 0x28 : 0x20));
        *(access_flags) &= ~0x01000000; //enable compilation
        *(access_flags) &= ~0x04000000;
        *(access_flags) &= ~0x02000000;
        *(access_flags) &= ~0x08000000;
        if (compile_method)
        {
            unsigned short* _flags = (unsigned short*)((uint8_t*)method + 0x32);
            *_flags &= ~(1 << 2);
        }
        else
        {
            *((uint8_t*)method + 43) &= ~(1 << 4);
        }
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
        const char* must_be_compiled_str_addr = (const char*)jvmdll.pattern_scan((uint8_t*)"must_be_compiled", 16, PAGE_READONLY);
        uint8_t lea_pattern[] =
        {
            0x48, 0x8D,  0x05
        };
        
        for (uint8_t* lea_addr : jvmdll.pattern_scan_all(lea_pattern, sizeof(lea_pattern), PAGE_EXECUTE_READ))
        {
            uint8_t* rip = lea_addr + 7;
            int32_t rip_relative_offset = ((uint8_t*)must_be_compiled_str_addr - rip);
            int32_t lea_offset = *((int32_t*)(lea_addr + 3));
            if (lea_offset != rip_relative_offset)
                continue;
            while (rip[0] != 0xE8)
                rip++;
            uint8_t* rip2 = rip + 5;
            int32_t offset = *((int32_t*)(rip + 1));
            compile_method_old = (void*(*)(MethodHandle*, int, int, MethodHandle*, int, const char*, void*))(rip2 + offset);
            break;
        }
    }

    checker = std::thread([&] //periodically checks if the method has been deoptimized
        {
            JavaVM* jvm = nullptr;
            JNI_GetCreatedJavaVMs(&jvm, 1, nullptr);
            JNIEnv* jni_env = nullptr;
            jvm->AttachCurrentThread((void**)&jni_env, nullptr);
            while (runchecker)
            {
                for (const std::pair<jmethodID, HookData>& entry : hooked_methods)
                {
                    void* method = *((void**)entry.first);
                    if (!method)
                        continue;
                    uint8_t* code = *((uint8_t**)((uint8_t*)method + 0x48));
                    if (!code || *((void**)(code + (compile_method ? 0xE0 : 0x80))) != entry.second.verified_code_entry_point)
                    {
                        int* access_flags = (int*)((uint8_t*)method + (compile_method ? 0x28 : 0x20));
                        *(access_flags) &= ~0x01000000; //enable compilation
                        *(access_flags) &= ~0x04000000;
                        *(access_flags) &= ~0x02000000;
                        *(access_flags) &= ~0x08000000;
                        std::cout << "recompile";
                        add_to_java_hook(entry.first, entry.second.callback);
                    }
                }
            }
        });
    return compile_method != nullptr || compile_method_old != nullptr;
}


void Ripterms::JavaHook::add_to_java_hook(jmethodID methodID, callback_t callback)
{
    void* Java_thread = get_current_JavaThread_ptr();
    void* method = *((void**)methodID);
    while (!method)
        method = *((void**)methodID);
    int* access_flags = (int*)((uint8_t*)method + (compile_method ? 0x28 : 0x20));

    if (compile_method)
    {
        unsigned short* _flags = (unsigned short*)((uint8_t*)method + 0x32);
        *_flags |= (1 << 2); //don't inline
    }
    else
    {
        *((uint8_t*)method + 43) |= (1 << 4); //don't inline java8
    }

    while ((*(access_flags) & 0x01000000) != 0) {}
    method = *((void**)methodID);
    while(!method)
        method = *((void**)methodID);

    uint8_t* _code = *((uint8_t**)((uint8_t*)method + 0x48));
    if (!_code)
    {
        MethodHandle handle = { method, Java_thread };
        MethodHandle hot_method = { nullptr, nullptr };
        if (compile_method)
        {
            compile_method(&handle, -1, 4, &hot_method, 0, 6, Java_thread);
        }
        else
        {
            compile_method_old(&handle, -1, 4, &hot_method, 0, "must_be_compiled", Java_thread);
        }
    }

    for (int i = 0; i < 1000;) //I don't even know, make sure the _code is correct
    {
        method = *((void**)methodID);
        if (!method)
            continue;
        access_flags = (int*)((uint8_t*)method + (compile_method ? 0x28 : 0x20));
        while ((*(access_flags) & 0x01000000) != 0) {}
        void* new_code = *((void**)((uint8_t*)method + 0x48));
        if (new_code && _code && new_code == _code)
            ++i;
        else
            i = 0;
        _code = (uint8_t*)new_code;
    }

    *(access_flags) |= 0x01000000; //disable compilation
    *(access_flags) |= 0x04000000;
    *(access_flags) |= 0x02000000;
    *(access_flags) |= 0x08000000;

    void* begin = *((void**)(_code + (compile_method ? 0xE0 : 0x80)));
    std::cout << begin << std::endl;
    if (begin && !hooks.contains(begin) && callback)
        hooks.insert({ begin, new Hook(0,begin, callback, nullptr, Hook::JAVA_ENTRY_HOOK) });

    hooked_methods[methodID] = {.verified_code_entry_point = begin , .callback = callback};
    /*
    begin = *((void**)(code + (compile_method ? 0xD8 : 0x78))); // _entry_point of nmethod
    if (begin && !hooks.contains(begin) && callback)
        hooks.insert({ begin, new Hook(0,begin, callback, nullptr, Hook::JAVA_ENTRY_HOOK) });
    std::cout << begin << '\n';
    */
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