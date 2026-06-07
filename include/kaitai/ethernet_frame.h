#pragma once

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <kaitai/kaitaistruct.h>
#include <kaitai/kaitaistream.h>

#include <stdint.h>
#include <vector>
#include <sstream>
class ipv4_packet_t;

class ethernet_frame_t : public kaitai::kstruct {

public:

    enum ether_type_enum_t {
        ETHER_TYPE_ENUM_IPV4 = 2048,
        ETHER_TYPE_ENUM_X_75_INTERNET = 2049,
        ETHER_TYPE_ENUM_NBS_INTERNET = 2050,
        ETHER_TYPE_ENUM_ECMA_INTERNET = 2051,
        ETHER_TYPE_ENUM_CHAOSNET = 2052,
        ETHER_TYPE_ENUM_X_25_LEVEL_3 = 2053,
        ETHER_TYPE_ENUM_ARP = 2054
    };

    ethernet_frame_t(kaitai::kstream* p_io, kaitai::kstruct* p_parent = 0, ethernet_frame_t* p_root = 0);
    veles::dbif::ObjectHandle veles_obj;
    ~ethernet_frame_t();

private:
    std::string m_dst_mac;
    std::string m_src_mac;
    ether_type_enum_t m_ether_type;
    ipv4_packet_t* m_ipv4_body;
    bool n_ipv4_body;

public:
    bool _is_null_ipv4_body() { ipv4_body(); return n_ipv4_body; };

private:
    std::string m_body;
    bool n_body;

public:
    bool _is_null_body() { body(); return n_body; };

private:
    ethernet_frame_t* m__root;
    kaitai::kstruct* m__parent;
    std::string m__raw_ipv4_body;
    kaitai::kstream* m__io__raw_ipv4_body;

public:
    std::string dst_mac() const { return m_dst_mac; }
    std::string src_mac() const { return m_src_mac; }
    ether_type_enum_t ether_type() const { return m_ether_type; }
    ipv4_packet_t* ipv4_body() const { return m_ipv4_body; }
    std::string body() const { return m_body; }
    ethernet_frame_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
    std::string _raw_ipv4_body() const { return m__raw_ipv4_body; }
    kaitai::kstream* _io__raw_ipv4_body() const { return m__io__raw_ipv4_body; }
};

