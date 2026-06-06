// This is a generated file! Please edit source .ksy file and use
// kaitai-struct-compiler to rebuild

#include "kaitai/jpeg.h"

jpeg_t::jpeg_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent,
               jpeg_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = this;
  m__io->popName();
  veles_obj = m__io->startChunk("jpeg");
  m_segments = new std::vector<segment_t*>();
  while (!m__io->is_eof()) {
    m__io->pushName("segments");
    m_segments->push_back(new segment_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->endChunk();
}

jpeg_t::~jpeg_t() {
  for (auto it = m_segments->begin(); it != m_segments->end(); ++it) {
    delete *it;
  }
  delete m_segments;
}

jpeg_t::segment_t::segment_t(kaitai::kstream* p_io, jpeg_t* p_parent,
                               jpeg_t* p_root)
    : kaitai::kstruct(p_io), m__io__raw_data(nullptr), m_data(nullptr) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("segment");
  m__io->pushName("magic");
  m_magic = m__io->ensure_fixed_contents(std::string("\xFF", 1));
  m__io->popName();
  m__io->pushName("marker");
  m_marker = static_cast<marker_enum_t>(m__io->read_u1());
  m__io->popName();
  n_length = true;
  if (marker() != MARKER_ENUM_SOI && marker() != MARKER_ENUM_EOI) {
    n_length = false;
    m__io->pushName("length");
    m_length = m__io->read_u2be();
    m__io->popName();
  }
  n_data = true;
  if (marker() != MARKER_ENUM_SOI && marker() != MARKER_ENUM_EOI) {
    n_data = false;
    m__io->pushName("_skip_me_data");
    m__raw_data = m__io->read_bytes(length() - 2);
    m__io->popName();
    uint64_t data_start = m__io->pos() - m__raw_data.size();
    uint64_t data_end = m__io->pos();
    m__io__raw_data = new kaitai::kstream(
        m__io->blob(), data_start, veles_obj, data_end, m__io->error());
    veles::dbif::ObjectHandle data_vobj;
    switch (marker()) {
    case MARKER_ENUM_SOS: {
      m__io->pushName("data");
      auto* sos = new segment_sos_t(m__io__raw_data, this, m__root);
      data_vobj = sos->veles_obj;
      m_data = sos;
      m__io->popName();
      break;
    }
    case MARKER_ENUM_APP1: {
      m__io->pushName("data");
      auto* app1 = new segment_app1_t(m__io__raw_data, this, m__root);
      data_vobj = app1->veles_obj;
      m_data = app1;
      m__io->popName();
      break;
    }
    case MARKER_ENUM_SOF0: {
      m__io->pushName("data");
      auto* sof0 = new segment_sof0_t(m__io__raw_data, this, m__root);
      data_vobj = sof0->veles_obj;
      m_data = sof0;
      m__io->popName();
      break;
    }
    case MARKER_ENUM_APP0: {
      m__io->pushName("data");
      auto* app0 = new segment_app0_t(m__io__raw_data, this, m__root);
      data_vobj = app0->veles_obj;
      m_data = app0;
      m__io->popName();
      break;
    }
    default:
      break;
    }
    if (m_data != nullptr) {
      m__io->addSubchunkItem(data_start, data_end, "data", data_vobj);
    }
  }
  n_image_data = true;
  if (marker() == MARKER_ENUM_SOS) {
    n_image_data = false;
    m__io->pushName("image_data");
    m_image_data = m__io->read_bytes_full();
    m__io->popName();
  }
  m__io->endChunk();
}

jpeg_t::segment_t::~segment_t() {
  delete m__io__raw_data;
  if (!n_data && m_data != nullptr) {
    switch (m_marker) {
    case MARKER_ENUM_SOS:
      delete static_cast<segment_sos_t*>(m_data);
      break;
    case MARKER_ENUM_APP1:
      delete static_cast<segment_app1_t*>(m_data);
      break;
    case MARKER_ENUM_SOF0:
      delete static_cast<segment_sof0_t*>(m_data);
      break;
    case MARKER_ENUM_APP0:
      delete static_cast<segment_app0_t*>(m_data);
      break;
    default:
      break;
    }
  }
}

jpeg_t::segment_sos_t::segment_sos_t(kaitai::kstream* p_io,
                                      jpeg_t::segment_t* p_parent,
                                      jpeg_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("segment_sos");
  m__io->pushName("num_components");
  m_num_components = m__io->read_u1();
  m__io->popName();
  m_components = new std::vector<component_t*>();
  for (int i = 0; i < num_components(); i++) {
    m__io->pushName("components");
    m_components->push_back(new component_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->pushName("start_spectral_selection");
  m_start_spectral_selection = m__io->read_u1();
  m__io->popName();
  m__io->pushName("end_spectral");
  m_end_spectral = m__io->read_u1();
  m__io->popName();
  m__io->pushName("appr_bit_pos");
  m_appr_bit_pos = m__io->read_u1();
  m__io->popName();
  m__io->endChunk();
}

jpeg_t::segment_sos_t::~segment_sos_t() {
  for (auto it = m_components->begin(); it != m_components->end(); ++it) {
    delete *it;
  }
  delete m_components;
}

jpeg_t::segment_sos_t::component_t::component_t(
    kaitai::kstream* p_io, jpeg_t::segment_sos_t* p_parent,
    jpeg_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("component");
  m__io->pushName("id");
  m_id = static_cast<jpeg_t::component_id_t>(m__io->read_u1());
  m__io->popName();
  m__io->pushName("huffman_table");
  m_huffman_table = m__io->read_u1();
  m__io->popName();
  m__io->endChunk();
}

jpeg_t::segment_sos_t::component_t::~component_t() {}

jpeg_t::segment_app1_t::segment_app1_t(kaitai::kstream* p_io,
                                        jpeg_t::segment_t* p_parent,
                                        jpeg_t* p_root)
    : kaitai::kstruct(p_io), m_body(nullptr) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("segment_app1");
  m__io->pushName("magic");
  m_magic = m__io->read_strz("ASCII", 0, false, true, true);
  m__io->popName();
  if (magic() == "Exif") {
    m__io->pushName("body");
    m_body = new exif_in_jpeg_t(m__io, this, m__root);
    m__io->popName();
  }
  m__io->endChunk();
}

jpeg_t::segment_app1_t::~segment_app1_t() {
  delete m_body;
}

jpeg_t::exif_in_jpeg_t::exif_in_jpeg_t(kaitai::kstream* p_io,
                                        jpeg_t::segment_app1_t* p_parent,
                                        jpeg_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("exif_in_jpeg");
  m__io->pushName("extra_zero");
  m_extra_zero = m__io->ensure_fixed_contents(std::string("\x00", 1));
  m__io->popName();
  m__io->pushName("raw_data");
  m_raw_data = m__io->read_bytes_full();
  m__io->popName();
  m__io->endChunk();
}

jpeg_t::exif_in_jpeg_t::~exif_in_jpeg_t() {}

jpeg_t::segment_sof0_t::segment_sof0_t(kaitai::kstream* p_io,
                                        jpeg_t::segment_t* p_parent,
                                        jpeg_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("segment_sof0");
  m__io->pushName("bits_per_sample");
  m_bits_per_sample = m__io->read_u1();
  m__io->popName();
  m__io->pushName("image_height");
  m_image_height = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("image_width");
  m_image_width = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("num_components");
  m_num_components = m__io->read_u1();
  m__io->popName();
  m_components = new std::vector<component_t*>();
  for (int i = 0; i < num_components(); i++) {
    m__io->pushName("components");
    m_components->push_back(new component_t(m__io, this, m__root));
    m__io->popName();
  }
  m__io->endChunk();
}

jpeg_t::segment_sof0_t::~segment_sof0_t() {
  for (auto it = m_components->begin(); it != m_components->end(); ++it) {
    delete *it;
  }
  delete m_components;
}

jpeg_t::segment_sof0_t::component_t::component_t(
    kaitai::kstream* p_io, jpeg_t::segment_sof0_t* p_parent,
    jpeg_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("component");
  f_sampling_x = false;
  f_sampling_y = false;
  m__io->pushName("id");
  m_id = static_cast<jpeg_t::component_id_t>(m__io->read_u1());
  m__io->popName();
  m__io->pushName("sampling_factors");
  m_sampling_factors = m__io->read_u1();
  m__io->popName();
  m__io->pushName("quantization_table_id");
  m_quantization_table_id = m__io->read_u1();
  m__io->popName();
  m__io->endChunk();
}

jpeg_t::segment_sof0_t::component_t::~component_t() {}

int32_t jpeg_t::segment_sof0_t::component_t::sampling_x() {
  if (f_sampling_x)
    return m_sampling_x;
  m_sampling_x = ((sampling_factors() & 240) >> 4);
  f_sampling_x = true;
  return m_sampling_x;
}

int32_t jpeg_t::segment_sof0_t::component_t::sampling_y() {
  if (f_sampling_y)
    return m_sampling_y;
  m_sampling_y = (sampling_factors() & 15);
  f_sampling_y = true;
  return m_sampling_y;
}

jpeg_t::segment_app0_t::segment_app0_t(kaitai::kstream* p_io,
                                        jpeg_t::segment_t* p_parent,
                                        jpeg_t* p_root)
    : kaitai::kstruct(p_io) {
  m__io->pushName("_parent");
  m__parent = p_parent;
  m__io->popName();
  m__io->pushName("_root");
  m__root = p_root;
  m__io->popName();
  veles_obj = m__io->startChunk("segment_app0");
  m__io->pushName("magic");
  m_magic = m__io->read_str_byte_limit(5, "ASCII");
  m__io->popName();
  m__io->pushName("version_major");
  m_version_major = m__io->read_u1();
  m__io->popName();
  m__io->pushName("version_minor");
  m_version_minor = m__io->read_u1();
  m__io->popName();
  m__io->pushName("density_units");
  m_density_units = static_cast<density_unit_t>(m__io->read_u1());
  m__io->popName();
  m__io->pushName("density_x");
  m_density_x = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("density_y");
  m_density_y = m__io->read_u2be();
  m__io->popName();
  m__io->pushName("thumbnail_x");
  m_thumbnail_x = m__io->read_u1();
  m__io->popName();
  m__io->pushName("thumbnail_y");
  m_thumbnail_y = m__io->read_u1();
  m__io->popName();
  m__io->pushName("thumbnail");
  m_thumbnail = m__io->read_bytes(
      static_cast<size_t>(thumbnail_x()) * static_cast<size_t>(thumbnail_y()) * 3);
  m__io->popName();
  m__io->endChunk();
}

jpeg_t::segment_app0_t::~segment_app0_t() {}
