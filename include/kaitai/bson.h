#pragma once

// This is a generated file! Please edit source .ksy file and use
// kaitai-struct-compiler to rebuild

#include <kaitai/kaitaistruct.h>
#include <kaitai/kaitaistream.h>

#include <stdint.h>
#include <string>
#include <vector>

class bson_t : public kaitai::kstruct {
public:
    class timestamp_t;
    class bin_data_t;
    class elements_list_t;
    class cstring_t;
    class string_t;
    class element_t;
    class db_pointer_t;
    class code_with_scope_t;
    class f16_t;
    class object_id_t;
    class reg_ex_t;

    bson_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent = nullptr,
           bson_t* p_root = nullptr);
    veles::dbif::ObjectHandle veles_obj;
    ~bson_t();

    int32_t len() const { return m_len; }
    elements_list_t* fields() const { return m_fields; }
    std::string terminator() const { return m_terminator; }
    bson_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }

    class timestamp_t : public kaitai::kstruct {
    public:
        timestamp_t(kaitai::kstream* p_io,
                    bson_t::element_t* p_parent = nullptr,
                    bson_t* p_root = nullptr);
        veles::dbif::ObjectHandle veles_obj;
        ~timestamp_t();
        uint32_t increment() const { return m_increment; }
        uint32_t timestamp() const { return m_timestamp; }
        bson_t* _root() const { return m__root; }
        bson_t::element_t* _parent() const { return m__parent; }
    private:
        uint32_t m_increment;
        uint32_t m_timestamp;
        bson_t* m__root;
        bson_t::element_t* m__parent;
    };

    class bin_data_t : public kaitai::kstruct {
    public:
        class byte_array_deprecated_t;

        enum subtype_t {
            SUBTYPE_GENERIC = 0,
            SUBTYPE_FUNCTION = 1,
            SUBTYPE_BYTE_ARRAY_DEPRECATED = 2,
            SUBTYPE_UUID_DEPRECATED = 3,
            SUBTYPE_UUID = 4,
            SUBTYPE_MD5 = 5,
            SUBTYPE_CUSTOM = 128
        };

        bin_data_t(kaitai::kstream* p_io,
                   bson_t::element_t* p_parent = nullptr,
                   bson_t* p_root = nullptr);
        veles::dbif::ObjectHandle veles_obj;
        ~bin_data_t();

        int32_t len() const { return m_len; }
        subtype_t subtype() const { return m_subtype; }
        std::string raw_content() const { return m__raw_content; }
        byte_array_deprecated_t* content() const { return m_content; }
        bson_t* _root() const { return m__root; }
        bson_t::element_t* _parent() const { return m__parent; }

        class byte_array_deprecated_t : public kaitai::kstruct {
        public:
            byte_array_deprecated_t(kaitai::kstream* p_io,
                                    bson_t::bin_data_t* p_parent = nullptr,
                                    bson_t* p_root = nullptr);
            veles::dbif::ObjectHandle veles_obj;
            ~byte_array_deprecated_t();
            int32_t len() const { return m_len; }
            std::string content() const { return m_content; }
            bson_t* _root() const { return m__root; }
            bson_t::bin_data_t* _parent() const { return m__parent; }
        private:
            int32_t m_len;
            std::string m_content;
            bson_t* m__root;
            bson_t::bin_data_t* m__parent;
        };

    private:
        int32_t m_len;
        subtype_t m_subtype;
        std::string m__raw_content;
        kaitai::kstream* m__io__raw_content;
        byte_array_deprecated_t* m_content;
        bson_t* m__root;
        bson_t::element_t* m__parent;
    };

    class elements_list_t : public kaitai::kstruct {
    public:
        elements_list_t(kaitai::kstream* p_io, bson_t* p_parent = nullptr,
                        bson_t* p_root = nullptr);
        ~elements_list_t();
        std::vector<element_t*>* elements() const { return m_elements; }
        bson_t* _root() const { return m__root; }
        bson_t* _parent() const { return m__parent; }
    private:
        std::vector<element_t*>* m_elements;
        bson_t* m__root;
        bson_t* m__parent;
    };

    class cstring_t : public kaitai::kstruct {
    public:
        cstring_t(kaitai::kstream* p_io,
                  kaitai::kstruct* p_parent = nullptr,
                  bson_t* p_root = nullptr);
        ~cstring_t();
        std::string str() const { return m_str; }
        bson_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    private:
        std::string m_str;
        bson_t* m__root;
        kaitai::kstruct* m__parent;
    };

    class string_t : public kaitai::kstruct {
    public:
        string_t(kaitai::kstream* p_io,
                 kaitai::kstruct* p_parent = nullptr,
                 bson_t* p_root = nullptr);
        veles::dbif::ObjectHandle veles_obj;
        ~string_t();
        int32_t len() const { return m_len; }
        std::string str() const { return m_str; }
        bson_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    private:
        int32_t m_len;
        std::string m_str;
        std::string m_terminator;
        bson_t* m__root;
        kaitai::kstruct* m__parent;
    };

    class element_t : public kaitai::kstruct {
    public:
        enum bson_type_t {
            BSON_TYPE_MIN_KEY = -1,
            BSON_TYPE_END_OF_OBJECT = 0,
            BSON_TYPE_NUMBER_DOUBLE = 1,
            BSON_TYPE_STRING = 2,
            BSON_TYPE_DOCUMENT = 3,
            BSON_TYPE_ARRAY = 4,
            BSON_TYPE_BIN_DATA = 5,
            BSON_TYPE_UNDEFINED = 6,
            BSON_TYPE_OBJECT_ID = 7,
            BSON_TYPE_BOOLEAN = 8,
            BSON_TYPE_UTC_DATETIME = 9,
            BSON_TYPE_JST_NULL = 10,
            BSON_TYPE_REG_EX = 11,
            BSON_TYPE_DB_POINTER = 12,
            BSON_TYPE_JAVASCRIPT = 13,
            BSON_TYPE_SYMBOL = 14,
            BSON_TYPE_CODE_WITH_SCOPE = 15,
            BSON_TYPE_NUMBER_INT = 16,
            BSON_TYPE_TIMESTAMP = 17,
            BSON_TYPE_NUMBER_LONG = 18,
            BSON_TYPE_NUMBER_DECIMAL = 19,
            BSON_TYPE_MAX_KEY = 127
        };

        element_t(kaitai::kstream* p_io,
                  bson_t::elements_list_t* p_parent = nullptr,
                  bson_t* p_root = nullptr);
        veles::dbif::ObjectHandle veles_obj;
        ~element_t();

        bson_type_t type_byte() const { return m_type_byte; }
        cstring_t* name() const { return m_name; }
        bson_t* _root() const { return m__root; }
        bson_t::elements_list_t* _parent() const { return m__parent; }

    private:
        bson_type_t m_type_byte;
        cstring_t* m_name;
        double m_content_double;
        int32_t m_content_int32;
        int64_t m_content_int64;
        uint8_t m_content_bool;
        string_t* m_content_string;
        bson_t* m_content_bson;
        bin_data_t* m_content_bin_data;
        object_id_t* m_content_object_id;
        timestamp_t* m_content_timestamp;
        reg_ex_t* m_content_reg_ex;
        db_pointer_t* m_content_db_pointer;
        code_with_scope_t* m_content_code_with_scope;
        f16_t* m_content_f16;
        bson_t::elements_list_t* m__parent;
        bson_t* m__root;
    };

    class object_id_t : public kaitai::kstruct {
    public:
        object_id_t(kaitai::kstream* p_io,
                    kaitai::kstruct* p_parent = nullptr,
                    bson_t* p_root = nullptr);
        veles::dbif::ObjectHandle veles_obj;
        ~object_id_t();
        uint32_t epoch_time() const { return m_epoch_time; }
        std::string machine_id() const { return m_machine_id; }
        uint16_t process_id() const { return m_process_id; }
        std::string counter() const { return m_counter; }
        bson_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    private:
        uint32_t m_epoch_time;
        std::string m_machine_id;
        uint16_t m_process_id;
        std::string m_counter;
        bson_t* m__root;
        kaitai::kstruct* m__parent;
    };

    class reg_ex_t : public kaitai::kstruct {
    public:
        reg_ex_t(kaitai::kstream* p_io,
                 bson_t::element_t* p_parent = nullptr,
                 bson_t* p_root = nullptr);
        veles::dbif::ObjectHandle veles_obj;
        ~reg_ex_t();
        cstring_t* pattern() const { return m_pattern; }
        cstring_t* options() const { return m_options; }
        bson_t* _root() const { return m__root; }
        bson_t::element_t* _parent() const { return m__parent; }
    private:
        cstring_t* m_pattern;
        cstring_t* m_options;
        bson_t* m__root;
        bson_t::element_t* m__parent;
    };

    class db_pointer_t : public kaitai::kstruct {
    public:
        db_pointer_t(kaitai::kstream* p_io,
                     bson_t::element_t* p_parent = nullptr,
                     bson_t* p_root = nullptr);
        veles::dbif::ObjectHandle veles_obj;
        ~db_pointer_t();
        string_t* ns() const { return m_ns; }
        object_id_t* id() const { return m_id; }
        bson_t* _root() const { return m__root; }
        bson_t::element_t* _parent() const { return m__parent; }
    private:
        string_t* m_ns;
        object_id_t* m_id;
        bson_t* m__root;
        bson_t::element_t* m__parent;
    };

    class code_with_scope_t : public kaitai::kstruct {
    public:
        code_with_scope_t(kaitai::kstream* p_io,
                          bson_t::element_t* p_parent = nullptr,
                          bson_t* p_root = nullptr);
        veles::dbif::ObjectHandle veles_obj;
        ~code_with_scope_t();
        int32_t id() const { return m_id; }
        string_t* source() const { return m_source; }
        bson_t* scope() const { return m_scope; }
        bson_t* _root() const { return m__root; }
        bson_t::element_t* _parent() const { return m__parent; }
    private:
        int32_t m_id;
        string_t* m_source;
        bson_t* m_scope;
        bson_t* m__root;
        bson_t::element_t* m__parent;
    };

    class f16_t : public kaitai::kstruct {
    public:
        f16_t(kaitai::kstream* p_io,
              bson_t::element_t* p_parent = nullptr,
              bson_t* p_root = nullptr);
        veles::dbif::ObjectHandle veles_obj;
        ~f16_t();
        std::string raw() const { return m_raw; }
        bson_t* _root() const { return m__root; }
        bson_t::element_t* _parent() const { return m__parent; }
    private:
        std::string m_raw;
        bson_t* m__root;
        bson_t::element_t* m__parent;
    };

private:
    int32_t m_len;
    std::string m__raw_fields;
    kaitai::kstream* m__io__raw_fields;
    elements_list_t* m_fields;
    std::string m_terminator;
    kaitai::kstruct* m__parent;
    bson_t* m__root;
};
