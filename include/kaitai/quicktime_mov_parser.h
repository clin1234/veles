#include "kaitai/quicktime_mov.h"
#include "parser/parser.h"

namespace veles {
namespace kaitai {
class Quicktime_movParser : public parser::Parser {
 public:
  Quicktime_movParser() : parser::Parser("quicktime_mov (ksy)") {}
  void parse(const dbif::ObjectHandle& blob, uint64_t start,
             const dbif::ObjectHandle& parent_chunk) override {
    try {
      auto stream = kaitai::kstream(blob, start, parent_chunk);
      kaitai::quicktime_mov_t parser(&stream);
    } catch (const std::exception&) {
    }
  }
};

}  // namespace kaitai
}  // namespace veles
