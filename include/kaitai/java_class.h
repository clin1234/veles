#ifndef JAVA_CLASS_H_
#define JAVA_CLASS_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <kaitai/kaitaistruct.h>
#include <kaitai/kaitaistream.h>

#include <stdint.h>
#include <vector>
#include <sstream>

class java_class_t : public kaitai::kstruct {

public:
    class method_ref_cp_info_t;
    class field_info_t;
    class name_and_type_cp_info_t;
    class utf8_cp_info_t;
    class interface_method_ref_cp_info_t;
    class attribute_t;
    class class_cp_info_t;
    class constant_pool_entry_t;
    class method_info_t;
    class field_ref_cp_info_t;

    java_class_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent = 0, java_class_t* p_root = 0);
    veles::dbif::ObjectHandle veles_obj;
    ~java_class_t();

    class method_ref_cp_info_t : public kaitai::kstruct {

    public:

        method_ref_cp_info_t(kaitai::kstream* p_io, java_class_t::constant_pool_entry_t* p_parent = 0, java_class_t* p_root = 0);
        veles::dbif::ObjectHandle veles_obj;
        ~method_ref_cp_info_t();

    private:
        uint16_t m_class_index;
        uint16_t m_name_and_type_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t class_index() const { return m_class_index; }
        uint16_t name_and_type_index() const { return m_name_and_type_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    class field_info_t : public kaitai::kstruct {

    public:

        field_info_t(kaitai::kstream* p_io, java_class_t* p_parent = 0, java_class_t* p_root = 0);
        veles::dbif::ObjectHandle veles_obj;
        ~field_info_t();

    private:
        uint16_t m_access_flags;
        uint16_t m_name_index;
        uint16_t m_descriptor_index;
        uint16_t m_attributes_count;
        std::vector<attribute_t*>* m_attributes;
        java_class_t* m__root;
        java_class_t* m__parent;

    public:
        uint16_t access_flags() const { return m_access_flags; }
        uint16_t name_index() const { return m_name_index; }
        uint16_t descriptor_index() const { return m_descriptor_index; }
        uint16_t attributes_count() const { return m_attributes_count; }
        std::vector<attribute_t*>* attributes() const { return m_attributes; }
        java_class_t* _root() const { return m__root; }
        java_class_t* _parent() const { return m__parent; }
    };

    class name_and_type_cp_info_t : public kaitai::kstruct {

    public:

        name_and_type_cp_info_t(kaitai::kstream* p_io, java_class_t::constant_pool_entry_t* p_parent = 0, java_class_t* p_root = 0);
        veles::dbif::ObjectHandle veles_obj;
        ~name_and_type_cp_info_t();

    private:
        uint16_t m_name_index;
        uint16_t m_descriptor_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t name_index() const { return m_name_index; }
        uint16_t descriptor_index() const { return m_descriptor_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    class utf8_cp_info_t : public kaitai::kstruct {

    public:

        utf8_cp_info_t(kaitai::kstream* p_io, java_class_t::constant_pool_entry_t* p_parent = 0, java_class_t* p_root = 0);
        veles::dbif::ObjectHandle veles_obj;
        ~utf8_cp_info_t();

    private:
        uint16_t m_str_len;
        std::string m_value;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t str_len() const { return m_str_len; }
        std::string value() const { return m_value; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    class interface_method_ref_cp_info_t : public kaitai::kstruct {

    public:

        interface_method_ref_cp_info_t(kaitai::kstream* p_io, java_class_t::constant_pool_entry_t* p_parent = 0, java_class_t* p_root = 0);
        veles::dbif::ObjectHandle veles_obj;
        ~interface_method_ref_cp_info_t();

    private:
        uint16_t m_class_index;
        uint16_t m_name_and_type_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t class_index() const { return m_class_index; }
        uint16_t name_and_type_index() const { return m_name_and_type_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    // Parent is kaitai::kstruct* so this compiles when used from both
    // field_info_t and method_info_t.
    class attribute_t : public kaitai::kstruct {

    public:

        attribute_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent = 0, java_class_t* p_root = 0);
        veles::dbif::ObjectHandle veles_obj;
        ~attribute_t();

    private:
        uint16_t m_attribute_name_index;
        uint32_t m_attribute_length;
        std::string m_info;
        java_class_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint16_t attribute_name_index() const { return m_attribute_name_index; }
        uint32_t attribute_length() const { return m_attribute_length; }
        std::string info() const { return m_info; }
        java_class_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class class_cp_info_t : public kaitai::kstruct {

    public:

        class_cp_info_t(kaitai::kstream* p_io, java_class_t::constant_pool_entry_t* p_parent = 0, java_class_t* p_root = 0);
        veles::dbif::ObjectHandle veles_obj;
        ~class_cp_info_t();

    private:
        bool f_name;
        constant_pool_entry_t* m_name;

    public:
        constant_pool_entry_t* name();

    private:
        uint16_t m_name_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t name_index() const { return m_name_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    class constant_pool_entry_t : public kaitai::kstruct {

    public:

        enum tag_enum_t {
            TAG_ENUM_UTF8 = 1,
            TAG_ENUM_INTEGER = 3,
            TAG_ENUM_FLOAT = 4,
            TAG_ENUM_LONG = 5,
            TAG_ENUM_DOUBLE = 6,
            TAG_ENUM_CLASS_TYPE = 7,
            TAG_ENUM_STRING = 8,
            TAG_ENUM_FIELD_REF = 9,
            TAG_ENUM_METHOD_REF = 10,
            TAG_ENUM_INTERFACE_METHOD_REF = 11,
            TAG_ENUM_NAME_AND_TYPE = 12,
            TAG_ENUM_METHOD_HANDLE = 15,
            TAG_ENUM_METHOD_TYPE = 16,
            TAG_ENUM_INVOKE_DYNAMIC = 18
        };

        constant_pool_entry_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent = 0, java_class_t* p_root = 0);
        veles::dbif::ObjectHandle veles_obj;
        ~constant_pool_entry_t();

    private:
        tag_enum_t m_tag;
        utf8_cp_info_t* m_utf8_cp_info;
        bool n_utf8_cp_info;
        class_cp_info_t* m_class_cp_info;
        bool n_class_cp_info;
        name_and_type_cp_info_t* m_name_and_type_cp_info;
        bool n_name_and_type_cp_info;
        field_ref_cp_info_t* m_field_ref_cp_info;
        bool n_field_ref_cp_info;
        method_ref_cp_info_t* m_method_ref_cp_info;
        bool n_method_ref_cp_info;
        interface_method_ref_cp_info_t* m_interface_method_ref_cp_info;
        bool n_interface_method_ref_cp_info;
        java_class_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        tag_enum_t tag() const { return m_tag; }
        utf8_cp_info_t* utf8_cp_info() const { return m_utf8_cp_info; }
        class_cp_info_t* class_cp_info() const { return m_class_cp_info; }
        name_and_type_cp_info_t* name_and_type_cp_info() const { return m_name_and_type_cp_info; }
        field_ref_cp_info_t* field_ref_cp_info() const { return m_field_ref_cp_info; }
        method_ref_cp_info_t* method_ref_cp_info() const { return m_method_ref_cp_info; }
        interface_method_ref_cp_info_t* interface_method_ref_cp_info() const { return m_interface_method_ref_cp_info; }
        java_class_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class method_info_t : public kaitai::kstruct {

    public:

        method_info_t(kaitai::kstream* p_io, java_class_t* p_parent = 0, java_class_t* p_root = 0);
        veles::dbif::ObjectHandle veles_obj;
        ~method_info_t();

    private:
        uint16_t m_access_flags;
        uint16_t m_name_index;
        uint16_t m_descriptor_index;
        uint16_t m_attributes_count;
        std::vector<attribute_t*>* m_attributes;
        java_class_t* m__root;
        java_class_t* m__parent;

    public:
        uint16_t access_flags() const { return m_access_flags; }
        uint16_t name_index() const { return m_name_index; }
        uint16_t descriptor_index() const { return m_descriptor_index; }
        uint16_t attributes_count() const { return m_attributes_count; }
        std::vector<attribute_t*>* attributes() const { return m_attributes; }
        java_class_t* _root() const { return m__root; }
        java_class_t* _parent() const { return m__parent; }
    };

    class field_ref_cp_info_t : public kaitai::kstruct {

    public:

        field_ref_cp_info_t(kaitai::kstream* p_io, java_class_t::constant_pool_entry_t* p_parent = 0, java_class_t* p_root = 0);
        veles::dbif::ObjectHandle veles_obj;
        ~field_ref_cp_info_t();

    private:
        uint16_t m_class_index;
        uint16_t m_name_and_type_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t class_index() const { return m_class_index; }
        uint16_t name_and_type_index() const { return m_name_and_type_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

private:
    std::string m_magic;
    uint16_t m_version_minor;
    uint16_t m_version_major;
    uint16_t m_constant_pool_count;
    std::vector<constant_pool_entry_t*>* m_constant_pool;
    uint16_t m_access_flags;
    uint16_t m_this_class;
    uint16_t m_super_class;
    uint16_t m_interfaces_count;
    std::vector<uint16_t>* m_interfaces;
    uint16_t m_fields_count;
    std::vector<field_info_t*>* m_fields;
    uint16_t m_methods_count;
    std::vector<method_info_t*>* m_methods;
    java_class_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::string magic() const { return m_magic; }
    uint16_t version_minor() const { return m_version_minor; }
    uint16_t version_major() const { return m_version_major; }
    uint16_t constant_pool_count() const { return m_constant_pool_count; }
    std::vector<constant_pool_entry_t*>* constant_pool() const { return m_constant_pool; }
    uint16_t access_flags() const { return m_access_flags; }
    uint16_t this_class() const { return m_this_class; }
    uint16_t super_class() const { return m_super_class; }
    uint16_t interfaces_count() const { return m_interfaces_count; }
    std::vector<uint16_t>* interfaces() const { return m_interfaces; }
    uint16_t fields_count() const { return m_fields_count; }
    std::vector<field_info_t*>* fields() const { return m_fields; }
    uint16_t methods_count() const { return m_methods_count; }
    std::vector<method_info_t*>* methods() const { return m_methods; }
    java_class_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // JAVA_CLASS_H_
