#pragma once

#include "kaitai/bson.h"
#include "parser/parser.h"

namespace veles {
namespace kaitai {

class BsonParser : public parser::Parser {
 public:
  BsonParser() : parser::Parser("bson (ksy)") {}
  void parse(const dbif::ObjectHandle& blob, uint64_t start,
             const dbif::ObjectHandle& parent_chunk) override {
    try {
      auto stream = kaitai::kstream(blob, start, parent_chunk);
      auto parser = bson_t(&stream);
    } catch (const std::exception&) {
    }
  }
};

}  // namespace kaitai
}  // namespace veles
