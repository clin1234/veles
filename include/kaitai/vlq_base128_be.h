#pragma once

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <kaitai/kaitaistruct.h>
#include <kaitai/kaitaistream.h>

#include <stdint.h>
#include <vector>

class vlq_base128_be_t : public kaitai::kstruct {
 public:
  explicit vlq_base128_be_t(kaitai::kstream* p_io);
  veles::dbif::ObjectHandle veles_obj;
  ~vlq_base128_be_t();
  int32_t value();
  int32_t len();

 private:
  bool f_value;
  int32_t m_value;
  bool f_len;
  int32_t m_len;
  std::vector<uint8_t>* m_groups;
};
