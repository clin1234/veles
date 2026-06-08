// This is a generated file! Please edit source .ksy file and use
// kaitai-struct-compiler to rebuild

#include "kaitai/bson.h"

bson_t::bson_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent,
               bson_t* p_root)
    : kaitai::kstruct(p_io) {
  m__parent = p_parent;
  m__root = (p_root != nullptr) ? p_root : this;
  veles_obj = m__io->startChunk("bson");
  m__io->pushName("len");
  m_len = m__io->read_s4le();
  m__io->popName();
  m__io->pushName("_skip_me_fields");
  m__raw_fields = m__io->read_bytes(m_len - 5);
  m__io->popName();
  m__io__raw_fields =
      new kaitai::kstream(m__io->blob(), m__io->pos() - m__raw_fields.size(),
                          veles_obj, m__io->pos(), m__io->error());
  m_fields = new elements_list_t(m__io__raw_fields, this, m__root);
  m__io->pushName("terminator");
  m_terminator = m__io->ensure_fixed_contents(std::string("\x00", 1));
  m__io->popName();
  m__io->endChunk();
}

bson_t::~bson_t() {
  delete m__io__raw_fields;
  delete m_fields;
}

bson_t::timestamp_t::timestamp_t(kaitai::kstream* p_io,
                                  bson_t::element_t* p_parent,
                                  bson_t* p_root)
    : kaitai::kstruct(p_io) {
  m__parent = p_parent;
  m__root = p_root;
  veles_obj = m__io->startChunk("timestamp");
  m__io->pushName("increment");
  m_increment = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("timestamp");
  m_timestamp = m__io->read_u4le();
  m__io->popName();
  m__io->endChunk();
}

bson_t::timestamp_t::~timestamp_t() {}

bson_t::bin_data_t::bin_data_t(kaitai::kstream* p_io,
                                bson_t::element_t* p_parent, bson_t* p_root)
    : kaitai::kstruct(p_io), m__io__raw_content(nullptr), m_content(nullptr) {
  m__parent = p_parent;
  m__root = p_root;
  veles_obj = m__io->startChunk("bin_data");
  m__io->pushName("len");
  m_len = m__io->read_s4le();
  m__io->popName();
  m__io->pushName("subtype");
  m_subtype = static_cast<subtype_t>(m__io->read_u1());
  m__io->popName();
  if (m_subtype == SUBTYPE_BYTE_ARRAY_DEPRECATED) {
    uint64_t content_start = m__io->pos();
    m__io->pushName("_skip_me_content");
    m__raw_content = m__io->read_bytes(m_len);
    m__io->popName();
    m__io__raw_content =
        new kaitai::kstream(m__io->blob(), content_start, veles_obj,
                            content_start + m_len, m__io->error());
    m_content = new byte_array_deprecated_t(m__io__raw_content, this, m__root);
  } else {
    m__io->pushName("content");
    m__raw_content = m__io->read_bytes(m_len);
    m__io->popName();
  }
  m__io->endChunk();
}

bson_t::bin_data_t::~bin_data_t() {
  delete m__io__raw_content;
  delete m_content;
}

bson_t::bin_data_t::byte_array_deprecated_t::byte_array_deprecated_t(
    kaitai::kstream* p_io, bson_t::bin_data_t* p_parent, bson_t* p_root)
    : kaitai::kstruct(p_io) {
  m__parent = p_parent;
  m__root = p_root;
  veles_obj = m__io->startChunk("byte_array_deprecated");
  m__io->pushName("len");
  m_len = m__io->read_s4le();
  m__io->popName();
  m__io->pushName("content");
  m_content = m__io->read_bytes(m_len);
  m__io->popName();
  m__io->endChunk();
}

bson_t::bin_data_t::byte_array_deprecated_t::~byte_array_deprecated_t() {}

bson_t::elements_list_t::elements_list_t(kaitai::kstream* p_io,
                                          bson_t* p_parent, bson_t* p_root)
    : kaitai::kstruct(p_io) {
  m__parent = p_parent;
  m__root = p_root;
  m_elements = new std::vector<element_t*>();
  while (!m__io->is_eof()) {
    m__io->pushName("elements");
    m_elements->push_back(new element_t(m__io, this, m__root));
    m__io->popName();
  }
}

bson_t::elements_list_t::~elements_list_t() {
  for (auto* e : *m_elements) delete e;
  delete m_elements;
}

bson_t::cstring_t::cstring_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent,
                               bson_t* p_root)
    : kaitai::kstruct(p_io) {
  m__parent = p_parent;
  m__root = p_root;
  m_str = m__io->read_strz("UTF-8", 0, false, true, true);
}

bson_t::cstring_t::~cstring_t() {}

bson_t::string_t::string_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent,
                             bson_t* p_root)
    : kaitai::kstruct(p_io) {
  m__parent = p_parent;
  m__root = p_root;
  veles_obj = m__io->startChunk("string");
  m__io->pushName("len");
  m_len = m__io->read_s4le();
  m__io->popName();
  m__io->pushName("str");
  m_str = m__io->read_str_byte_limit(m_len - 1, "UTF-8");
  m__io->popName();
  m__io->pushName("terminator");
  m_terminator = m__io->ensure_fixed_contents(std::string("\x00", 1));
  m__io->popName();
  m__io->endChunk();
}

bson_t::string_t::~string_t() {}

bson_t::element_t::element_t(kaitai::kstream* p_io,
                               bson_t::elements_list_t* p_parent,
                               bson_t* p_root)
    : kaitai::kstruct(p_io),
      m_content_double(0.0),
      m_content_int32(0),
      m_content_int64(0),
      m_content_bool(0),
      m_content_string(nullptr),
      m_content_bson(nullptr),
      m_content_bin_data(nullptr),
      m_content_object_id(nullptr),
      m_content_timestamp(nullptr),
      m_content_reg_ex(nullptr),
      m_content_db_pointer(nullptr),
      m_content_code_with_scope(nullptr),
      m_content_f16(nullptr) {
  m__parent = p_parent;
  m__root = p_root;
  veles_obj = m__io->startChunk("element");
  m__io->pushName("type_byte");
  m_type_byte = static_cast<bson_type_t>(m__io->read_u1());
  m__io->popName();
  m__io->pushName("name");
  m_name = new cstring_t(m__io, this, m__root);
  m__io->popName();
  switch (m_type_byte) {
  case BSON_TYPE_NUMBER_DOUBLE:
    m__io->pushName("content");
    m_content_double = m__io->read_f8le();
    m__io->popName();
    break;
  case BSON_TYPE_STRING:
  case BSON_TYPE_JAVASCRIPT:
  case BSON_TYPE_SYMBOL:
    m__io->pushName("content");
    m_content_string = new string_t(m__io, this, m__root);
    m__io->popName();
    break;
  case BSON_TYPE_DOCUMENT:
  case BSON_TYPE_ARRAY:
    m__io->pushName("content");
    m_content_bson = new bson_t(m__io, this, m__root);
    m__io->popName();
    break;
  case BSON_TYPE_BIN_DATA:
    m__io->pushName("content");
    m_content_bin_data = new bin_data_t(m__io, this, m__root);
    m__io->popName();
    break;
  case BSON_TYPE_OBJECT_ID:
    m__io->pushName("content");
    m_content_object_id = new object_id_t(m__io, this, m__root);
    m__io->popName();
    break;
  case BSON_TYPE_BOOLEAN:
    m__io->pushName("content");
    m_content_bool = m__io->read_u1();
    m__io->popName();
    break;
  case BSON_TYPE_UTC_DATETIME:
  case BSON_TYPE_NUMBER_LONG:
    m__io->pushName("content");
    m_content_int64 = m__io->read_s8le();
    m__io->popName();
    break;
  case BSON_TYPE_REG_EX:
    m__io->pushName("content");
    m_content_reg_ex = new reg_ex_t(m__io, this, m__root);
    m__io->popName();
    break;
  case BSON_TYPE_DB_POINTER:
    m__io->pushName("content");
    m_content_db_pointer = new db_pointer_t(m__io, this, m__root);
    m__io->popName();
    break;
  case BSON_TYPE_CODE_WITH_SCOPE:
    m__io->pushName("content");
    m_content_code_with_scope = new code_with_scope_t(m__io, this, m__root);
    m__io->popName();
    break;
  case BSON_TYPE_NUMBER_INT:
    m__io->pushName("content");
    m_content_int32 = m__io->read_s4le();
    m__io->popName();
    break;
  case BSON_TYPE_TIMESTAMP:
    m__io->pushName("content");
    m_content_timestamp = new timestamp_t(m__io, this, m__root);
    m__io->popName();
    break;
  case BSON_TYPE_NUMBER_DECIMAL:
    m__io->pushName("content");
    m_content_f16 = new f16_t(m__io, this, m__root);
    m__io->popName();
    break;
  default:
    break;
  }
  m__io->endChunk();
}

bson_t::element_t::~element_t() {
  delete m_name;
  delete m_content_string;
  delete m_content_bson;
  delete m_content_bin_data;
  delete m_content_object_id;
  delete m_content_timestamp;
  delete m_content_reg_ex;
  delete m_content_db_pointer;
  delete m_content_code_with_scope;
  delete m_content_f16;
}

bson_t::object_id_t::object_id_t(kaitai::kstream* p_io,
                                   kaitai::kstruct* p_parent, bson_t* p_root)
    : kaitai::kstruct(p_io) {
  m__parent = p_parent;
  m__root = p_root;
  veles_obj = m__io->startChunk("object_id");
  m__io->pushName("epoch_time");
  m_epoch_time = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("machine_id");
  m_machine_id = m__io->read_bytes(3);
  m__io->popName();
  m__io->pushName("process_id");
  m_process_id = m__io->read_u2le();
  m__io->popName();
  m__io->pushName("counter");
  m_counter = m__io->read_bytes(3);
  m__io->popName();
  m__io->endChunk();
}

bson_t::object_id_t::~object_id_t() {}

bson_t::reg_ex_t::reg_ex_t(kaitai::kstream* p_io,
                             bson_t::element_t* p_parent, bson_t* p_root)
    : kaitai::kstruct(p_io) {
  m__parent = p_parent;
  m__root = p_root;
  veles_obj = m__io->startChunk("reg_ex");
  m__io->pushName("pattern");
  m_pattern = new cstring_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("options");
  m_options = new cstring_t(m__io, this, m__root);
  m__io->popName();
  m__io->endChunk();
}

bson_t::reg_ex_t::~reg_ex_t() {
  delete m_pattern;
  delete m_options;
}

bson_t::db_pointer_t::db_pointer_t(kaitai::kstream* p_io,
                                     bson_t::element_t* p_parent,
                                     bson_t* p_root)
    : kaitai::kstruct(p_io) {
  m__parent = p_parent;
  m__root = p_root;
  veles_obj = m__io->startChunk("db_pointer");
  m__io->pushName("namespace");
  m_ns = new string_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("id");
  m_id = new object_id_t(m__io, this, m__root);
  m__io->popName();
  m__io->endChunk();
}

bson_t::db_pointer_t::~db_pointer_t() {
  delete m_ns;
  delete m_id;
}

bson_t::code_with_scope_t::code_with_scope_t(kaitai::kstream* p_io,
                                               bson_t::element_t* p_parent,
                                               bson_t* p_root)
    : kaitai::kstruct(p_io) {
  m__parent = p_parent;
  m__root = p_root;
  veles_obj = m__io->startChunk("code_with_scope");
  m__io->pushName("id");
  m_id = m__io->read_s4le();
  m__io->popName();
  m__io->pushName("source");
  m_source = new string_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("scope");
  m_scope = new bson_t(m__io, this, m__root);
  m__io->popName();
  m__io->endChunk();
}

bson_t::code_with_scope_t::~code_with_scope_t() {
  delete m_source;
  delete m_scope;
}

bson_t::f16_t::f16_t(kaitai::kstream* p_io, bson_t::element_t* p_parent,
                      bson_t* p_root)
    : kaitai::kstruct(p_io) {
  m__parent = p_parent;
  m__root = p_root;
  veles_obj = m__io->startChunk("decimal128");
  m__io->pushName("raw");
  m_raw = m__io->read_bytes(16);
  m__io->popName();
  m__io->endChunk();
}

bson_t::f16_t::~f16_t() {}
