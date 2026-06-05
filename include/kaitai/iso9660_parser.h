#include "kaitai/iso9660.h"
#include "parser/parser.h"

namespace veles {
namespace kaitai {
class ISO9660Parser : public parser::Parser {
 public:
  ISO9660Parser() : parser::Parser("iso9660 (ksy)") {}
  void parse(const dbif::ObjectHandle& blob, uint64_t start,
             const dbif::ObjectHandle& parent_chunk) override {
    try {
      auto stream = kaitai::kstream(blob, start, parent_chunk);
      auto parser = iso9660_t(&stream);
    } catch (const std::exception&) {
    }
  }
};

}  // namespace kaitai
}  // namespace veles
