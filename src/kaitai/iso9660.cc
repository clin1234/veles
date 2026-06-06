// This is a generated file! Please edit source .ksy file and use
// kaitai-struct-compiler to rebuild

#include "kaitai/iso9660.h"

iso9660_t::iso9660_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent,
                     iso9660_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = this;
  m__io->popName();
  veles_obj = m__io->startChunk("iso9660");
  f_sector_size = false;
  f_primary_vol_desc = false;
  m__io->pushName("primary_vol_desc");
  primary_vol_desc();
  m__io->popName();
  m__io->endChunk();
}

iso9660_t::~iso9660_t() {
  if (f_primary_vol_desc) {
    delete m_primary_vol_desc;
  }
}

iso9660_t::vol_desc_primary_t::vol_desc_primary_t(
    kaitai::kstream* p_io, iso9660_t::vol_desc_t* p_parent,
    iso9660_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("vol_desc_primary");
  f_path_table = false;
  m__io->pushName("unused1");
  m_unused1 = m__io->ensure_fixed_contents(std::string("\x00", 1));
  m__io->popName();
  m__io->pushName("system_id");
  m_system_id = m__io->read_str_byte_limit(32, "UTF-8");
  m__io->popName();
  m__io->pushName("volume_id");
  m_volume_id = m__io->read_str_byte_limit(32, "UTF-8");
  m__io->popName();
  m__io->pushName("unused2");
  m_unused2 = m__io->ensure_fixed_contents(
      std::string("\x00\x00\x00\x00\x00\x00\x00\x00", 8));
  m__io->popName();
  m__io->pushName("vol_space_size");
  m_vol_space_size = new u4bi_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("unused3");
  m_unused3 = m__io->ensure_fixed_contents(std::string(
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
      32));
  m__io->popName();
  m__io->pushName("vol_set_size");
  m_vol_set_size = new u2bi_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("vol_seq_num");
  m_vol_seq_num = new u2bi_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("logical_block_size");
  m_logical_block_size = new u2bi_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("path_table_size");
  m_path_table_size = new u4bi_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("lba_path_table_le");
  m_lba_path_table_le = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("lba_opt_path_table_le");
  m_lba_opt_path_table_le = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("lba_path_table_be");
  m_lba_path_table_be = m__io->read_u4be();
  m__io->popName();
  m__io->pushName("lba_opt_path_table_be");
  m_lba_opt_path_table_be = m__io->read_u4be();
  m__io->popName();
  m__io->pushName("_skip_me_root_dir");
  m__raw_root_dir = m__io->read_bytes(34);
  m__io->popName();
  m__io->pushName("m__raw_root_dir" + 3);
  m__io__raw_root_dir = new kaitai::kstream(
      m__io->blob(), m__io->pos() - m__raw_root_dir.size(),
      veles_obj, m__io->pos(), m__io->error());
  m__io->popName();
  m__io->pushName("root_dir");
  m_root_dir = new dir_entry_t(m__io__raw_root_dir, this, m__root);
  m__io->popName();
  m__io->addSubchunkItem(m__io->pos() - m__raw_root_dir.size(), m__io->pos(),
                         "root_dir", m_root_dir->veles_obj);
  m__io->pushName("vol_set_id");
  m_vol_set_id = m__io->read_str_byte_limit(128, "UTF-8");
  m__io->popName();
  m__io->pushName("publisher_id");
  m_publisher_id = m__io->read_str_byte_limit(128, "UTF-8");
  m__io->popName();
  m__io->pushName("data_preparer_id");
  m_data_preparer_id = m__io->read_str_byte_limit(128, "UTF-8");
  m__io->popName();
  m__io->pushName("application_id");
  m_application_id = m__io->read_str_byte_limit(128, "UTF-8");
  m__io->popName();
  m__io->pushName("copyright_file_id");
  m_copyright_file_id = m__io->read_str_byte_limit(38, "UTF-8");
  m__io->popName();
  m__io->pushName("abstract_file_id");
  m_abstract_file_id = m__io->read_str_byte_limit(36, "UTF-8");
  m__io->popName();
  m__io->pushName("bibliographic_file_id");
  m_bibliographic_file_id = m__io->read_str_byte_limit(37, "UTF-8");
  m__io->popName();
  m__io->pushName("vol_create_datetime");
  m_vol_create_datetime = new dec_datetime_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("vol_mod_datetime");
  m_vol_mod_datetime = new dec_datetime_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("vol_expire_datetime");
  m_vol_expire_datetime = new dec_datetime_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("vol_effective_datetime");
  m_vol_effective_datetime = new dec_datetime_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("file_structure_version");
  m_file_structure_version = m__io->read_u1();
  m__io->popName();
  m__io->pushName("unused4");
  m_unused4 = m__io->read_u1();
  m__io->popName();
  m__io->pushName("application_area");
  m_application_area = m__io->read_bytes(512);
  m__io->popName();
  m__io->pushName("path_table");
  path_table();
  m__io->popName();
  m__io->endChunk();
}

iso9660_t::vol_desc_primary_t::~vol_desc_primary_t() {
  delete m_vol_space_size;
  delete m_vol_set_size;
  delete m_vol_seq_num;
  delete m_logical_block_size;
  delete m_path_table_size;
  delete m__io__raw_root_dir;
  delete m_root_dir;
  delete m_vol_create_datetime;
  delete m_vol_mod_datetime;
  delete m_vol_expire_datetime;
  delete m_vol_effective_datetime;
  if (f_path_table) {
    delete m__io__raw_path_table;
    delete m_path_table;
  }
}

iso9660_t::path_table_le_t* iso9660_t::vol_desc_primary_t::path_table() {
  if (f_path_table)
    return m_path_table;
  uint64_t _pos = m__io->pos();
  m__io->seek(lba_path_table_le() * _root()->sector_size());
  m__io->pushName("_skip_me_path_table");
  m__raw_path_table = m__io->read_bytes(path_table_size()->le());
  m__io->popName();
  m__io->pushName("m__raw_path_table" + 3);
  m__io__raw_path_table = new kaitai::kstream(
      m__io->blob(), m__io->pos() - m__raw_path_table.size(),
      veles_obj, m__io->pos(), m__io->error());
  m__io->popName();
  m__io->pushName("path_table");
  m_path_table = new path_table_le_t(m__io__raw_path_table, this, m__root);
  m__io->popName();
  m__io->addSubchunkItem(m__io->pos() - m__raw_path_table.size(), m__io->pos(),
                         "path_table", m_path_table->veles_obj);
  m__io->seek(_pos);
  f_path_table = true;
  return m_path_table;
}

iso9660_t::vol_desc_boot_record_t::vol_desc_boot_record_t(
    kaitai::kstream* p_io, iso9660_t::vol_desc_t* p_parent,
    iso9660_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("vol_desc_boot_record");
  m__io->pushName("boot_system_id");
  m_boot_system_id = m__io->read_str_byte_limit(32, "UTF-8");
  m__io->popName();
  m__io->pushName("boot_id");
  m_boot_id = m__io->read_str_byte_limit(32, "UTF-8");
  m__io->popName();
  m__io->endChunk();
}

iso9660_t::vol_desc_boot_record_t::~vol_desc_boot_record_t() {}

iso9660_t::datetime_t::datetime_t(kaitai::kstream* p_io,
                                  iso9660_t::dir_entry_body_t* p_parent,
                                  iso9660_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("datetime");
  m__io->pushName("year");
  m_year = m__io->read_u1();
  m__io->popName();
  m__io->pushName("month");
  m_month = m__io->read_u1();
  m__io->popName();
  m__io->pushName("day");
  m_day = m__io->read_u1();
  m__io->popName();
  m__io->pushName("hour");
  m_hour = m__io->read_u1();
  m__io->popName();
  m__io->pushName("minute");
  m_minute = m__io->read_u1();
  m__io->popName();
  m__io->pushName("sec");
  m_sec = m__io->read_u1();
  m__io->popName();
  m__io->pushName("timezone");
  m_timezone = m__io->read_u1();
  m__io->popName();
  m__io->endChunk();
}

iso9660_t::datetime_t::~datetime_t() {}

iso9660_t::dir_entry_t::dir_entry_t(kaitai::kstream* p_io,
                                    kaitai::kstruct* p_parent,
                                    iso9660_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("dir_entry");
  m__io->pushName("len");
  m_len = m__io->read_u1();
  m__io->popName();
  n_body = true;
  if (len() > 0) {
    n_body = false;
    m__io->pushName("_skip_me_body");
    m__raw_body = m__io->read_bytes((len() - 1));
    m__io->popName();
    m__io->pushName("m__raw_body" + 3);
    m__io__raw_body = new kaitai::kstream(
        m__io->blob(), m__io->pos() - m__raw_body.size(),
        veles_obj, m__io->pos(), m__io->error());
    m__io->popName();
    m__io->pushName("body");
    m_body = new dir_entry_body_t(m__io__raw_body, this, m__root);
    m__io->popName();
    m__io->addSubchunkItem(m__io->pos() - m__raw_body.size(), m__io->pos(),
                           "body", m_body->veles_obj);
  }
  m__io->endChunk();
}

iso9660_t::dir_entry_t::~dir_entry_t() {
  if (!n_body) {
    delete m__io__raw_body;
    delete m_body;
  }
}

iso9660_t::vol_desc_t::vol_desc_t(kaitai::kstream* p_io,
                                  iso9660_t* p_parent,
                                  iso9660_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("vol_desc");
  m__io->pushName("type");
  m_type = m__io->read_u1();
  m__io->popName();
  m__io->pushName("magic");
  m_magic = m__io->ensure_fixed_contents(std::string("\x43\x44\x30\x30\x31", 5));
  m__io->popName();
  m__io->pushName("version");
  m_version = m__io->read_u1();
  m__io->popName();
  n_vol_desc_boot_record = true;
  if (type() == 0) {
    n_vol_desc_boot_record = false;
    m__io->pushName("vol_desc_boot_record");
    m_vol_desc_boot_record = new vol_desc_boot_record_t(m__io, this, m__root);
    m__io->popName();
  }
  n_vol_desc_primary = true;
  if (type() == 1) {
    n_vol_desc_primary = false;
    m__io->pushName("vol_desc_primary");
    m_vol_desc_primary = new vol_desc_primary_t(m__io, this, m__root);
    m__io->popName();
  }
  m__io->endChunk();
}

iso9660_t::vol_desc_t::~vol_desc_t() {
  if (!n_vol_desc_boot_record) {
    delete m_vol_desc_boot_record;
  }
  if (!n_vol_desc_primary) {
    delete m_vol_desc_primary;
  }
}

iso9660_t::path_table_entry_le_t::path_table_entry_le_t(
    kaitai::kstream* p_io, iso9660_t::path_table_le_t* p_parent,
    iso9660_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("path_table_entry_le");
  m__io->pushName("len_dir_name");
  m_len_dir_name = m__io->read_u1();
  m__io->popName();
  m__io->pushName("len_ext_attr_rec");
  m_len_ext_attr_rec = m__io->read_u1();
  m__io->popName();
  m__io->pushName("lba_extent");
  m_lba_extent = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("parent_dir_idx");
  m_parent_dir_idx = m__io->read_u2le();
  m__io->popName();
  m__io->pushName("dir_name");
  m_dir_name = m__io->read_str_byte_limit(len_dir_name(), "UTF-8");
  m__io->popName();
  n_padding = true;
  if (kaitai::kstream::mod(len_dir_name(), 2) == 1) {
    n_padding = false;
    m__io->pushName("padding");
    m_padding = m__io->read_u1();
    m__io->popName();
  }
  m__io->endChunk();
}

iso9660_t::path_table_entry_le_t::~path_table_entry_le_t() {}

iso9660_t::dir_entries_t::dir_entries_t(kaitai::kstream* p_io,
                                        iso9660_t::dir_entry_body_t* p_parent,
                                        iso9660_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("dir_entries");
  m_entries = new std::vector<dir_entry_t*>();
  {
    dir_entry_t* _;
    do {
      m__io->pushName("entries");
      _ = new dir_entry_t(m__io, this, m__root);
      m__io->popName();
      m_entries->push_back(_);
    } while (!(_->len() == 0));
  }
  m__io->endChunk();
}

iso9660_t::dir_entries_t::~dir_entries_t() {
  for (auto it = m_entries->begin(); it != m_entries->end(); ++it) {
    delete *it;
  }
  delete m_entries;
}

iso9660_t::u4bi_t::u4bi_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent,
                           iso9660_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("u4bi");
  m__io->pushName("le");
  m_le = m__io->read_u4le();
  m__io->popName();
  m__io->pushName("be");
  m_be = m__io->read_u4be();
  m__io->popName();
  m__io->endChunk();
}

iso9660_t::u4bi_t::~u4bi_t() {}

iso9660_t::u2bi_t::u2bi_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent,
                           iso9660_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("u2bi");
  m__io->pushName("le");
  m_le = m__io->read_u2le();
  m__io->popName();
  m__io->pushName("be");
  m_be = m__io->read_u2be();
  m__io->popName();
  m__io->endChunk();
}

iso9660_t::u2bi_t::~u2bi_t() {}

iso9660_t::path_table_le_t::path_table_le_t(
    kaitai::kstream* p_io, iso9660_t::vol_desc_primary_t* p_parent,
    iso9660_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("path_table_le");
  m_entries = new std::vector<path_table_entry_le_t*>();
  while (!m__io->is_eof()) {
    m__io->pushName("entries");
    m_entries->push_back(new path_table_entry_le_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->endChunk();
}

iso9660_t::path_table_le_t::~path_table_le_t() {
  for (auto it = m_entries->begin(); it != m_entries->end(); ++it) {
    delete *it;
  }
  delete m_entries;
}

iso9660_t::dec_datetime_t::dec_datetime_t(
    kaitai::kstream* p_io, iso9660_t::vol_desc_primary_t* p_parent,
    iso9660_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("dec_datetime");
  m__io->pushName("year");
  m_year = m__io->read_str_byte_limit(4, "ASCII");
  m__io->popName();
  m__io->pushName("month");
  m_month = m__io->read_str_byte_limit(2, "ASCII");
  m__io->popName();
  m__io->pushName("day");
  m_day = m__io->read_str_byte_limit(2, "ASCII");
  m__io->popName();
  m__io->pushName("hour");
  m_hour = m__io->read_str_byte_limit(2, "ASCII");
  m__io->popName();
  m__io->pushName("minute");
  m_minute = m__io->read_str_byte_limit(2, "ASCII");
  m__io->popName();
  m__io->pushName("sec");
  m_sec = m__io->read_str_byte_limit(2, "ASCII");
  m__io->popName();
  m__io->pushName("sec_hundreds");
  m_sec_hundreds = m__io->read_str_byte_limit(2, "ASCII");
  m__io->popName();
  m__io->pushName("timezone");
  m_timezone = m__io->read_u1();
  m__io->popName();
  m__io->endChunk();
}

iso9660_t::dec_datetime_t::~dec_datetime_t() {}

iso9660_t::dir_entry_body_t::dir_entry_body_t(
    kaitai::kstream* p_io, iso9660_t::dir_entry_t* p_parent,
    iso9660_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("dir_entry_body");
  f_extent_as_dir = false;
  f_extent_as_file = false;
  m__io->pushName("len_ext_attr_rec");
  m_len_ext_attr_rec = m__io->read_u1();
  m__io->popName();
  m__io->pushName("lba_extent");
  m_lba_extent = new u4bi_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("size_extent");
  m_size_extent = new u4bi_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("datetime");
  m_datetime = new datetime_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("file_flags");
  m_file_flags = m__io->read_u1();
  m__io->popName();
  m__io->pushName("file_unit_size");
  m_file_unit_size = m__io->read_u1();
  m__io->popName();
  m__io->pushName("interleave_gap_size");
  m_interleave_gap_size = m__io->read_u1();
  m__io->popName();
  m__io->pushName("vol_seq_num");
  m_vol_seq_num = new u2bi_t(m__io, this, m__root);
  m__io->popName();
  m__io->pushName("len_file_name");
  m_len_file_name = m__io->read_u1();
  m__io->popName();
  m__io->pushName("file_name");
  m_file_name = m__io->read_str_byte_limit(len_file_name(), "UTF-8");
  m__io->popName();
  n_padding = true;
  if (kaitai::kstream::mod(len_file_name(), 2) == 0) {
    n_padding = false;
    m__io->pushName("padding");
    m_padding = m__io->read_u1();
    m__io->popName();
  }
  m__io->pushName("rest");
  m_rest = m__io->read_bytes_full();
  m__io->popName();
  m__io->endChunk();
}

iso9660_t::dir_entry_body_t::~dir_entry_body_t() {
  delete m_lba_extent;
  delete m_size_extent;
  delete m_datetime;
  delete m_vol_seq_num;
  if (f_extent_as_dir && !n_extent_as_dir) {
    delete m__io__raw_extent_as_dir;
    delete m_extent_as_dir;
  }
}

iso9660_t::dir_entries_t* iso9660_t::dir_entry_body_t::extent_as_dir() {
  if (f_extent_as_dir)
    return m_extent_as_dir;
  n_extent_as_dir = true;
  m__io->pushName("extent_as_dir");
  if ((file_flags() & 2) != 0) {
    n_extent_as_dir = false;
    kaitai::kstream* io = _root()->_io();
    uint64_t _pos = io->pos();
    io->seek(lba_extent()->le() * _root()->sector_size());
    io->pushName("_skip_me_extent_as_dir");
    m__raw_extent_as_dir = io->read_bytes(size_extent()->le());
    io->popName();
    m__io__raw_extent_as_dir = new kaitai::kstream(
        io->blob(), io->pos() - m__raw_extent_as_dir.size(),
        veles_obj, io->pos(), io->error());
    m__io->pushName("extent_as_dir");
    m_extent_as_dir = new dir_entries_t(m__io__raw_extent_as_dir, this, m__root);
    m__io->popName();
    io->seek(_pos);
  }
  f_extent_as_dir = true;
  m__io->popName();
  return m_extent_as_dir;
}

std::string iso9660_t::dir_entry_body_t::extent_as_file() {
  if (f_extent_as_file)
    return m_extent_as_file;
  n_extent_as_file = true;
  m__io->pushName("extent_as_file");
  if ((file_flags() & 2) == 0) {
    n_extent_as_file = false;
    kaitai::kstream* io = _root()->_io();
    uint64_t _pos = io->pos();
    io->seek(lba_extent()->le() * _root()->sector_size());
    io->pushName("extent_as_file");
    m_extent_as_file = io->read_bytes(size_extent()->le());
    io->popName();
    io->seek(_pos);
  }
  f_extent_as_file = true;
  m__io->popName();
  return m_extent_as_file;
}

int32_t iso9660_t::sector_size() {
  if (f_sector_size)
    return m_sector_size;
  m_sector_size = 2048;
  f_sector_size = true;
  return m_sector_size;
}

iso9660_t::vol_desc_t* iso9660_t::primary_vol_desc() {
  if (f_primary_vol_desc)
    return m_primary_vol_desc;
  uint64_t _pos = m__io->pos();
  m__io->seek(16 * sector_size());
  m__io->pushName("primary_vol_desc");
  m_primary_vol_desc = new vol_desc_t(m__io, this, m__root);
  m__io->popName();
  m__io->seek(_pos);
  f_primary_vol_desc = true;
  return m_primary_vol_desc;
}
