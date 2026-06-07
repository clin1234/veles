// This is a generated file! Please edit source .ksy file and use
// kaitai-struct-compiler to rebuild

#include "kaitai/java_class.h"

java_class_t::java_class_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent,
                            java_class_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = this;
  m__io->popName();
  veles_obj = m__io->startChunk("java_class");
  m__io->pushName("magic");
  m_magic = m__io->ensure_fixed_contents(
      std::string("\xCA\xFE\xBA\xBE", 4));
  m__io->popName();
  m__io->pushName("version_minor");
  m_version_minor = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("version_major");
  m_version_major = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("constant_pool_count");
  m_constant_pool_count = m__io->read_u2be();
  m__io->popName();
  // LONG and DOUBLE each occupy two constant pool slots (JVM spec §4.4.5).
  // Track by slot index so we insert a nullptr placeholder for the phantom slot.
  int target_slots = constant_pool_count() - 1;
  m_constant_pool = new std::vector<constant_pool_entry_t*>();
  m_constant_pool->reserve(target_slots);
  for (int slot = 0; slot < target_slots; ) {
    m__io->pushName("constant_pool");
    auto entry = new constant_pool_entry_t(m__io, this, m__root);
    m_constant_pool->push_back(entry);
    m__io->popName();
    bool is_wide = (entry->tag() == constant_pool_entry_t::TAG_ENUM_LONG ||
                    entry->tag() == constant_pool_entry_t::TAG_ENUM_DOUBLE);
    if (is_wide && slot + 1 < target_slots) {
      m_constant_pool->push_back(nullptr);
      slot += 2;
    } else {
      slot += 1;
    }
  }
  m__io->pushName("access_flags");
  m_access_flags = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("this_class");
  m_this_class = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("super_class");
  m_super_class = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("interfaces_count");
  m_interfaces_count = m__io->read_u2be();
  m__io->popName();
  int l_interfaces = interfaces_count();
  m_interfaces = new std::vector<uint16_t>();
  m_interfaces->reserve(l_interfaces);
  for (int i = 0; i < l_interfaces; i++) {
    m__io->pushName("interfaces");
    m_interfaces->push_back(m__io->read_u2be());
    m__io->popName();
  }
  m__io->pushName("fields_count");
  m_fields_count = m__io->read_u2be();
  m__io->popName();
  int l_fields = fields_count();
  m_fields = new std::vector<field_info_t*>();
  m_fields->reserve(l_fields);
  for (int i = 0; i < l_fields; i++) {
    m__io->pushName("fields");
    m_fields->push_back(new field_info_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->pushName("methods_count");
  m_methods_count = m__io->read_u2be();
  m__io->popName();
  int l_methods = methods_count();
  m_methods = new std::vector<method_info_t*>();
  m_methods->reserve(l_methods);
  for (int i = 0; i < l_methods; i++) {
    m__io->pushName("methods");
    m_methods->push_back(new method_info_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->endChunk();
}

java_class_t::~java_class_t() {
  for (auto it = m_constant_pool->begin(); it != m_constant_pool->end(); ++it)
    if (*it) delete *it;
  delete m_constant_pool;
  delete m_interfaces;
  for (auto it = m_fields->begin(); it != m_fields->end(); ++it)
    delete *it;
  delete m_fields;
  for (auto it = m_methods->begin(); it != m_methods->end(); ++it)
    delete *it;
  delete m_methods;
}

java_class_t::method_ref_cp_info_t::method_ref_cp_info_t(
    kaitai::kstream* p_io, java_class_t::constant_pool_entry_t* p_parent,
    java_class_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("method_ref");
  m__io->pushName("class_index");
  m_class_index = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("name_and_type_index");
  m_name_and_type_index = m__io->read_u2be();
  m__io->popName();
  m__io->endChunk();
}

java_class_t::method_ref_cp_info_t::~method_ref_cp_info_t() {}

java_class_t::field_info_t::field_info_t(kaitai::kstream* p_io,
                                          java_class_t* p_parent,
                                          java_class_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("field_info");
  m__io->pushName("access_flags");
  m_access_flags = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("name_index");
  m_name_index = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("descriptor_index");
  m_descriptor_index = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("attributes_count");
  m_attributes_count = m__io->read_u2be();
  m__io->popName();
  int l_attributes = attributes_count();
  m_attributes = new std::vector<attribute_t*>();
  m_attributes->reserve(l_attributes);
  for (int i = 0; i < l_attributes; i++) {
    m__io->pushName("attributes");
    m_attributes->push_back(new attribute_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->endChunk();
}

java_class_t::field_info_t::~field_info_t() {
  for (auto it = m_attributes->begin(); it != m_attributes->end(); ++it)
    delete *it;
  delete m_attributes;
}

java_class_t::name_and_type_cp_info_t::name_and_type_cp_info_t(
    kaitai::kstream* p_io, java_class_t::constant_pool_entry_t* p_parent,
    java_class_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("name_and_type");
  m__io->pushName("name_index");
  m_name_index = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("descriptor_index");
  m_descriptor_index = m__io->read_u2be();
  m__io->popName();
  m__io->endChunk();
}

java_class_t::name_and_type_cp_info_t::~name_and_type_cp_info_t() {}

java_class_t::utf8_cp_info_t::utf8_cp_info_t(
    kaitai::kstream* p_io, java_class_t::constant_pool_entry_t* p_parent,
    java_class_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("utf8_cp");
  m__io->pushName("str_len");
  m_str_len = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("value");
  m_value = m__io->read_str_byte_limit(str_len(), "UTF-8");
  m__io->popName();
  m__io->endChunk();
}

java_class_t::utf8_cp_info_t::~utf8_cp_info_t() {}

java_class_t::interface_method_ref_cp_info_t::interface_method_ref_cp_info_t(
    kaitai::kstream* p_io, java_class_t::constant_pool_entry_t* p_parent,
    java_class_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("interface_method_ref");
  m__io->pushName("class_index");
  m_class_index = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("name_and_type_index");
  m_name_and_type_index = m__io->read_u2be();
  m__io->popName();
  m__io->endChunk();
}

java_class_t::interface_method_ref_cp_info_t::~interface_method_ref_cp_info_t() {}

java_class_t::attribute_t::attribute_t(kaitai::kstream* p_io,
                                        kaitai::kstruct* p_parent,
                                        java_class_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("attribute");
  m__io->pushName("attribute_name_index");
  m_attribute_name_index = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("attribute_length");
  m_attribute_length = m__io->read_u4be();
  m__io->popName();
  m__io->pushName("info");
  m_info = m__io->read_bytes(attribute_length());
  m__io->popName();
  m__io->endChunk();
}

java_class_t::attribute_t::~attribute_t() {}

java_class_t::class_cp_info_t::class_cp_info_t(
    kaitai::kstream* p_io, java_class_t::constant_pool_entry_t* p_parent,
    java_class_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("class_cp");
  f_name = false;
  m__io->pushName("name_index");
  m_name_index = m__io->read_u2be();
  m__io->popName();
  m__io->endChunk();
}

java_class_t::class_cp_info_t::~class_cp_info_t() {}

java_class_t::constant_pool_entry_t* java_class_t::class_cp_info_t::name() {
  if (f_name)
    return m_name;
  m_name = _root()->constant_pool()->at(name_index() - 1);
  f_name = true;
  return m_name;
}

java_class_t::constant_pool_entry_t::constant_pool_entry_t(
    kaitai::kstream* p_io, kaitai::kstruct* p_parent, java_class_t* p_root)
    : kaitai::kstruct(p_io),
      m_utf8_cp_info(nullptr), m_class_cp_info(nullptr),
      m_name_and_type_cp_info(nullptr), m_field_ref_cp_info(nullptr),
      m_method_ref_cp_info(nullptr), m_interface_method_ref_cp_info(nullptr) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("constant_pool_entry");
  m__io->pushName("tag");
  m_tag = static_cast<tag_enum_t>(m__io->read_u1());
  m__io->popName();
  n_utf8_cp_info = true;
  if (tag() == TAG_ENUM_UTF8) {
    n_utf8_cp_info = false;
    m__io->pushName("utf8_cp_info");
    m_utf8_cp_info = new utf8_cp_info_t(m__io, this, m__root);
    m__io->popName();
  }
  n_class_cp_info = true;
  if (tag() == TAG_ENUM_CLASS_TYPE) {
    n_class_cp_info = false;
    m__io->pushName("class_cp_info");
    m_class_cp_info = new class_cp_info_t(m__io, this, m__root);
    m__io->popName();
  }
  n_name_and_type_cp_info = true;
  if (tag() == TAG_ENUM_NAME_AND_TYPE) {
    n_name_and_type_cp_info = false;
    m__io->pushName("name_and_type_cp_info");
    m_name_and_type_cp_info =
        new name_and_type_cp_info_t(m__io, this, m__root);
    m__io->popName();
  }
  n_field_ref_cp_info = true;
  if (tag() == TAG_ENUM_FIELD_REF) {
    n_field_ref_cp_info = false;
    m__io->pushName("field_ref_cp_info");
    m_field_ref_cp_info = new field_ref_cp_info_t(m__io, this, m__root);
    m__io->popName();
  }
  n_method_ref_cp_info = true;
  if (tag() == TAG_ENUM_METHOD_REF) {
    n_method_ref_cp_info = false;
    m__io->pushName("method_ref_cp_info");
    m_method_ref_cp_info = new method_ref_cp_info_t(m__io, this, m__root);
    m__io->popName();
  }
  n_interface_method_ref_cp_info = true;
  if (tag() == TAG_ENUM_INTERFACE_METHOD_REF) {
    n_interface_method_ref_cp_info = false;
    m__io->pushName("interface_method_ref_cp_info");
    m_interface_method_ref_cp_info =
        new interface_method_ref_cp_info_t(m__io, this, m__root);
    m__io->popName();
  }
  // Consume bytes for tag types that have no dedicated sub-object.
  // Without this, the stream stays misaligned and all subsequent reads
  // produce garbage, eventually exhausting the stream and crashing on
  // getBe16()[0] (vector subscript out of range).
  if (tag() == TAG_ENUM_STRING) {          // u2 string_index
    m__io->pushName("string_index");
    m__io->read_u2be();
    m__io->popName();
  } else if (tag() == TAG_ENUM_INTEGER || tag() == TAG_ENUM_FLOAT) {  // u4
    m__io->pushName("bytes");
    m__io->read_u4be();
    m__io->popName();
  } else if (tag() == TAG_ENUM_LONG || tag() == TAG_ENUM_DOUBLE) {    // u8
    m__io->pushName("high_bytes");
    m__io->read_u4be();
    m__io->popName();
    m__io->pushName("low_bytes");
    m__io->read_u4be();
    m__io->popName();
  } else if (tag() == TAG_ENUM_METHOD_HANDLE) {  // u1 ref_kind + u2 ref_index
    m__io->pushName("reference_kind");
    m__io->read_u1();
    m__io->popName();
    m__io->pushName("reference_index");
    m__io->read_u2be();
    m__io->popName();
  } else if (tag() == TAG_ENUM_METHOD_TYPE) {    // u2 descriptor_index
    m__io->pushName("descriptor_index");
    m__io->read_u2be();
    m__io->popName();
  } else if (tag() == TAG_ENUM_INVOKE_DYNAMIC) { // u2 + u2
    m__io->pushName("bootstrap_method_attr_index");
    m__io->read_u2be();
    m__io->popName();
    m__io->pushName("name_and_type_index");
    m__io->read_u2be();
    m__io->popName();
  }
  m__io->endChunk();
}

java_class_t::constant_pool_entry_t::~constant_pool_entry_t() {
  if (!n_utf8_cp_info) delete m_utf8_cp_info;
  if (!n_class_cp_info) delete m_class_cp_info;
  if (!n_name_and_type_cp_info) delete m_name_and_type_cp_info;
  if (!n_field_ref_cp_info) delete m_field_ref_cp_info;
  if (!n_method_ref_cp_info) delete m_method_ref_cp_info;
  if (!n_interface_method_ref_cp_info) delete m_interface_method_ref_cp_info;
}

java_class_t::method_info_t::method_info_t(kaitai::kstream* p_io,
                                            java_class_t* p_parent,
                                            java_class_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("method_info");
  m__io->pushName("access_flags");
  m_access_flags = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("name_index");
  m_name_index = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("descriptor_index");
  m_descriptor_index = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("attributes_count");
  m_attributes_count = m__io->read_u2be();
  m__io->popName();
  int l_attributes = attributes_count();
  m_attributes = new std::vector<attribute_t*>();
  m_attributes->reserve(l_attributes);
  for (int i = 0; i < l_attributes; i++) {
    m__io->pushName("attributes");
    m_attributes->push_back(new attribute_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->endChunk();
}

java_class_t::method_info_t::~method_info_t() {
  for (auto it = m_attributes->begin(); it != m_attributes->end(); ++it)
    delete *it;
  delete m_attributes;
}

java_class_t::field_ref_cp_info_t::field_ref_cp_info_t(
    kaitai::kstream* p_io, java_class_t::constant_pool_entry_t* p_parent,
    java_class_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("field_ref");
  m__io->pushName("class_index");
  m_class_index = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("name_and_type_index");
  m_name_and_type_index = m__io->read_u2be();
  m__io->popName();
  m__io->endChunk();
}

java_class_t::field_ref_cp_info_t::~field_ref_cp_info_t() {}
