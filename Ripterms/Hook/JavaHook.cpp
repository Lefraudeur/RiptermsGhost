#include "Hook.h"
#include <unordered_map>
#include <functional>
#include <thread>

namespace
{
    std::unordered_map<void*, Ripterms::Hook*> hooks{};
    std::unordered_map<void*, void(*)(void*, void*)> methods_to_hook{};

    //fastcall so that parameters are passed through rcx and rdx (Method* is in rbx, but JavaHook mov rcx, rbx)
    void detour_i2i_entry(void* method_rbx, void* sp_r13)
    {
        if (methods_to_hook.contains(method_rbx))
        {
            methods_to_hook[method_rbx](method_rbx, sp_r13);
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

void Ripterms::JavaHook::add_to_java_hook(jmethodID methodID, void(*callback)(void*, void*))
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