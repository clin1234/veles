// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/ethernet_frame.h"

#include <iostream>
#include <fstream>
#include "kaitai/ipv4_packet.h"

ethernet_frame_t::ethernet_frame_t(kaitai::kstream *p_io, kaitai::kstruct *p_parent, ethernet_frame_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = this;
    m__io__raw_ipv4_body = nullptr;
    m_ipv4_body = nullptr;
    veles_obj = m__io->startChunk("ethernet_frame");
    m__io->pushName("dst_mac");
    m_dst_mac = m__io->read_bytes(6);
    m__io->popName();
    m__io->pushName("src_mac");
    m_src_mac = m__io->read_bytes(6);
    m__io->popName();
    m__io->pushName("ether_type");
    m_ether_type = static_cast<ethernet_frame_t::ether_type_enum_t>(m__io->read_u2be());
    m__io->popName();
    n_ipv4_body = true;
    if (ether_type() == ETHER_TYPE_ENUM_IPV4) {
        n_ipv4_body = false;
        uint64_t ipv4_start = m__io->pos();
        m__io->pushName("_skip_me_ipv4_body");
        m__raw_ipv4_body = m__io->read_bytes_full();
        m__io->popName();
        uint64_t ipv4_len = m__raw_ipv4_body.size();
        m__io__raw_ipv4_body = new kaitai::kstream(m__io->blob(), ipv4_start, veles_obj, ipv4_start + ipv4_len);
        m_ipv4_body = new ipv4_packet_t(m__io__raw_ipv4_body);
        m__io->addSubchunkItem(ipv4_start, ipv4_start + ipv4_len, "ipv4_body", m_ipv4_body->veles_obj);
    }
    n_body = true;
    if (ether_type() != ETHER_TYPE_ENUM_IPV4) {
        n_body = false;
        m__io->pushName("body");
        m_body = m__io->read_bytes_full();
        m__io->popName();
    }
    m__io->endChunk();
}

ethernet_frame_t::~ethernet_frame_t() {
    if (!n_ipv4_body) {
        delete m__io__raw_ipv4_body;
        delete m_ipv4_body;
    }
}
