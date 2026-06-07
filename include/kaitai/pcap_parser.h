#pragma once

#include "kaitai/pcap.h"
#include "parser/parser.h"

namespace veles {
namespace kaitai {

class PcapParser : public parser::Parser {
 public:
  PcapParser() : parser::Parser("pcap (ksy)") {}
  void parse(const dbif::ObjectHandle& blob, uint64_t start,
             const dbif::ObjectHandle& parent_chunk) override {
    try {
      auto stream = kaitai::kstream(blob, start, parent_chunk);
      auto parser = pcap_t(&stream);
    } catch (const std::exception&) {
    }
  }
};

}  // namespace kaitai
}  // namespace veles
