#include "kaitai/regf.h"
#include "parser/parser.h"

namespace veles {
namespace kaitai {

class RegfParser : public parser::Parser {
 public:
  RegfParser() : parser::Parser("regf (ksy)") {}
  void parse(const dbif::ObjectHandle& blob, uint64_t start,
             const dbif::ObjectHandle& parent_chunk) override {
    try {
      auto stream = kaitai::kstream(blob, start, parent_chunk);
      auto parser = regf_t(&stream);
    } catch (const std::exception&) {
    }
  }
};

}  // namespace kaitai
}  // namespace veles
