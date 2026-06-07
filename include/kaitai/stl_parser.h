#pragma once

#include "kaitai/stl.h"
#include "parser/parser.h"

namespace veles {
namespace kaitai {

class StlParser : public parser::Parser {
 public:
  StlParser() : parser::Parser("stl (ksy)") {}
  void parse(const dbif::ObjectHandle& blob, uint64_t start,
             const dbif::ObjectHandle& parent_chunk) override {
    try {
      auto stream = kaitai::kstream(blob, start, parent_chunk);
      auto parser = stl_t(&stream);
    } catch (const std::exception&) {
    }
  }
};

}  // namespace kaitai
}  // namespace veles
