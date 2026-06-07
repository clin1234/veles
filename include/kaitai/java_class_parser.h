#include "kaitai/java_class.h"
#include "parser/parser.h"

namespace veles {
namespace kaitai {

class JavaClassParser : public parser::Parser {
 public:
  JavaClassParser() : parser::Parser("java_class (ksy)") {}
  void parse(const dbif::ObjectHandle& blob, uint64_t start,
             const dbif::ObjectHandle& parent_chunk) override {
    try {
      auto stream = kaitai::kstream(blob, start, parent_chunk);
      auto parser = java_class_t(&stream);
    } catch (const std::exception&) {
    }
  }
};

}  // namespace kaitai
}  // namespace veles
