/*
 * Copyright 2026 Charlie Lin, 2017 Codilime
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "data/types.h"
#include "parser/stream.h"

namespace veles {
namespace kaitai {

/**
 * Kaitai Stream class (veles::kaitai::kstream) is an implementation of
 * Kaitai Struct stream API for Veles.
 * (https://github.com/kaitai-io/kaitai_struct/wiki/Kaitai-Struct-stream-API)
 * It's implemented as a wrapper over Veles StreamParser.
 *
 * It has also additional methods which allow Veles to know field names and
 * create chunk tree.
 */
class kstream {
 public:
  explicit kstream(const veles::dbif::ObjectHandle& blob, uint64_t start = 0,
                   const veles::dbif::ObjectHandle& parent_chunk =
                       veles::dbif::ObjectHandle(),
                   uint64_t max_size = 0, bool error = false);
  explicit kstream(const std::string& data);
  ~kstream();

  /** Kaitai Struct Stream API methods */
  void close();
  bool is_eof();
  void seek(uint64_t pos);
  uint64_t pos();
  uint64_t size();

  int8_t read_s1();

  int16_t read_s2be();
  int32_t read_s4be();
  int64_t read_s8be();

  int16_t read_s2le();
  int32_t read_s4le();
  int64_t read_s8le();

  uint8_t read_u1();

  uint16_t read_u2be();
  uint32_t read_u4be();
  uint64_t read_u8be();

  uint16_t read_u2le();
  uint32_t read_u4le();
  uint64_t read_u8le();

  float read_f4be();
  double read_f8be();

  float read_f4le();
  double read_f8le();

  std::string read_str_eos(const char* enc);
  std::string read_str_byte_limit(size_t len, const char* enc);
  std::string read_strz(const char* enc, char term, bool include, bool consume,
                        bool eos_error);

  std::string read_bytes(size_t len);
  std::string read_bytes_full();
  std::string ensure_fixed_contents(const std::string& expected);

  static std::string bytes_to_string(const std::vector<uint8_t>& bytes,
                                     const char* src_enc);

  /** additional methods required by Veles */
  void pushName(const char* name);
  void popName();
  const char* currentName() { return current_name_; }
  veles::dbif::ObjectHandle startChunk(const char* name);
  veles::dbif::ObjectHandle endChunk();
  veles::parser::StreamParser* parser() { return parser_; }
  veles::dbif::ObjectHandle blob() { return obj_; }
  bool error() { return error_; }

 private:
  veles::dbif::ObjectHandle obj_;
  veles::parser::StreamParser* parser_;
  std::vector<std::string> names_stack_;
  const char* current_name_;
  bool error_;
  uint64_t max_size_;

  // Used only when constructed from a std::string (no StreamParser).
  // startChunk/endChunk are no-ops in this mode; sub-chunks are not
  // recorded in the Veles chunk tree.
  std::string data_;
  uint64_t data_pos_;
  std::string data_read(size_t n);
  uint64_t data_uint(size_t n, bool little_endian);
};

}  // namespace kaitai
}  // namespace veles
