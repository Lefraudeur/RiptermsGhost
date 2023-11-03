#include "Hook.h"
#include <unordered_map>
#include <functional>
#include <thread>

namespace //unique coding style lmao
{
    std::unordered_map<void*, Ripterms::Hook*> hooks{};
    std::unordered_map<void*, void(*)(const Ripterms::JavaHook::JavaParameters& params)> methods_to_hook{};

    //parameters are passed through rcx and rdx, r8, r9 (Method* is in rbx, but JavaHook mov rcx, rbx)
    void detour_i2i_entry(void* method_rbx, void* sp_r13, void* thread_r15)
    {
        if (!method_rbx || !sp_r13 || !thread_r15)
            return;
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
    if (!JavaParameters::make_local) return false;

    uint8_t pattern[] = //0x90 used as wildcard
    {
        0x48, 0x63, 0xC1, 0x48, 0x8D, 0x0D, 0x06, 0x90, 0x90, 0x00, 0x48, 0x89, 0x14, 0xC1, 0xC3
    };
    uint8_t* pattern_addr = jvmdll.pattern_scan(pattern, sizeof(pattern), PAGE_EXECUTE_READ);
    if (!pattern_addr) return false;
    uint8_t* rip = pattern_addr + 3 + 7;
    int32_t rip_offset = *((int32_t*)(pattern_addr + 6));
    void** _entry_table = (void**)(rip + rip_offset);
    std::cout << "table addr " << _entry_table << std::endl;
    for (int i = 0; i < 36; ++i)
    {
        if (!_entry_table[i])
            continue;
        std::cout << _entry_table[i] << std::endl;
        if (!hooks.contains(_entry_table[i]))
        {
            try
            {
                Hook* hk = new Hook(0, _entry_table[i], detour_i2i_entry, nullptr, Hook::JAVA_ENTRY_HOOK);
                hooks.insert({ _entry_table[i], hk});
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    return true;
}

void Ripterms::JavaHook::add_to_java_hook(jmethodID methodID, void(*callback)(const JavaParameters& params))
{
    void* method = *((void**)methodID);
    methods_to_hook[method] = callback;
}
