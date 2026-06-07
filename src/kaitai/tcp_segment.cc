// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/tcp_segment.h"

#include <iostream>
#include <fstream>

tcp_segment_t::tcp_segment_t(kaitai::kstream *p_io, kaitai::kstruct *p_parent, tcp_segment_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = this;
    veles_obj = m__io->startChunk("tcp_segment");
    m__io->pushName("src_port");
    m_src_port = m__io->read_u2be();
    m__io->popName();
    m__io->pushName("dst_port");
    m_dst_port = m__io->read_u2be();
    m__io->popName();
    m__io->pushName("seq_num");
    m_seq_num = m__io->read_u4be();
    m__io->popName();
    m__io->pushName("ack_num");
    m_ack_num = m__io->read_u4be();
    m__io->popName();
    m__io->pushName("b12");
    m_b12 = m__io->read_u1();
    m__io->popName();
    m__io->pushName("b13");
    m_b13 = m__io->read_u1();
    m__io->popName();
    m__io->pushName("window_size");
    m_window_size = m__io->read_u2be();
    m__io->popName();
    m__io->pushName("checksum");
    m_checksum = m__io->read_u2be();
    m__io->popName();
    m__io->pushName("urgent_pointer");
    m_urgent_pointer = m__io->read_u2be();
    m__io->popName();
    m__io->pushName("body");
    m_body = m__io->read_bytes_full();
    m__io->popName();
    m__io->endChunk();
}

tcp_segment_t::~tcp_segment_t() {
}
