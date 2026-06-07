// This is a generated file! Please edit source .ksy file and use
// kaitai-struct-compiler to rebuild

#include "kaitai/regf.h"

regf_t::regf_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent,
               regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = this;
  m__io->popName();
  veles_obj = m__io->startChunk("regf");
  m__io->pushName("header");
  m_header = new file_header_t(m__io, this, m__root);
  m__io->popName();
  m_hive_bins = new std::vector<hive_bin_t*>();
  m_hive_bin_streams = new std::vector<kaitai::kstream*>();
  while (!m__io->is_eof()) {
    uint64_t bin_start = m__io->pos();
    m__io->pushName("_skip_me_hive_bin");
    m__io->read_bytes(4096);
    m__io->popName();
    uint64_t bin_end = m__io->pos();
    auto* bin_stream = new kaitai::kstream(
        m__io->blob(), bin_start, veles_obj, bin_end, m__io->error());
    m_hive_bin_streams->push_back(bin_stream);
    m__io->pushName("hive_bins");
    auto* bin = new hive_bin_t(bin_stream, this, m__root);
    m__io->popName();
    m_hive_bins->push_back(bin);
    m__io->addSubchunkItem(bin_start, bin_end, "hive_bins", bin->veles_obj);
  }
  m__io->endChunk();
}

regf_t::~regf_t() {
  delete m_header;
  for (auto it = m_hive_bins->begin(); it != m_hive_bins->end(); ++it) {
    delete *it;
  }
  delete m_hive_bins;
  for (auto it = m_hive_bin_streams->begin(); it != m_hive_bin_streams->end();
       ++it) {
    delete *it;
  }
  delete m_hive_bin_streams;
}

regf_t::filetime_t::filetime_t(kaitai::kstream* p_io,
                                kaitai::kstruct* p_parent,
                                regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("filetime");
  m__io->pushName("value");
  m_value = m__io->read_u8le();
  m__io->popName();
  m__io->endChunk();
}

regf_t::filetime_t::~filetime_t() {}

regf_t::hive_bin_t::hive_bin_t(kaitai::kstream* p_io, regf_t* p_parent,
                                regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("hive_bin");
  m__io->pushName("header");
  m_header = new hive_bin_header_t(m__io, this, m__root);
  m__io->popName();
  m_cells = new std::vector<hive_bin_cell_t*>();
  while (!m__io->is_eof()) {
    m__io->pushName("cells");
    m_cells->push_back(new hive_bin_cell_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->endChunk();
}

regf_t::hive_bin_t::~hive_bin_t() {
  delete m_header;
  for (auto it = m_cells->begin(); it != m_cells->end(); ++it) {
    delete *it;
  }
  delete m_cells;
}

regf_t::hive_bin_header_t::hive_bin_header_t(kaitai::kstream* p_io,
                                               regf_t::hive_bin_t* p_parent,
                                               regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("hive_bin_header");
  m__io->pushName("signature");
  m_signature = m__io->ensure_fixed_contents(
      std::string("\x68\x62\x69\x6E", 4));
  m__io->popName();
  m__io->pushName("offset");
  m_offset = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("size");
  m_size = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("unknown1");
  m_unknown1 = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("unknown2");
  m_unknown2 = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("timestamp");
  m_timestamp = new filetime_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("unknown4");
  m_unknown4 = m__io->read_u4le();
  m__io->popName();
  m__io->endChunk();
}

regf_t::hive_bin_header_t::~hive_bin_header_t() {
  delete m_timestamp;
}

regf_t::hive_bin_cell_t::hive_bin_cell_t(kaitai::kstream* p_io,
                                          regf_t::hive_bin_t* p_parent,
                                          regf_t* p_root)
    : kaitai::kstruct(p_io), m__io__raw_data(nullptr), m_data(nullptr) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("hive_bin_cell");
  f_cell_size = false;
  f_is_allocated = false;
  m__io->pushName("cell_size_raw");
  m_cell_size_raw = m__io->read_s4le();
  m__io->popName();
  m__io->pushName("identifier");
  m_identifier = m__io->read_str_byte_limit(2, "ascii");
  m__io->popName();
  int32_t data_bytes = (cell_size() - 2) - 4;
  if (data_bytes > 0) {
    m__io->pushName("_skip_me_data");
    m__raw_data = m__io->read_bytes(static_cast<size_t>(data_bytes));
    m__io->popName();
    uint64_t data_start = m__io->pos() - m__raw_data.size();
    uint64_t data_end = m__io->pos();
    m__io__raw_data = new kaitai::kstream(
        m__io->blob(), data_start, veles_obj, data_end, m__io->error());
    veles::dbif::ObjectHandle data_vobj;
    const std::string& id = identifier();
    if (id == "li") {
      m__io->pushName("data");
      auto* p = new sub_key_list_li_t(m__io__raw_data, this, m__root);
      data_vobj = p->veles_obj;
      m_data = p;
      m__io->popName();
    } else if (id == "vk") {
      m__io->pushName("data");
      auto* p = new sub_key_list_vk_t(m__io__raw_data, this, m__root);
      data_vobj = p->veles_obj;
      m_data = p;
      m__io->popName();
    } else if (id == "lf" || id == "lh") {
      m__io->pushName("data");
      auto* p = new sub_key_list_lh_lf_t(m__io__raw_data, this, m__root);
      data_vobj = p->veles_obj;
      m_data = p;
      m__io->popName();
    } else if (id == "ri") {
      m__io->pushName("data");
      auto* p = new sub_key_list_ri_t(m__io__raw_data, this, m__root);
      data_vobj = p->veles_obj;
      m_data = p;
      m__io->popName();
    } else if (id == "nk") {
      m__io->pushName("data");
      auto* p = new named_key_t(m__io__raw_data, this, m__root);
      data_vobj = p->veles_obj;
      m_data = p;
      m__io->popName();
    } else if (id == "sk") {
      m__io->pushName("data");
      auto* p = new sub_key_list_sk_t(m__io__raw_data, this, m__root);
      data_vobj = p->veles_obj;
      m_data = p;
      m__io->popName();
    }
    if (m_data != nullptr) {
      m__io->addSubchunkItem(data_start, data_end, "data", data_vobj);
    }
  }
  m__io->endChunk();
}

regf_t::hive_bin_cell_t::~hive_bin_cell_t() {
  delete m__io__raw_data;
  if (m_data != nullptr) {
    const std::string& id = m_identifier;
    if (id == "li") delete static_cast<sub_key_list_li_t*>(m_data);
    else if (id == "vk") delete static_cast<sub_key_list_vk_t*>(m_data);
    else if (id == "lf" || id == "lh")
      delete static_cast<sub_key_list_lh_lf_t*>(m_data);
    else if (id == "ri") delete static_cast<sub_key_list_ri_t*>(m_data);
    else if (id == "nk") delete static_cast<named_key_t*>(m_data);
    else if (id == "sk") delete static_cast<sub_key_list_sk_t*>(m_data);
  }
}

regf_t::hive_bin_cell_t::sub_key_list_vk_t::sub_key_list_vk_t(
    kaitai::kstream* p_io, regf_t::hive_bin_cell_t* p_parent,
    regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("vk");
  m__io->pushName("value_name_size");
  m_value_name_size = m__io->read_u2le();
  m__io->popName();
  m__io->pushName("data_size");
  m_data_size = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("data_offset");
  m_data_offset = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("data_type");
  m_data_type = static_cast<data_type_enum_t>(m__io->read_u4le());
  m__io->popName();
  m__io->pushName("flags");
  m_flags = static_cast<vk_flags_t>(m__io->read_u2le());
  m__io->popName();
  m__io->pushName("padding");
  m_padding = m__io->read_u2le();
  m__io->popName();
  n_value_name = true;
  if (flags() == VK_FLAGS_VALUE_COMP_NAME) {
    n_value_name = false;
    m__io->pushName("value_name");
    m_value_name = m__io->read_str_byte_limit(value_name_size(), "ascii");
    m__io->popName();
  }
  m__io->endChunk();
}

regf_t::hive_bin_cell_t::sub_key_list_vk_t::~sub_key_list_vk_t() {}

regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t::sub_key_list_lh_lf_t(
    kaitai::kstream* p_io, regf_t::hive_bin_cell_t* p_parent,
    regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("lh_lf");
  m__io->pushName("count");
  m_count = m__io->read_u2le();
  m__io->popName();
  m_items = new std::vector<item_t*>();
  for (int i = 0; i < static_cast<int>(count()); i++) {
    m__io->pushName("items");
    m_items->push_back(new item_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->endChunk();
}

regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t::~sub_key_list_lh_lf_t() {
  for (auto it = m_items->begin(); it != m_items->end(); ++it) {
    delete *it;
  }
  delete m_items;
}

regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t::item_t::item_t(
    kaitai::kstream* p_io,
    regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t* p_parent,
    regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("lh_lf_item");
  m__io->pushName("named_key_offset");
  m_named_key_offset = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("hash_value");
  m_hash_value = m__io->read_u4le();
  m__io->popName();
  m__io->endChunk();
}

regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t::item_t::~item_t() {}

regf_t::hive_bin_cell_t::sub_key_list_sk_t::sub_key_list_sk_t(
    kaitai::kstream* p_io, regf_t::hive_bin_cell_t* p_parent,
    regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("sk");
  m__io->pushName("unknown1");
  m_unknown1 = m__io->read_u2le();
  m__io->popName();
  m__io->pushName("previous_security_key_offset");
  m_previous_security_key_offset = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("next_security_key_offset");
  m_next_security_key_offset = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("reference_count");
  m_reference_count = m__io->read_u4le();
  m__io->popName();
  m__io->endChunk();
}

regf_t::hive_bin_cell_t::sub_key_list_sk_t::~sub_key_list_sk_t() {}

regf_t::hive_bin_cell_t::sub_key_list_li_t::sub_key_list_li_t(
    kaitai::kstream* p_io, regf_t::hive_bin_cell_t* p_parent,
    regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("li");
  m__io->pushName("count");
  m_count = m__io->read_u2le();
  m__io->popName();
  m_items = new std::vector<item_t*>();
  for (int i = 0; i < static_cast<int>(count()); i++) {
    m__io->pushName("items");
    m_items->push_back(new item_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->endChunk();
}

regf_t::hive_bin_cell_t::sub_key_list_li_t::~sub_key_list_li_t() {
  for (auto it = m_items->begin(); it != m_items->end(); ++it) {
    delete *it;
  }
  delete m_items;
}

regf_t::hive_bin_cell_t::sub_key_list_li_t::item_t::item_t(
    kaitai::kstream* p_io,
    regf_t::hive_bin_cell_t::sub_key_list_li_t* p_parent,
    regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("li_item");
  m__io->pushName("named_key_offset");
  m_named_key_offset = m__io->read_u4le();
  m__io->popName();
  m__io->endChunk();
}

regf_t::hive_bin_cell_t::sub_key_list_li_t::item_t::~item_t() {}

regf_t::hive_bin_cell_t::named_key_t::named_key_t(
    kaitai::kstream* p_io, regf_t::hive_bin_cell_t* p_parent,
    regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("nk");
  m__io->pushName("flags");
  m_flags = static_cast<nk_flags_t>(m__io->read_u2le());
  m__io->popName();
  m__io->pushName("last_key_written_date_and_time");
  m_last_key_written_date_and_time = new filetime_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("unknown1");
  m_unknown1 = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("parent_key_offset");
  m_parent_key_offset = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("number_of_sub_keys");
  m_number_of_sub_keys = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("number_of_volatile_sub_keys");
  m_number_of_volatile_sub_keys = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("sub_keys_list_offset");
  m_sub_keys_list_offset = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("number_of_values");
  m_number_of_values = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("values_list_offset");
  m_values_list_offset = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("security_key_offset");
  m_security_key_offset = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("class_name_offset");
  m_class_name_offset = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("largest_sub_key_name_size");
  m_largest_sub_key_name_size = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("largest_sub_key_class_name_size");
  m_largest_sub_key_class_name_size = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("largest_value_name_size");
  m_largest_value_name_size = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("largest_value_data_size");
  m_largest_value_data_size = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("unknown2");
  m_unknown2 = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("key_name_size");
  m_key_name_size = m__io->read_u2le();
  m__io->popName();
  m__io->pushName("class_name_size");
  m_class_name_size = m__io->read_u2le();
  m__io->popName();
  m__io->pushName("unknown_string_size");
  m_unknown_string_size = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("unknown_string");
  m_unknown_string = m__io->read_str_byte_limit(unknown_string_size(), "ascii");
  m__io->popName();
  m__io->endChunk();
}

regf_t::hive_bin_cell_t::named_key_t::~named_key_t() {
  delete m_last_key_written_date_and_time;
}

regf_t::hive_bin_cell_t::sub_key_list_ri_t::sub_key_list_ri_t(
    kaitai::kstream* p_io, regf_t::hive_bin_cell_t* p_parent,
    regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("ri");
  m__io->pushName("count");
  m_count = m__io->read_u2le();
  m__io->popName();
  m_items = new std::vector<item_t*>();
  for (int i = 0; i < static_cast<int>(count()); i++) {
    m__io->pushName("items");
    m_items->push_back(new item_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->endChunk();
}

regf_t::hive_bin_cell_t::sub_key_list_ri_t::~sub_key_list_ri_t() {
  for (auto it = m_items->begin(); it != m_items->end(); ++it) {
    delete *it;
  }
  delete m_items;
}

regf_t::hive_bin_cell_t::sub_key_list_ri_t::item_t::item_t(
    kaitai::kstream* p_io,
    regf_t::hive_bin_cell_t::sub_key_list_ri_t* p_parent,
    regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("ri_item");
  m__io->pushName("sub_key_list_offset");
  m_sub_key_list_offset = m__io->read_u4le();
  m__io->popName();
  m__io->endChunk();
}

regf_t::hive_bin_cell_t::sub_key_list_ri_t::item_t::~item_t() {}

int32_t regf_t::hive_bin_cell_t::cell_size() {
  if (f_cell_size)
    return m_cell_size;
  m_cell_size = ((cell_size_raw() < 0) ? (-1) : (1)) * cell_size_raw();
  f_cell_size = true;
  return m_cell_size;
}

bool regf_t::hive_bin_cell_t::is_allocated() {
  if (f_is_allocated)
    return m_is_allocated;
  m_is_allocated = cell_size_raw() < 0;
  f_is_allocated = true;
  return m_is_allocated;
}

regf_t::file_header_t::file_header_t(kaitai::kstream* p_io, regf_t* p_parent,
                                      regf_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("file_header");
  m__io->pushName("signature");
  m_signature = m__io->ensure_fixed_contents(
      std::string("\x72\x65\x67\x66", 4));
  m__io->popName();
  m__io->pushName("primary_sequence_number");
  m_primary_sequence_number = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("secondary_sequence_number");
  m_secondary_sequence_number = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("last_modification_date_and_time");
  m_last_modification_date_and_time = new filetime_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("major_version");
  m_major_version = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("minor_version");
  m_minor_version = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("type");
  m_type = static_cast<file_type_t>(m__io->read_u4le());
  m__io->popName();
  m__io->pushName("format");
  m_format = static_cast<file_format_t>(m__io->read_u4le());
  m__io->popName();
  m__io->pushName("root_key_offset");
  m_root_key_offset = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("hive_bins_data_size");
  m_hive_bins_data_size = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("clustering_factor");
  m_clustering_factor = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("unknown1");
  m_unknown1 = m__io->read_bytes(64);
  m__io->popName();
  m__io->pushName("unknown2");
  m_unknown2 = m__io->read_bytes(396);
  m__io->popName();
  m__io->pushName("checksum");
  m_checksum = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("reserved");
  m_reserved = m__io->read_bytes(3576);
  m__io->popName();
  m__io->pushName("boot_type");
  m_boot_type = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("boot_recover");
  m_boot_recover = m__io->read_u4le();
  m__io->popName();
  m__io->endChunk();
}

regf_t::file_header_t::~file_header_t() {
  delete m_last_modification_date_and_time;
}
