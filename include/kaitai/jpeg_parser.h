#include "kaitai/jpeg.h"
#include "parser/parser.h"

namespace veles {
namespace kaitai {

class JpegParser : public parser::Parser {
 public:
  JpegParser() : parser::Parser("jpeg (ksy)") {}
  void parse(const dbif::ObjectHandle& blob, uint64_t start,
             const dbif::ObjectHandle& parent_chunk) override {
    try {
      auto stream = kaitai::kstream(blob, start, parent_chunk);
      auto parser = jpeg_t(&stream);
    } catch (const std::exception&) {
    }
  }
};

}  // namespace kaitai
}  // namespace veles
