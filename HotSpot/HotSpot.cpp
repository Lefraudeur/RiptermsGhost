#include "HotSpot.hpp"
#include <iostream>
#include <JNI/jni.h>
#include "../Ripterms/Modules/Modules.h"

extern "C" JNIIMPORT HotSpot::VMStructEntry * gHotSpotVMStructs;
extern "C" JNIIMPORT HotSpot::VMTypeEntry* gHotSpotVMTypes;
extern "C" JNIIMPORT HotSpot::VMIntConstantEntry* gHotSpotVMIntConstants;
extern "C" JNIIMPORT HotSpot::VMLongConstantEntry* gHotSpotVMLongConstants;

static HotSpot::VMStructEntry* find_VMStructEntry(const char* typeName, const char* fieldName, bool isStatic);
static HotSpot::VMStructEntry* find_VMStructEntry(const char* fieldName, bool isStatic);
static HotSpot::VMTypeEntry* find_VMTypeEntry(const char* typeName);
static HotSpot::VMIntConstantEntry* find_VMIntConstantEntry(const char* constant_name);
static HotSpot::VMLongConstantEntry* find_VMLongConstantEntry(const char* constant_name);

bool HotSpot::init()
{
    if (!gHotSpotVMStructs || !gHotSpotVMTypes || !gHotSpotVMIntConstants || !gHotSpotVMLongConstants)
    {
        std::cerr << "[-] Failed to find gHotSpotVMStructs\n";
        return false;
    }
    return true;
}

static HotSpot::VMStructEntry* find_VMStructEntry(const char* typeName, const char* fieldName, bool isStatic)
{
    for (HotSpot::VMStructEntry* entry = gHotSpotVMStructs; entry->typeName != nullptr; ++entry)
    {
        if (typeName && std::strcmp(typeName, entry->typeName)) continue;
        if (fieldName && std::strcmp(fieldName, entry->fieldName)) continue;
        if (isStatic != (bool)entry->isStatic) continue;
        std::clog << "[+] Found VMStructEntry: \n"
            "type: " << typeName << "\n"
            "field: " << fieldName << "\n"
            "static: " << (isStatic ? "true" : "false") << "\n"
            "address: " << entry->address << "\n"
            "offset: " << entry->offset << "\n\n";
        return entry;
    }
    std::cerr << "[-] Failed to find VMStructEntry: \n"
        "type: " << typeName << "\n"
        "field: " << fieldName << "\n"
        "static: " << (isStatic ? "true" : "false") << "\n\n";
    return nullptr;
}

static HotSpot::VMStructEntry* find_VMStructEntry(const char* fieldName, bool isStatic)
{
    for (HotSpot::VMStructEntry* entry = gHotSpotVMStructs; entry->typeName != nullptr; ++entry)
    {
        if (fieldName && std::strcmp(fieldName, entry->fieldName)) continue;
        if (isStatic != (bool)entry->isStatic) continue;
        std::clog << "[+] Found VMStructEntry: \n"
            "type: " << entry->typeName << "\n"
            "field: " << fieldName << "\n"
            "static: " << (isStatic ? "true" : "false") << "\n"
            "address: " << entry->address << "\n"
            "offset: " << entry->offset << "\n\n";
    }
    return nullptr;
}

static HotSpot::VMTypeEntry* find_VMTypeEntry(const char* typeName)
{
    for (HotSpot::VMTypeEntry* entry = gHotSpotVMTypes; entry->typeName != nullptr; ++entry)
    {
        if (typeName && std::strcmp(typeName, entry->typeName)) continue;
        std::clog << "[+] Found VMTypeEntry: \n"
            "type: " << typeName << "\n";
        return entry;
    }
    std::cerr << "[-] Failed to find VMTypeEntry: \n"
        "type: " << typeName << "\n\n";
    return nullptr;
}

HotSpot::VMIntConstantEntry* find_VMIntConstantEntry(const char* constant_name)
{
    if (!constant_name || !gHotSpotVMIntConstants) return nullptr;
    for (HotSpot::VMIntConstantEntry* entry = gHotSpotVMIntConstants; entry->name != nullptr; ++entry)
    {
        if (std::strcmp(constant_name, entry->name)) continue;
        std::clog << "[+] Found VMIntConstantEntry: \n"
            "name: " << entry->name << "\n"
            "value: " << entry->value << "\n\n";
        return entry;
    }
    std::cerr << "[-] Failed to find VMTypeEntry: \n"
        "name: " << constant_name << "\n\n";
    return nullptr;
}

HotSpot::VMLongConstantEntry* find_VMLongConstantEntry(const char* constant_name)
{
    if (!constant_name || !gHotSpotVMLongConstants) return nullptr;
    for (HotSpot::VMLongConstantEntry* entry = gHotSpotVMLongConstants; entry->name != nullptr; ++entry)
    {
        if (std::strcmp(constant_name, entry->name)) continue;
        std::clog << "[+] Found VMLongConstantEntry: \n"
            "name: " << entry->name << "\n"
            "value: " << entry->value << "\n\n";
        return entry;
    }
    std::cerr << "[-] Failed to find VMLongEntry: \n"
        "name: " << constant_name << "\n\n";
    return nullptr;
}

std::string HotSpot::Symbol::to_string()
{
    if (!this) return "";

    static VMStructEntry* _body_entry = find_VMStructEntry("Symbol", "_body", false);
    if (!_body_entry) return "";

    static VMStructEntry* _length_entry = find_VMStructEntry("Symbol", "_length", false);
    if (!_length_entry) return "";

    unsigned char* _body = (uint8_t*)this + _body_entry->offset;
    unsigned short _length = *(unsigned short*)((uint8_t*)this + _length_entry->offset);
    std::string class_name((char*)_body, _length);
    return class_name;
}

HotSpot::Symbol* HotSpot::Klass::get_name()
{
    if (!this) return nullptr;

    static VMStructEntry* _name_entry = find_VMStructEntry("Klass", "_name", false);
    if (!_name_entry) return nullptr;

    Symbol* _name = *(Symbol**)((uint8_t*)this + _name_entry->offset);
    return _name;
}

HotSpot::Method* HotSpot::Klass::findMethod(const std::string& method_name, const std::string& method_sig)
{
    Array* _methods = get_methods();
    Method** _data = (Method**)_methods->get_data();
    int _length = _methods->get_length();
    for (int i = 0; i < _length; ++i)
    {
        Method* method = _data[i];
        ConstMethod* cm = method->get_constMethod();
        ConstantPool* cp = cm->get_constants();
        void** b = cp->get_base();
        unsigned short n = cm->get_name_index();
        unsigned short s = cm->get_signature_index();
        Symbol* symbol = (Symbol*)b[n];
        Symbol* symbol_sig = (Symbol*)b[s];
        const std::string& name = symbol->to_string();
        const std::string& signature =  symbol_sig->to_string();
        if (name == method_name && signature == method_sig)
            return method;
    }
    return nullptr;
}

HotSpot::Array_u2* HotSpot::Klass::get_fields()
{
    if (!this) return nullptr;

    static VMStructEntry* _fields_entry = find_VMStructEntry("InstanceKlass", "_fields", false);
    if (!_fields_entry) return nullptr;

    return *(Array_u2**)((uint8_t*)this + _fields_entry->offset);
}

HotSpot::Array* HotSpot::Klass::get_methods()
{
    if (!this) return nullptr;

    static VMStructEntry* _methods_entry = find_VMStructEntry("InstanceKlass", "_methods", false);
    if (!_methods_entry) return nullptr;

    return *(Array**)((uint8_t*)this + _methods_entry->offset);
}

HotSpot::ConstantPool* HotSpot::Klass::get_constants()
{
    if (!this) return nullptr;

    static VMStructEntry* _constants_entry = find_VMStructEntry("InstanceKlass", "_constants", false);
    if (!_constants_entry) return nullptr;

    return *(ConstantPool**)((uint8_t*)this + _constants_entry->offset);
}

int HotSpot::Array::get_length()
{
    if (!this) return 0;

    static VMStructEntry* _length_entry = find_VMStructEntry("Array<Klass*>", "_length", false);
    if (!_length_entry) return 0;

    return *(int*)((uint8_t*)this + _length_entry->offset);
}

void** HotSpot::Array::get_data()
{
    if (!this) return nullptr;

    static VMStructEntry* _data_entry = find_VMStructEntry("Array<Klass*>", "_data", false);
    if (!_data_entry) return nullptr;

    return (void**)((uint8_t*)this + _data_entry->offset);
}

JNIEnv* HotSpot::Thread::get_env()
{
    if (!this) return nullptr;

    static VMStructEntry* _anchor_entry = find_VMStructEntry("JavaThread", "_anchor", false);
    if (!_anchor_entry) return nullptr;

    return (JNIEnv*)((uint8_t*)this + _anchor_entry->offset + 32);
}

HotSpot::ConstMethod* HotSpot::Method::get_constMethod()
{
    if (!this) return nullptr;

    static VMStructEntry* _constMethod_entry = find_VMStructEntry("Method", "_constMethod", false);
    if (!_constMethod_entry) return nullptr;

    return *(ConstMethod**)((uint8_t*)this + _constMethod_entry->offset);
}

std::string HotSpot::Method::get_signature()
{
    if (!this) return "";
    
    ConstMethod* const_method = this->get_constMethod();
    int signature_index = const_method->get_signature_index();
    ConstantPool* cp = const_method->get_constants();
    Symbol** base = (Symbol**)cp->get_base();

    return base[signature_index]->to_string();
}

std::string HotSpot::Method::get_name()
{
    if (!this) return "";

    ConstMethod* const_method = this->get_constMethod();
    int name_index = const_method->get_name_index();
    ConstantPool* cp = const_method->get_constants();
    Symbol** base = (Symbol**)cp->get_base();

    return base[name_index]->to_string();
}

int HotSpot::Method::get_parameters_count()
{
    std::string signature = get_signature();
    if (signature.empty()) return 0;

    size_t parenthesis_index = signature.find(')');
    signature = signature.substr(1, parenthesis_index - 1);

    int param_count = 0;
    for (size_t i = 0; i < signature.size(); ++i)
    {
        char c = signature[i];
        if (c == 'L')
        {
            size_t cp_end = signature.find(';', i);
            i = cp_end;
        }
        ++param_count;
    }

    return param_count;
}

HotSpot::AccessFlags* HotSpot::Method::get_access_flags()
{
    if (!this) return nullptr;

    static VMStructEntry* _access_flags_entry = find_VMStructEntry("Method", "_access_flags", false);
    if (!_access_flags_entry) return nullptr;

    return (AccessFlags*)((uint8_t*)this + _access_flags_entry->offset);
}

void* HotSpot::Method::get_from_interpreted_entry()
{
    static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_from_interpreted_entry", false);
    if (!vm_entry) return nullptr;

    return *(void**)((uint8_t*)this + vm_entry->offset);
}

void HotSpot::Method::set_from_interpreted_entry(void* entry)
{
    static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_from_interpreted_entry", false);
    if (!vm_entry) return;

    *(void**)((uint8_t*)this + vm_entry->offset) = entry;
    return;
}

void* HotSpot::Method::get_from_compiled_entry()
{
    static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_from_compiled_entry", false);
    if (!vm_entry) return nullptr;

    return *(void**)((uint8_t*)this + vm_entry->offset);
}

void HotSpot::Method::set_from_compiled_entry(void* entry)
{
    static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_from_compiled_entry", false);
    if (!vm_entry) return;

    *(void**)((uint8_t*)this + vm_entry->offset) = entry;
    return;
}

void* HotSpot::Method::get_i2i_entry()
{
    static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_i2i_entry", false);
    if (!vm_entry) return nullptr;

    return *(void**)((uint8_t*)this + vm_entry->offset);
}

HotSpot::ConstantPool* HotSpot::ConstMethod::get_constants()
{
    if (!this) return nullptr;

    static VMStructEntry* _constants_entry = find_VMStructEntry("ConstMethod", "_constants", false);
    if (!_constants_entry) return nullptr;

    return *(ConstantPool**)((uint8_t*)this + _constants_entry->offset);
}

void HotSpot::ConstMethod::set_constants(ConstantPool* _constants)
{
    if (!this) return;

    static VMStructEntry* _constants_entry = find_VMStructEntry("ConstMethod", "_constants", false);
    if (!_constants_entry) return;

    *(ConstantPool**)((uint8_t*)this + _constants_entry->offset) = _constants;
}

unsigned short HotSpot::ConstMethod::get_name_index()
{
    if (!this) return 0;

    static VMStructEntry* _name_index_entry = find_VMStructEntry("ConstMethod", "_name_index", false);
    if (!_name_index_entry) return 0;

    return *(unsigned short*)((uint8_t*)this + _name_index_entry->offset);
}

unsigned short HotSpot::ConstMethod::get_signature_index()
{
    if (!this) return 0;

    static VMStructEntry* _signature_index_entry = find_VMStructEntry("ConstMethod", "_signature_index", false);
    if (!_signature_index_entry) return 0;

    return *(unsigned short*)((uint8_t*)this + _signature_index_entry->offset);
}

int HotSpot::ConstantPool::get_size()
{
    static VMTypeEntry* ConstantPool_entry = find_VMTypeEntry("ConstantPool");
    if (!ConstantPool_entry) return 0;

    return (int)ConstantPool_entry->size;
}

void** HotSpot::ConstantPool::get_base()
{
    if (!this) return nullptr;

    int size = get_size();
    if (!size) return nullptr;

    return (void**)((uint8_t*)this + size);
}

int HotSpot::ConstantPool::get_length()
{
    if (!this) return 0;

    static VMStructEntry* entry = find_VMStructEntry("ConstantPool", "_length", false);
    if (!entry) return 0;

    return *(int*)((uint8_t*)this + entry->offset);
}

int HotSpot::Array_u2::get_length()
{
    if (!this) return 0;

    static VMStructEntry* _length_entry = find_VMStructEntry("Array<Klass*>", "_length", false);
    if (!_length_entry) return 0;

    return *(int*)((uint8_t*)this + _length_entry->offset);
}

unsigned short* HotSpot::Array_u2::get_data()
{
    if (!this) return nullptr;

    static VMStructEntry* _data_entry = find_VMStructEntry("Array<u2>", "_data", false);
    if (!_data_entry) return nullptr;

    return (unsigned short*)((uint8_t*)this + _data_entry->offset);
}

unsigned short HotSpot::FieldInfo::get_name_index()
{
    return _data[1];
}

unsigned short HotSpot::FieldInfo::get_signature_index()
{
    return _data[2];
}

unsigned short HotSpot::FieldInfo::get_access()
{
    return _data[0];
}

bool HotSpot::FieldInfo::is_internal()
{
    return (get_access() & JVM_ACC_FIELD_INTERNAL) != 0;
}

bool HotSpot::FieldInfo::is_public()
{
    return (get_access() & JVM_ACC_PUBLIC) != 0;
}

bool HotSpot::FieldInfo::is_private()
{
    return (get_access() & JVM_ACC_PRIVATE) != 0;
}

bool HotSpot::FieldInfo::is_protected()
{
    return (get_access() & JVM_ACC_PROTECTED) != 0;
}

bool HotSpot::FieldInfo::is_static()
{
    return (get_access() & JVM_ACC_STATIC) != 0;
}

bool HotSpot::FieldInfo::is_final()
{
    return (get_access() & JVM_ACC_FINAL) != 0;
}

HotSpot::DirectoryEntry* HotSpot::DirectoryEntry::get_next()
{
    static VMStructEntry* _next_entry = find_VMStructEntry("BasicHashtableEntry<mtInternal>", "_next", false);
    if (!_next_entry) return nullptr;

    return (DirectoryEntry*)(*(intptr_t*)((uint8_t*)this + _next_entry->offset) & -2);
}

void* HotSpot::DirectoryEntry::get_literal()
{
    static VMStructEntry* _literal_entry = find_VMStructEntry("IntptrHashtableEntry", "_literal", false);
    if (!_literal_entry) return nullptr;

    return *(void**)((uint8_t*)this + _literal_entry->offset);
}

HotSpot::DirectoryEntry** HotSpot::Dictionary::get_buckets()
{
    static VMStructEntry* _buckets_entry = find_VMStructEntry("BasicHashtable<mtInternal>", "_buckets", false);
    if (!_buckets_entry) return nullptr;

    return *(DirectoryEntry***)((uint8_t*)this + _buckets_entry->offset);
}

int HotSpot::Dictionary::get_table_size()
{
    static VMStructEntry* _table_size_entry = find_VMStructEntry("BasicHashtable<mtInternal>", "_table_size", false);
    if (!_table_size_entry) return 0;

    return *(int*)((uint8_t*)this + _table_size_entry->offset);
}

bool HotSpot::AccessFlags::is_static()
{
    return (_flags & JVM_ACC_STATIC) != 0;
}

uint32_t HotSpot::Thread::get_suspend_flags()
{
    static VMStructEntry* vm_entry = find_VMStructEntry("Thread", "_suspend_flags", false);
    if (!vm_entry) return 0;

    return *(uint32_t*)((uint8_t*)this + vm_entry->offset);
}

void** HotSpot::frame::get_locals()
{
    if (!this) return nullptr;

    return *(void***)((uint8_t*)this + locals_offset); //48 on java8, 56 on java17
}

HotSpot::Method* HotSpot::frame::get_method()
{
    if (!this) return nullptr;

    return *(Method**)((uint8_t*)this - 24);
}

unsigned short* HotSpot::Method::get_flags()
{
    if (!this) return nullptr;
    static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_flags", false);
    if (!vm_entry)
        return nullptr;
    return (unsigned short*)((uint8_t*)this + vm_entry->offset);
}

void HotSpot::Method::set_dont_inline(bool enabled)
{
    unsigned short* _flags = get_flags();
    if (!_flags)
    {
        static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_intrinsic_id", false);
        if (!vm_entry) return;
        unsigned char* flags = ((uint8_t*)this + vm_entry->offset + 1);
        if (enabled)
            *flags |= (1 << 3);
        else
            *flags &= ~(1 << 3);
        return;
    }

    if (enabled)
        *_flags |= _dont_inline;
    else
        *_flags &= ~_dont_inline;
}

int HotSpot::Thread::get_thread_state_offset()
{
    static VMStructEntry* vm_entry = find_VMStructEntry("JavaThread", "_thread_state", false);
    if (!vm_entry)
        return 0;
    return (int)vm_entry->offset;
}

HotSpot::JavaThreadState HotSpot::Thread::get_thread_state()
{
    if (!this) return _thread_uninitialized;

    return *(JavaThreadState*)((uint8_t*)this + get_thread_state_offset());
}

void HotSpot::Thread::set_thread_state(JavaThreadState state)
{
    if (!this) return;

    *(JavaThreadState*)((uint8_t*)this + get_thread_state_offset()) = state;
}