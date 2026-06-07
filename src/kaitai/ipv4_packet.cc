// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/ipv4_packet.h"

#include <iostream>
#include <fstream>
#include "kaitai/tcp_segment.h"
#include "kaitai/icmp_packet.h"

ipv4_packet_t::ipv4_packet_t(kaitai::kstream *p_io, kaitai::kstruct *p_parent, ipv4_packet_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = this;
    f_version = false;
    f_ihl = false;
    f_ihl_bytes = false;
    veles_obj = m__io->startChunk("ipv4_packet");
    m__io->pushName("b1");
    m_b1 = m__io->read_u1();
    m__io->popName();
    m__io->pushName("b2");
    m_b2 = m__io->read_u1();
    m__io->popName();
    m__io->pushName("total_length");
    m_total_length = m__io->read_u2be();
    m__io->popName();
    m__io->pushName("identification");
    m_identification = m__io->read_u2be();
    m__io->popName();
    m__io->pushName("b67");
    m_b67 = m__io->read_u2be();
    m__io->popName();
    m__io->pushName("ttl");
    m_ttl = m__io->read_u1();
    m__io->popName();
    m__io->pushName("protocol");
    m_protocol = static_cast<ipv4_packet_t::protocol_enum_t>(m__io->read_u1());
    m__io->popName();
    m__io->pushName("header_checksum");
    m_header_checksum = m__io->read_u2be();
    m__io->popName();
    m__io->pushName("src_ip_addr");
    m_src_ip_addr = m__io->read_bytes(4);
    m__io->popName();
    m__io->pushName("dst_ip_addr");
    m_dst_ip_addr = m__io->read_bytes(4);
    m__io->popName();
    uint64_t options_start = m__io->pos();
    uint64_t options_len = (ihl_bytes() > 20) ? static_cast<uint64_t>(ihl_bytes() - 20) : 0;
    if (options_len > 0) {
        m__io->pushName("_skip_me_options");
        m__raw_options = m__io->read_bytes(options_len);
        m__io->popName();
        m__io__raw_options = new kaitai::kstream(m__io->blob(), options_start, veles_obj, options_start + options_len);
        m_options = new ipv4_options_t(m__io__raw_options, this, m__root);
        m__io->addSubchunkItem(options_start, options_start + options_len, "options", m_options->veles_obj);
    } else {
        m__raw_options = m__io->read_bytes(0);
        m__io__raw_options = new kaitai::kstream(m__raw_options);
        m_options = new ipv4_options_t(m__io__raw_options, this, m__root);
    }
    n_tcp_segment_body = true;
    if (protocol() == PROTOCOL_ENUM_TCP) {
        n_tcp_segment_body = false;
        m_tcp_segment_body = new tcp_segment_t(m__io);
    }
    n_icmp_body = true;
    if (protocol() == PROTOCOL_ENUM_ICMP) {
        n_icmp_body = false;
        m_icmp_body = new icmp_packet_t(m__io);
    }
    n_body = true;
    if (protocol() != PROTOCOL_ENUM_TCP && protocol() != PROTOCOL_ENUM_ICMP) {
        n_body = false;
        m__io->pushName("body");
        m_body = m__io->read_bytes((total_length() - ihl_bytes()));
        m__io->popName();
    }
    m__io->endChunk();
}

ipv4_packet_t::~ipv4_packet_t() {
    delete m__io__raw_options;
    delete m_options;
    if (!n_tcp_segment_body) {
        delete m_tcp_segment_body;
    }
    if (!n_icmp_body) {
        delete m_icmp_body;
    }
}

ipv4_packet_t::ipv4_options_t::ipv4_options_t(kaitai::kstream *p_io, ipv4_packet_t *p_parent, ipv4_packet_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = p_root;
    veles_obj = m__io->startChunk("ipv4_options");
    m_entries = new std::vector<ipv4_option_t*>();
    while (!m__io->is_eof()) {
        m_entries->push_back(new ipv4_option_t(m__io, this, m__root));
    }
    m__io->endChunk();
}

ipv4_packet_t::ipv4_options_t::~ipv4_options_t() {
    for (std::vector<ipv4_option_t*>::iterator it = m_entries->begin(); it != m_entries->end(); ++it) {
        delete *it;
    }
    delete m_entries;
}

ipv4_packet_t::ipv4_option_t::ipv4_option_t(kaitai::kstream *p_io, ipv4_packet_t::ipv4_options_t *p_parent, ipv4_packet_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = p_root;
    f_copy = false;
    f_opt_class = false;
    f_number = false;
    veles_obj = m__io->startChunk("ipv4_option");
    m__io->pushName("b1");
    m_b1 = m__io->read_u1();
    m__io->popName();
    m__io->pushName("len");
    m_len = m__io->read_u1();
    m__io->popName();
    m__io->pushName("body");
    m_body = m__io->read_bytes((len() > 2) ? ((len() - 2)) : (0));
    m__io->popName();
    m__io->endChunk();
}

ipv4_packet_t::ipv4_option_t::~ipv4_option_t() {
}

int32_t ipv4_packet_t::ipv4_option_t::copy() {
    if (f_copy)
        return m_copy;
    m_copy = ((b1() & 128) >> 7);
    f_copy = true;
    return m_copy;
}

int32_t ipv4_packet_t::ipv4_option_t::opt_class() {
    if (f_opt_class)
        return m_opt_class;
    m_opt_class = ((b1() & 96) >> 5);
    f_opt_class = true;
    return m_opt_class;
}

int32_t ipv4_packet_t::ipv4_option_t::number() {
    if (f_number)
        return m_number;
    m_number = (b1() & 31);
    f_number = true;
    return m_number;
}

int32_t ipv4_packet_t::version() {
    if (f_version)
        return m_version;
    m_version = ((b1() & 240) >> 4);
    f_version = true;
    return m_version;
}

int32_t ipv4_packet_t::ihl() {
    if (f_ihl)
        return m_ihl;
    m_ihl = (b1() & 15);
    f_ihl = true;
    return m_ihl;
}

int32_t ipv4_packet_t::ihl_bytes() {
    if (f_ihl_bytes)
        return m_ihl_bytes;
    m_ihl_bytes = (ihl() * 4);
    f_ihl_bytes = true;
    return m_ihl_bytes;
}
