#include "Hook.h"
#include <unordered_map>
#include <functional>
#include <thread>

namespace //unique coding style lmao
{
    std::unordered_map<void*, Ripterms::Hook*> hooks{};
    std::unordered_map<void*, void(*)(const Ripterms::JavaHook::JavaParameters& params)> methods_to_hook{};

    //fastcall so that parameters are passed through rcx and rdx (Method* is in rbx, but JavaHook mov rcx, rbx)
    void detour_i2i_entry(void* method_rbx, void* sp_r13, void* thread_r15)
    {
        if (methods_to_hook.contains(method_rbx))
        {
            methods_to_hook[method_rbx]({sp_r13, thread_r15});
        }
        return;
    }
}

void Ripterms::JavaHook::clean()
{
    for (const std::pair<void*, Ripterms::Hook*>& hook : hooks)
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
    return JavaParameters::make_local != nullptr;
}

void Ripterms::JavaHook::add_to_java_hook(jmethodID methodID, void(*callback)(const JavaParameters& params))
{
    // hook size 8 bytes
    // Method* in rbx
    // Method parameters on stack
    // rsp saved in r13 ????
    void* method = *((void**)methodID);
    void* i2i = *((void**)(uint64_t(method) + 0x50));
    std::cout << i2i << std::endl;
    if (!hooks.contains(i2i))
        hooks.insert({ i2i, new Hook(8, i2i, detour_i2i_entry, nullptr, Hook::JAVA_ENTRY_HOOK) });
    methods_to_hook.insert({ method, callback });
}
