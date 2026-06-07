// This is a generated file! Please edit source .ksy file and use
// kaitai-struct-compiler to rebuild

#include "kaitai/vlq_base128_be.h"

vlq_base128_be_t::vlq_base128_be_t(kaitai::kstream* p_io)
    : kaitai::kstruct(p_io), f_value(false), f_len(false) {
  veles_obj = m__io->startChunk("vlq");
  m_groups = new std::vector<uint8_t>();
  do {
    m__io->pushName("groups");
    m_groups->push_back(m__io->read_u1());
    m__io->popName();
  } while ((m_groups->back() & 0x80) != 0);
  m__io->endChunk();
}

vlq_base128_be_t::~vlq_base128_be_t() { delete m_groups; }

int32_t vlq_base128_be_t::value() {
  if (f_value) return m_value;
  int32_t result = 0;
  for (auto b : *m_groups)
    result = (result << 7) | (b & 0x7F);
  m_value = result;
  f_value = true;
  return m_value;
}

int32_t vlq_base128_be_t::len() {
  if (f_len) return m_len;
  m_len = static_cast<int32_t>(m_groups->size());
  f_len = true;
  return m_len;
}
