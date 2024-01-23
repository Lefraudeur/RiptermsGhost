#include "JavaHook.h"
#include <vector>
#include <Windows.h>
#include "Module.h"
#include <iostream>
#include "../Ripterms.h"

static void* find_correct_hook_place(void* _i2i_entry);
static void common_detour(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel);

struct i2iHookData
{
    void* _i2i_entry = nullptr;
    Ripterms::JavaHook::Midi2iHook* hook = nullptr;
};
static std::vector<i2iHookData> hooked_i2i_entries{};
struct HookedMethod
{
    HotSpot::Method* method = nullptr;
    Ripterms::JavaHook::i2i_detour_t detour = nullptr;
};
static std::vector<HookedMethod> hooked_methods{};

void Ripterms::JavaHook::clean()
{
    for (i2iHookData hk : hooked_i2i_entries)
    {
        delete hk.hook;
    }
    for (HookedMethod hm : hooked_methods)
    {
        int* flags = (int*)hm.method->get_access_flags();
        *flags &= ~(HotSpot::JVM_ACC_NOT_C2_COMPILABLE | HotSpot::JVM_ACC_NOT_C1_COMPILABLE | HotSpot::JVM_ACC_NOT_C2_OSR_COMPILABLE);
    }
}

bool Ripterms::JavaHook::hook(jmethodID methodID, i2i_detour_t detour)
{
    static int runonce = []()->int
    {
            jvmtiCapabilities capabilities{ .can_retransform_classes = JVMTI_ENABLE };
            Ripterms::p_tienv->AddCapabilities(&capabilities);
            return 0;
    }();
    if (!methodID || !detour) 
        return false;

    HotSpot::Method* method = *(HotSpot::Method**)methodID;
    for (HookedMethod& hk : hooked_methods)
    {
        if (hk.method == method)
            return true;
    }
    int* flags = (int*)method->get_access_flags();
    *flags |= (HotSpot::JVM_ACC_NOT_C2_COMPILABLE | HotSpot::JVM_ACC_NOT_C1_COMPILABLE | HotSpot::JVM_ACC_NOT_C2_OSR_COMPILABLE);

    jclass owner = nullptr;
    Ripterms::p_tienv->GetMethodDeclaringClass(methodID, &owner);
    Ripterms::p_tienv->RetransformClasses(1, &owner); //small trick to delete any already compiled / inlined code
    Ripterms::p_env->DeleteLocalRef(owner);

    method = *(HotSpot::Method**)methodID;
    flags = (int*)method->get_access_flags();
    *flags |= (HotSpot::JVM_ACC_NOT_C2_COMPILABLE | HotSpot::JVM_ACC_NOT_C1_COMPILABLE | HotSpot::JVM_ACC_NOT_C2_OSR_COMPILABLE);


    hooked_methods.push_back({ method, detour });

    bool hook_new_i2i = true;
    void* i2i = method->get_i2i_entry();
    for (i2iHookData& hk : hooked_i2i_entries)
    {
        if (hk._i2i_entry == i2i)
            hook_new_i2i = false;
    }


    if (!hook_new_i2i) return true;

    uint8_t* target = (uint8_t*)find_correct_hook_place(i2i);
    if (!target)
    {
        std::cerr << "Failed to find correct i2i hook location\n";
        return false;
    }
    Midi2iHook* hook = new Midi2iHook(target, common_detour);
    if (!hook)
        return false;

    hooked_i2i_entries.push_back({ i2i, hook });
    return true;
}

void* find_correct_hook_place(void* _i2i_entry)
{
    uint8_t pattern[] =
    {
        0x89, 0x84, 0x24, 0x90, 0x90, 0x90, 0x90,
        0x89, 0x84, 0x24, 0x90, 0x90, 0x90, 0x90,
        0x89, 0x84, 0x24, 0x90, 0x90, 0x90, 0x90,
        0x89, 0x84, 0x24, 0x90, 0x90, 0x90, 0x90,
        0x41, 0xC6, 0x87, 0x90, 0x90, 0x90, 0x90, 0x00
    };

    uint8_t* curr = (uint8_t*)_i2i_entry;
    while (curr < (uint8_t*)_i2i_entry + 0x350)
    {
        int matches = 0;
        for (int i = 0; i < sizeof(pattern); ++i)
        {
            if (pattern[i] == 0x90 || pattern[i] == curr[i])
                matches++;
            else
                break;
        }
        if (matches == sizeof(pattern))
            return curr + sizeof(pattern) - 8;
        curr += 1;
    }

    //8: sizeof : mov    BYTE PTR [r15+_do_not_unlock_if_synchronized_offset],0x0
    //we place the hook here because enough size and correct time
    return nullptr;
}

void common_detour(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
    HotSpot::JavaThreadState state = thread->get_thread_state();
    thread->set_thread_state(HotSpot::_thread_in_native);
    for (HookedMethod& hk : hooked_methods)
    {
        if (hk.method == frame->get_method())
            hk.detour(frame, thread, cancel);
    }
    thread->set_thread_state(state);
}

Ripterms::JavaHook::Midi2iHook::Midi2iHook(uint8_t* target, i2i_detour_t detour) :
    target(target)
{
    constexpr int hook_size = 8;
    /*
0:  50                      push   rax
1:  51                      push   rcx
2:  52                      push   rdx
3:  41 50                   push   r8
5:  41 51                   push   r9
7:  41 52                   push   r10
9:  41 53                   push   r11
b:  55                      push   rbp
c:  6a 00                   push   0x0
e:  48 89 e9                mov    rcx,rbp
11: 4c 89 fa                mov    rdx,r15
14: 4c 8d 04 24             lea    r8,[rsp]
18: 48 89 e5                mov    rbp,rsp
1b: 48 83 e4 f0             and    rsp,0xfffffffffffffff0
1f: 48 83 ec 20             sub    rsp,0x20
23: ff 15 3d 00 00 00       call   QWORD PTR [rip+0x3d]        # 0x66
29: 48 89 ec                mov    rsp,rbp
2c: 58                      pop    rax
2d: 48 83 f8 00             cmp    rax,0x0
31: 5d                      pop    rbp
32: 41 5b                   pop    r11
34: 41 5a                   pop    r10
36: 41 59                   pop    r9
38: 41 58                   pop    r8
3a: 5a                      pop    rdx
3b: 59                      pop    rcx
3c: 58                      pop    rax
3d: 0f 84 00 00 00 00       je     0x43
43: 66 48 0f 6e c0          movq   xmm0,rax
48: 4c 8b 6d c0             mov    r13,QWORD PTR [rbp-0x40]
4c: 4c 8b 75 c8             mov    r14,QWORD PTR [rbp-0x38]
50: 48 c7 45 f0 00 00 00    mov    QWORD PTR [rbp-0x10],0x0
57: 00
58: 48 8b 5d f8             mov    rbx,QWORD PTR [rbp-0x8]
5c: 48 89 ec                mov    rsp,rbp
5f: 5d                      pop    rbp
60: 5e                      pop    rsi
61: 48 89 dc                mov    rsp,rbx
64: ff e6                   jmp    rsi
    */
    uint8_t assembly[] =
    { 
        0x50, 0x51, 0x52, 0x41, 0x50, 0x41, 0x51, 0x41, 0x52, 0x41, 0x53, 0x55, 0x6A, 0x00, 0x48, 0x89, 0xE9, 0x4C, 0x89, 0xFA, 0x4C, 
        0x8D, 0x04, 0x24, 0x48, 0x89, 0xE5, 0x48, 0x83, 0xE4, 0xF0, 0x48, 0x83, 0xEC, 0x20, 0xFF, 0x15, 0x3D, 0x00, 0x00, 0x00, 0x48, 
        0x89, 0xEC, 0x58, 0x48, 0x83, 0xF8, 0x00, 0x5D, 0x41, 0x5B, 0x41, 0x5A, 0x41, 0x59, 0x41, 0x58, 0x5A, 0x59, 0x58, 0x0F, 0x84, 
        0x00, 0x00, 0x00, 0x00, 0x66, 0x48, 0x0F, 0x6E, 0xC0, 0x4C, 0x8B, 0x6D, 0xC0, 0x4C, 0x8B, 0x75, 0xC8, 0x48, 0xC7, 0x45, 0xF0, 
        0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x5D, 0xF8, 0x48, 0x89, 0xEC, 0x5D, 0x5E, 0x48, 0x89, 0xDC, 0xFF, 0xE6,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    allocated_assembly = Module::allocate_nearby_memory(target, hook_size + sizeof(assembly), PAGE_EXECUTE_READWRITE);
    if (!allocated_assembly)
    {
        std::cerr << "Failed to allocate memory for i2i hook\n";
        return;
    }
    int32_t jmp_back_delta = (int32_t)(target + hook_size - (allocated_assembly + hook_size + 0x43));
    *(int32_t*)(assembly + 0x3F) = jmp_back_delta;

    *(i2i_detour_t*)(assembly + 0x66) = detour;

    memcpy(allocated_assembly, target, hook_size);
    memcpy(allocated_assembly + hook_size, assembly, sizeof(assembly));
    
    DWORD original_prot = 0;
    VirtualProtect(allocated_assembly, hook_size + sizeof(assembly), PAGE_EXECUTE_READ, &original_prot);

    VirtualProtect(target, 5, PAGE_EXECUTE_READWRITE, &original_prot);
    target[0] = 0xE9U;
    int32_t jmp_detour_delta = (int32_t)(allocated_assembly - (target + 5));
    *(int32_t*)(target + 1) = jmp_detour_delta;
    VirtualProtect(target, 5, original_prot, &original_prot);

    is_error = false;
}

Ripterms::JavaHook::Midi2iHook::~Midi2iHook()
{
    if (is_error)
        return;

    DWORD original = 0;
    if (target[0] == 0xE9U && VirtualProtect(target, 5, PAGE_EXECUTE_READWRITE, &original))
    {
        memcpy(target, allocated_assembly, 5);
        VirtualProtect(target, 5, original, &original);
    }

    VirtualFree(allocated_assembly, 0, MEM_RELEASE);
}
