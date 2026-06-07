#pragma once

#include "kaitai/standard_midi_file.h"
#include "parser/parser.h"

namespace veles {
namespace kaitai {

class StandardMidiFileParser : public parser::Parser {
 public:
  StandardMidiFileParser() : parser::Parser("standard_midi_file (ksy)") {}
  void parse(const dbif::ObjectHandle& blob, uint64_t start,
             const dbif::ObjectHandle& parent_chunk) override {
    try {
      auto stream = kaitai::kstream(blob, start, parent_chunk);
      auto parser = standard_midi_file_t(&stream);
    } catch (const std::exception&) {
    }
  }
};

}  // namespace kaitai
}  // namespace veles
