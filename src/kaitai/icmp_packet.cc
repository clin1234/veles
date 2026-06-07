// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/icmp_packet.h"

#include <iostream>
#include <fstream>

icmp_packet_t::icmp_packet_t(kaitai::kstream *p_io, kaitai::kstruct *p_parent, icmp_packet_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = this;
    veles_obj = m__io->startChunk("icmp_packet");
    m__io->pushName("icmp_type");
    m_icmp_type = static_cast<icmp_packet_t::icmp_type_enum_t>(m__io->read_u1());
    m__io->popName();
    n_destination_unreachable = true;
    if (icmp_type() == ICMP_TYPE_ENUM_DESTINATION_UNREACHABLE) {
        n_destination_unreachable = false;
        m_destination_unreachable = new destination_unreachable_msg_t(m__io, this, m__root);
    }
    n_time_exceeded = true;
    if (icmp_type() == ICMP_TYPE_ENUM_TIME_EXCEEDED) {
        n_time_exceeded = false;
        m_time_exceeded = new time_exceeded_msg_t(m__io, this, m__root);
    }
    n_echo = true;
    if (icmp_type() == ICMP_TYPE_ENUM_ECHO || icmp_type() == ICMP_TYPE_ENUM_ECHO_REPLY) {
        n_echo = false;
        m_echo = new echo_msg_t(m__io, this, m__root);
    }
    m__io->endChunk();
}

icmp_packet_t::~icmp_packet_t() {
    if (!n_destination_unreachable) {
        delete m_destination_unreachable;
    }
    if (!n_time_exceeded) {
        delete m_time_exceeded;
    }
    if (!n_echo) {
        delete m_echo;
    }
}

icmp_packet_t::destination_unreachable_msg_t::destination_unreachable_msg_t(kaitai::kstream *p_io, icmp_packet_t *p_parent, icmp_packet_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = p_root;
    veles_obj = m__io->startChunk("destination_unreachable");
    m__io->pushName("code");
    m_code = static_cast<icmp_packet_t::destination_unreachable_msg_t::destination_unreachable_code_t>(m__io->read_u1());
    m__io->popName();
    m__io->pushName("checksum");
    m_checksum = m__io->read_u2be();
    m__io->popName();
    m__io->endChunk();
}

icmp_packet_t::destination_unreachable_msg_t::~destination_unreachable_msg_t() {
}

icmp_packet_t::time_exceeded_msg_t::time_exceeded_msg_t(kaitai::kstream *p_io, icmp_packet_t *p_parent, icmp_packet_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = p_root;
    veles_obj = m__io->startChunk("time_exceeded");
    m__io->pushName("code");
    m_code = static_cast<icmp_packet_t::time_exceeded_msg_t::time_exceeded_code_t>(m__io->read_u1());
    m__io->popName();
    m__io->pushName("checksum");
    m_checksum = m__io->read_u2be();
    m__io->popName();
    m__io->endChunk();
}

icmp_packet_t::time_exceeded_msg_t::~time_exceeded_msg_t() {
}

icmp_packet_t::echo_msg_t::echo_msg_t(kaitai::kstream *p_io, icmp_packet_t *p_parent, icmp_packet_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = p_root;
    veles_obj = m__io->startChunk("icmp_echo");
    m__io->pushName("code");
    m_code = m__io->ensure_fixed_contents(std::string("\x00", 1));
    m__io->popName();
    m__io->pushName("checksum");
    m_checksum = m__io->read_u2be();
    m__io->popName();
    m__io->pushName("identifier");
    m_identifier = m__io->read_u2be();
    m__io->popName();
    m__io->pushName("seq_num");
    m_seq_num = m__io->read_u2be();
    m__io->popName();
    m__io->endChunk();
}

icmp_packet_t::echo_msg_t::~echo_msg_t() {
}
