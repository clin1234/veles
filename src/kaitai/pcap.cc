// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/pcap.h"

#include <iostream>
#include <fstream>
#include "kaitai/ethernet_frame.h"

pcap_t::pcap_t(kaitai::kstream *p_io, kaitai::kstruct *p_parent, pcap_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = this;
    veles_obj = m__io->startChunk("pcap");
    m_hdr = new header_t(m__io, this, m__root);
    m_packets = new std::vector<packet_t*>();
    while (!m__io->is_eof()) {
        m_packets->push_back(new packet_t(m__io, this, m__root));
    }
    m__io->endChunk();
}

pcap_t::~pcap_t() {
    delete m_hdr;
    for (std::vector<packet_t*>::iterator it = m_packets->begin(); it != m_packets->end(); ++it) {
        delete *it;
    }
    delete m_packets;
}

pcap_t::packet_ppi_t::packet_ppi_t(kaitai::kstream *p_io, pcap_t::packet_t *p_parent, pcap_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = p_root;
    veles_obj = m__io->startChunk("packet_ppi");
    m_header = new packet_ppi_header_t(m__io, this, m__root);
    m_fields = new std::vector<packet_ppi_field_t*>();
    while (!m__io->is_eof()) {
        m_fields->push_back(new packet_ppi_field_t(m__io, this, m__root));
    }
    m__io->endChunk();
}

pcap_t::packet_ppi_t::~packet_ppi_t() {
    delete m_header;
    for (std::vector<packet_ppi_field_t*>::iterator it = m_fields->begin(); it != m_fields->end(); ++it) {
        delete *it;
    }
    delete m_fields;
}

pcap_t::packet_ppi_header_t::packet_ppi_header_t(kaitai::kstream *p_io, pcap_t::packet_ppi_t *p_parent, pcap_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = p_root;
    veles_obj = m__io->startChunk("packet_ppi_header");
    m__io->pushName("pph_version");
    m_pph_version = m__io->read_u1();
    m__io->popName();
    m__io->pushName("pph_flags");
    m_pph_flags = m__io->read_u1();
    m__io->popName();
    m__io->pushName("pph_len");
    m_pph_len = m__io->read_u2le();
    m__io->popName();
    m__io->pushName("pph_dlt");
    m_pph_dlt = m__io->read_u4le();
    m__io->popName();
    m__io->endChunk();
}

pcap_t::packet_ppi_header_t::~packet_ppi_header_t() {
}

pcap_t::header_t::header_t(kaitai::kstream *p_io, pcap_t *p_parent, pcap_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = p_root;
    veles_obj = m__io->startChunk("header");
    m__io->pushName("magic_number");
    m_magic_number = m__io->ensure_fixed_contents(std::string("\xD4\xC3\xB2\xA1", 4));
    m__io->popName();
    m__io->pushName("version_major");
    m_version_major = m__io->read_u2le();
    m__io->popName();
    m__io->pushName("version_minor");
    m_version_minor = m__io->read_u2le();
    m__io->popName();
    m__io->pushName("thiszone");
    m_thiszone = m__io->read_s4le();
    m__io->popName();
    m__io->pushName("sigfigs");
    m_sigfigs = m__io->read_u4le();
    m__io->popName();
    m__io->pushName("snaplen");
    m_snaplen = m__io->read_u4le();
    m__io->popName();
    m__io->pushName("network");
    m_network = static_cast<pcap_t::linktype_t>(m__io->read_u4le());
    m__io->popName();
    m__io->endChunk();
}

pcap_t::header_t::~header_t() {
}

pcap_t::radio_802_11_common_body_t::radio_802_11_common_body_t(kaitai::kstream *p_io, kaitai::kstruct *p_parent, pcap_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = p_root;
    m_tsf_timer = m__io->read_u8le();
    m_flags = m__io->read_u2le();
    m_rate = m__io->read_u2le();
    m_channel_freq = m__io->read_u2le();
    m_channel_flags = m__io->read_u2le();
    m_fhss_hopset = m__io->read_u1();
    m_fhss_pattern = m__io->read_u1();
    m_dbm_antsignal = m__io->read_s1();
    m_dbm_antnoise = m__io->read_s1();
}

pcap_t::radio_802_11_common_body_t::~radio_802_11_common_body_t() {
}

pcap_t::packet_ppi_field_t::packet_ppi_field_t(kaitai::kstream *p_io, pcap_t::packet_ppi_t *p_parent, pcap_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = p_root;
    veles_obj = m__io->startChunk("packet_ppi_field");
    m__io->pushName("pfh_type");
    m_pfh_type = m__io->read_u2le();
    m__io->popName();
    m__io->pushName("pfh_datalen");
    m_pfh_datalen = m__io->read_u2le();
    m__io->popName();
    m__io->pushName("body");
    m_body = m__io->read_bytes(pfh_datalen());
    m__io->popName();
    m__io->endChunk();
}

pcap_t::packet_ppi_field_t::~packet_ppi_field_t() {
}

pcap_t::packet_t::packet_t(kaitai::kstream *p_io, pcap_t *p_parent, pcap_t *p_root) : kaitai::kstruct(p_io) {
    m__parent = p_parent;
    m__root = p_root;
    m__io__raw_ppi_body = nullptr;
    m__io__raw_ethernet_body = nullptr;
    m_ppi_body = nullptr;
    m_ethernet_body = nullptr;
    veles_obj = m__io->startChunk("packet");
    m__io->pushName("ts_sec");
    m_ts_sec = m__io->read_u4le();
    m__io->popName();
    m__io->pushName("ts_usec");
    m_ts_usec = m__io->read_u4le();
    m__io->popName();
    m__io->pushName("incl_len");
    m_incl_len = m__io->read_u4le();
    m__io->popName();
    m__io->pushName("orig_len");
    m_orig_len = m__io->read_u4le();
    m__io->popName();
    n_body = true;
    if (_root()->hdr()->network() != LINKTYPE_PPI && _root()->hdr()->network() != LINKTYPE_ETHERNET) {
        n_body = false;
        m__io->pushName("body");
        m_body = m__io->read_bytes(incl_len());
        m__io->popName();
    }
    n_ppi_body = true;
    if (_root()->hdr()->network() == LINKTYPE_PPI) {
        n_ppi_body = false;
        uint64_t ppi_start = m__io->pos();
        m__io->pushName("_skip_me_ppi_body");
        m__raw_ppi_body = m__io->read_bytes(incl_len());
        m__io->popName();
        m__io__raw_ppi_body = new kaitai::kstream(m__io->blob(), ppi_start, veles_obj, incl_len());
        m_ppi_body = new packet_ppi_t(m__io__raw_ppi_body, this, m__root);
        m__io->addSubchunkItem(ppi_start, ppi_start + incl_len(), "ppi_body", m_ppi_body->veles_obj);
    }
    n_ethernet_body = true;
    if (_root()->hdr()->network() == LINKTYPE_ETHERNET) {
        n_ethernet_body = false;
        m__io->pushName("body");
        m__raw_ethernet_body = m__io->read_bytes(incl_len());
        m__io->popName();
        m__io__raw_ethernet_body = new kaitai::kstream(m__raw_ethernet_body);
        m_ethernet_body = new ethernet_frame_t(m__io__raw_ethernet_body);
    }
    m__io->endChunk();
}

pcap_t::packet_t::~packet_t() {
    if (!n_ppi_body) {
        delete m__io__raw_ppi_body;
        delete m_ppi_body;
    }
    if (!n_ethernet_body) {
        delete m__io__raw_ethernet_body;
        delete m_ethernet_body;
    }
}
