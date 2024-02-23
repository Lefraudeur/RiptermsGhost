#pragma once

#include <cstdint>
#include <string>
#include <JNI/jni.h>

namespace HotSpot
{
    bool init();

    typedef struct {
        const char* typeName;            // The type name containing the given field (example: "Klass")
        const char* fieldName;           // The field name within the type           (example: "_name")
        const char* typeString;          // Quoted name of the type of this field (example: "Symbol*";
        // parsed in Java to ensure type correctness
        int32_t  isStatic;               // Indicates whether following field is an offset or an address
        uint64_t offset;                 // Offset of field within structure; only used for nonstatic fields
        void* address;                   // Address of field; only used for static fields
        // ("offset" can not be reused because of apparent solstudio compiler bug
        // in generation of initializer data)
    } VMStructEntry;

    typedef struct {
        const char* typeName;            // Type name (example: "Method")
        const char* superclassName;      // Superclass name, or null if none (example: "oopDesc")
        int32_t isOopType;               // Does this type represent an oop typedef? (i.e., "Method*" or
        // "Klass*", but NOT "Method")
        int32_t isIntegerType;           // Does this type represent an integer type (of arbitrary size)?
        int32_t isUnsigned;              // If so, is it unsigned?
        uint64_t size;                   // Size, in bytes, of the type
    } VMTypeEntry;

    typedef struct {
        const char* name;                // Name of constant (example: "_thread_in_native")
        int32_t value;                   // Value of constant
    } VMIntConstantEntry;

    typedef struct {
        const char* name;                // Name of constant (example: "_thread_in_native")
        uint64_t value;                  // Value of constant
    } VMLongConstantEntry;

    typedef struct {
        const char* name;                // Name of address (example: "SharedRuntime::register_finalizer")
        void* value;                     // Value of address
    } VMAddressEntry;

    enum Flags
    {
        _caller_sensitive = 1 << 0,
        _force_inline = 1 << 1,
        _dont_inline = 1 << 2,
        _hidden = 1 << 3,
        _has_injected_profile = 1 << 4,
        _intrinsic_candidate = 1 << 5,
        _reserved_stack_access = 1 << 6,
        _scoped = 1 << 7
    };

    enum
    {
        // See jvm.h for shared JVM_ACC_XXX access flags

        // HotSpot-specific access flags

        // flags actually put in .class file
        JVM_ACC_WRITTEN_FLAGS = 0x00007FFF,

        // Method* flags
        JVM_ACC_MONITOR_MATCH = 0x10000000,     // True if we know that monitorenter/monitorexit bytecodes match
        JVM_ACC_HAS_MONITOR_BYTECODES = 0x20000000,     // Method contains monitorenter/monitorexit bytecodes
        JVM_ACC_HAS_LOOPS = 0x40000000,     // Method has loops
        JVM_ACC_LOOPS_FLAG_INIT = (int)0x80000000,// The loop flag has been initialized
        JVM_ACC_QUEUED = 0x01000000,     // Queued for compilation
        JVM_ACC_NOT_C2_COMPILABLE = 0x02000000,
        JVM_ACC_NOT_C1_COMPILABLE = 0x04000000,
        JVM_ACC_NOT_C2_OSR_COMPILABLE = 0x08000000,
        JVM_ACC_HAS_LINE_NUMBER_TABLE = 0x00100000,
        JVM_ACC_HAS_CHECKED_EXCEPTIONS = 0x00400000,
        JVM_ACC_HAS_JSRS = 0x00800000,
        JVM_ACC_IS_OLD = 0x00010000,     // RedefineClasses() has replaced this method
        JVM_ACC_IS_OBSOLETE = 0x00020000,     // RedefineClasses() has made method obsolete
        JVM_ACC_IS_PREFIXED_NATIVE = 0x00040000,     // JVMTI has prefixed this native method
        JVM_ACC_ON_STACK = 0x00080000,     // RedefineClasses() was used on the stack
        JVM_ACC_IS_DELETED = 0x00008000,     // RedefineClasses() has deleted this method

        // Klass* flags
        JVM_ACC_HAS_MIRANDA_METHODS = 0x10000000,     // True if this class has miranda methods in it's vtable
        JVM_ACC_HAS_VANILLA_CONSTRUCTOR = 0x20000000,     // True if klass has a vanilla default constructor
        JVM_ACC_HAS_FINALIZER = 0x40000000,     // True if klass has a non-empty finalize() method
        JVM_ACC_IS_CLONEABLE_FAST = (int)0x80000000,// True if klass implements the Cloneable interface and can be optimized in generated code
        JVM_ACC_HAS_FINAL_METHOD = 0x01000000,     // True if klass has final method
        JVM_ACC_IS_SHARED_CLASS = 0x02000000,     // True if klass is shared
        JVM_ACC_IS_HIDDEN_CLASS = 0x04000000,     // True if klass is hidden
        JVM_ACC_IS_VALUE_BASED_CLASS = 0x08000000,     // True if klass is marked as a ValueBased class

        // Klass* and Method* flags
        JVM_ACC_HAS_LOCAL_VARIABLE_TABLE = 0x00200000,

        JVM_ACC_PROMOTED_FLAGS = 0x00200000,     // flags promoted from methods to the holding klass

        // field flags
        // Note: these flags must be defined in the low order 16 bits because
        // InstanceKlass only stores a ushort worth of information from the
        // AccessFlags value.
        // These bits must not conflict with any other field-related access flags
        // (e.g., ACC_ENUM).
        // Note that the class-related ACC_ANNOTATION bit conflicts with these flags.
        JVM_ACC_FIELD_ACCESS_WATCHED = 0x00002000, // field access is watched by JVMTI
        JVM_ACC_FIELD_MODIFICATION_WATCHED = 0x00008000, // field modification is watched by JVMTI
        JVM_ACC_FIELD_INTERNAL = 0x00000400, // internal field, same as JVM_ACC_ABSTRACT
        JVM_ACC_FIELD_STABLE = 0x00000020, // @Stable field, same as JVM_ACC_SYNCHRONIZED and JVM_ACC_SUPER
        JVM_ACC_FIELD_INITIALIZED_FINAL_UPDATE = 0x00000100, // (static) final field updated outside (class) initializer, same as JVM_ACC_NATIVE
        JVM_ACC_FIELD_HAS_GENERIC_SIGNATURE = 0x00000800, // field has generic signature

        JVM_ACC_FIELD_INTERNAL_FLAGS = JVM_ACC_FIELD_ACCESS_WATCHED |
        JVM_ACC_FIELD_MODIFICATION_WATCHED |
        JVM_ACC_FIELD_INTERNAL |
        JVM_ACC_FIELD_STABLE |
        JVM_ACC_FIELD_HAS_GENERIC_SIGNATURE,

        JVM_ACC_PUBLIC       = 0x0001,  /* visible to everyone */
        JVM_ACC_PRIVATE      = 0x0002,  /* visible only to the defining class */
        JVM_ACC_PROTECTED    = 0x0004,  /* visible to subclasses */
        JVM_ACC_STATIC       = 0x0008,  /* instance variable is static */
        JVM_ACC_FINAL        = 0x0010,  /* no further subclassing, overriding */
        JVM_ACC_SYNCHRONIZED = 0x0020,  /* wrap method call in monitor lock */
        JVM_ACC_SUPER        = 0x0020,  /* funky handling of invokespecial */
        JVM_ACC_VOLATILE     = 0x0040,  /* can not cache in registers */
        JVM_ACC_BRIDGE       = 0x0040,  /* bridge method generated by compiler */
        JVM_ACC_TRANSIENT    = 0x0080,  /* not persistent */
        JVM_ACC_VARARGS      = 0x0080,  /* method declared with variable number of args */
        JVM_ACC_NATIVE       = 0x0100,  /* implemented in C */
        JVM_ACC_INTERFACE    = 0x0200,  /* class is an interface */
        JVM_ACC_ABSTRACT     = 0x0400,  /* no definition provided */
        JVM_ACC_STRICT       = 0x0800,  /* strict floating point */
        JVM_ACC_SYNTHETIC    = 0x1000,  /* compiler-generated class, method or field */
        JVM_ACC_ANNOTATION   = 0x2000,  /* annotation type */
        JVM_ACC_ENUM         = 0x4000  /* field is declared as element of enum */
    };

    enum JavaThreadState
    {
        _thread_uninitialized = 0, // should never happen (missing initialization)
        _thread_new = 2, // just starting up, i.e., in process of being initialized
        _thread_new_trans = 3, // corresponding transition state (not used, included for completness)
        _thread_in_native = 4, // running in native code
        _thread_in_native_trans = 5, // corresponding transition state
        _thread_in_vm = 6, // running in VM
        _thread_in_vm_trans = 7, // corresponding transition state
        _thread_in_Java = 8, // running in Java or in stub code
        _thread_in_Java_trans = 9, // corresponding transition state (not used, included for completness)
        _thread_blocked = 10, // blocked in vm
        _thread_blocked_trans = 11, // corresponding transition state
        _thread_max_state = 12  // maximum thread state+1 - used for statistics allocation
    };

    struct DirectoryEntry
    {
        DirectoryEntry* get_next();
        void* get_literal();
    };

    struct Dictionary
    {
        DirectoryEntry** get_buckets();
        int get_table_size();
    };

    struct Symbol
    {
        std::string to_string();
    };

    struct ConstantPool
    {
        void** get_base();
        static int get_size();
        int get_length();
    };

    struct ConstMethod
    {
        ConstantPool* get_constants();
        void set_constants(ConstantPool* _constants);
        unsigned short get_name_index();
        unsigned short get_signature_index();
    };

    struct AccessFlags
    {
        jint _flags;
        bool is_static();
    };

    struct Method
    {
        ConstMethod* get_constMethod();
        std::string get_signature();
        std::string get_name();
        int get_parameters_count();
        AccessFlags* get_access_flags();
        void* get_from_interpreted_entry();
        void set_from_interpreted_entry(void* entry);
        void* get_from_compiled_entry();
        void set_from_compiled_entry(void* entry);
        void* get_i2i_entry();
        unsigned short* get_flags();
        void set_dont_inline(bool enabled);
    };

    struct Array
    {
        int get_length();
        void** get_data();
    };

    struct Array_u2
    {
        int get_length();
        unsigned short* get_data();
    };

    struct Thread
    {
        JNIEnv* get_env();
        uint32_t get_suspend_flags();
        JavaThreadState get_thread_state();
        void set_thread_state(JavaThreadState state);
        static int get_thread_state_offset();
    };

    struct Klass
    {
        Symbol* get_name();
        Method* findMethod(const std::string& method_name, const std::string& method_sig);
        Array_u2* get_fields();
        Array* get_methods();
        ConstantPool* get_constants();
    };

    struct FieldInfo
    {
        unsigned short _data[6];
        unsigned short get_name_index();
        unsigned short get_signature_index();
        unsigned short get_access();
        bool is_internal();
        bool is_public();
        bool is_private();
        bool is_protected();
        bool is_static();
        bool is_final();
    };

    struct frame
    {
        inline static int locals_offset = -56;
        void** get_locals();
        Method* get_method();
    };
};