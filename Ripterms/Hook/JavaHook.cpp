#include "Hook.h"
#include <unordered_map>
#include "../Ripterms.h"

static uint8_t* generate_detour_code(Ripterms::JavaHook::callback_t callback, uint8_t* original_addr);
static jobject(*make_local)(void* thread, void* oop, int alloc_failure) = nullptr;

struct HookedJavaMethodCache
{
    Ripterms::JavaHook::callback_t interpreted_callback;
    uint8_t* prev_i2i_entry = nullptr;
    uint8_t* original_i2i_entry = nullptr;
};
static std::unordered_map<jmethodID, HookedJavaMethodCache> hookedMethods{}; //man overusing global variables

void Ripterms::JavaHook::clean()
{
    for (const std::pair<jmethodID, HookedJavaMethodCache>& m : hookedMethods)
    {
        uint8_t* method = *((uint8_t**)m.first);
        uint8_t** p_i2i_entry = (uint8_t**)(method + 0x38);
        uint8_t** p_from_interpreted_entry = (uint8_t**)(method + 0x50);
        if (m.second.original_i2i_entry)
        {
            *p_from_interpreted_entry = m.second.original_i2i_entry; //restore entries
            *p_i2i_entry = m.second.original_i2i_entry;
        }
        if (m.second.prev_i2i_entry)
            VirtualFree(m.second.prev_i2i_entry, 0, MEM_RELEASE);

        //unsigned short* _flags = (unsigned short*)(method + 0x32);
        //*_flags &= ~(1 << 2);

        int* access_flags = (int*)(method + 0x28);
        //*access_flags &= ~0x01000000;
        *access_flags &= ~0x02000000;
        *access_flags &= ~0x04000000;
        *access_flags &= ~0x08000000;
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
    if (!make_local)
        return false;
    return true;
}


void Ripterms::JavaHook::add_to_java_hook(jmethodID methodID, callback_t interpreted_callback)
{
    static int runonce = []()->int
    {
        jvmtiCapabilities capabilities{ .can_retransform_classes = JVMTI_ENABLE };
        Ripterms::p_tienv->AddCapabilities(&capabilities);
        return 0;
    }();

    jclass owner = nullptr;
    Ripterms::p_tienv->GetMethodDeclaringClass(methodID, &owner);
    Ripterms::p_tienv->RetransformClasses(1, &owner); //small trick to delete any already compiled / inlined code
    Ripterms::p_env->DeleteLocalRef(owner);

    uint8_t* method = *((uint8_t**)methodID);
    HookedJavaMethodCache& m = hookedMethods[methodID];
    m.interpreted_callback = interpreted_callback;

    unsigned short* _flags = (unsigned short*)(method + 0x32);
    *_flags |= (1 << 2); //don't inline

    int* access_flags = (int*)(method + 0x28);
    //*access_flags |= 0x01000000; //no compile
    *access_flags |= 0x02000000;
    *access_flags |= 0x04000000;
    *access_flags |= 0x08000000;

    uint8_t** p_i2i_entry = (uint8_t**)(method + 0x38);
    uint8_t* _i2i_entry = *p_i2i_entry;
    if (_i2i_entry && _i2i_entry != m.prev_i2i_entry)
    {
        //std::cout << "hooking" << '\n';
        uint8_t* new_i2i_entry = generate_detour_code(m.interpreted_callback, _i2i_entry);
        m.original_i2i_entry = _i2i_entry;
        *p_i2i_entry = new_i2i_entry;
        uint8_t** p_from_interpreted_entry = (uint8_t**)(method + 0x50);
        *p_from_interpreted_entry = *p_i2i_entry;
        uint8_t* _adapter = *(uint8_t**)(method + 0x20);
        uint8_t* _c2i_entry = *(uint8_t**)(_adapter + 0x20);
        uint8_t** p_from_compiled_entry = (uint8_t**)(method + 0x40);
        *p_from_compiled_entry = _c2i_entry;
        if (m.prev_i2i_entry)
            VirtualFree(m.prev_i2i_entry, 0, MEM_RELEASE);
        m.prev_i2i_entry = new_i2i_entry;
        *((uint8_t**)(method + 0x48)) = nullptr; // delete compiled code
    }
    return;
}


jobject Ripterms::JavaHook::oop_to_jobject(void* oop, void* thread)
{
    return make_local(thread, oop, 0);
}

jobject Ripterms::JavaHook::get_jobject_arg_at(void* sp, int index, void* thread)
{
    void* oop = get_primitive_arg_at<void*>(sp, index);
    if (!oop) return nullptr;
    return oop_to_jobject(oop, thread);
}

JNIEnv* Ripterms::JavaHook::get_env_for_thread(void* thread)
{
    return (JNIEnv*)((uint8_t*)thread + 688);
}

static uint8_t* generate_detour_code(Ripterms::JavaHook::callback_t callback, uint8_t* original_addr)
{

    uint8_t assembly[] =
    { 
        0x50, 0x51, 0x52, 0x41, 0x50, 0x41, 0x51, 0x41, 0x52, 0x41, 0x53, 0x55, 0x6A, 0x00, 
        0x48, 0x89, 0xE5, 0x48, 0x83, 0xE4, 0xF0, 0x48, 0x8D, 0x4D, 0x48, 0x48, 0x89, 0xEA, 
        0x49, 0x89, 0xD8, 0x4D, 0x89, 0xF9, 0x48, 0x83, 0xEC, 0x20, 0x48, 0xB8, 0x11, 0x11, 
        0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xFF, 0xD0, 0x48, 0x89, 0xEC, 0x58, 0x48, 0x83, 
        0xF8, 0x00, 0x5D, 0x41, 0x5B, 0x41, 0x5A, 0x41, 0x59, 0x41, 0x58, 0x5A, 0x59, 0x58, 
        0x74, 0x06, 0x5F, 0x4C, 0x89, 0xEC, 0xFF, 0xE7, 0xE9, 0x00, 0x00, 0x00, 0x00 
    };

    DWORD original_protection = 0;
    uint8_t* allocated_instructions = Ripterms::Hook::AllocateNearbyMemory(original_addr, sizeof(assembly));
    if (!allocated_instructions)
        return nullptr;

    memcpy(allocated_instructions, assembly, sizeof(assembly));

    *(void**)(allocated_instructions + 0x28) = callback;
    uint8_t* rip = allocated_instructions + 0x53;
    int32_t offset = original_addr - rip;
    *(int32_t*)(allocated_instructions + 0x4F) = offset;


    if (!VirtualProtect(allocated_instructions, sizeof(assembly), PAGE_EXECUTE_READ, &original_protection))
        return nullptr;

    return allocated_instructions;
}
