#pragma once

#include "kaitai/mach_o.h"
#include "parser/parser.h"

namespace veles {
namespace kaitai {

class MachOParser : public parser::Parser {
 public:
  MachOParser() : parser::Parser("mach_o (ksy)") {}
  void parse(const dbif::ObjectHandle& blob, uint64_t start,
             const dbif::ObjectHandle& parent_chunk) override {
    try {
      auto stream = kaitai::kstream(blob, start, parent_chunk);
      auto parser = mach_o_t(&stream);
    } catch (const std::exception&) {
    }
  }
};

}  // namespace kaitai
}  // namespace veles
