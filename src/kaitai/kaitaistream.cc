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

#include "kaitai/kaitaistream.h"

#include <cstring>

namespace veles {
namespace kaitai {

kaitai::kstream::kstream(const veles::dbif::ObjectHandle& blob, uint64_t start,
                         const veles::dbif::ObjectHandle& parent_chunk,
                         uint64_t max_size, bool error)
    : obj_(blob), current_name_(nullptr), error_(error), max_size_(max_size),
      data_pos_(0) {
  parser_ = new veles::parser::StreamParser(blob, start, parent_chunk);
}

kaitai::kstream::kstream(const std::string& data)
    : current_name_(nullptr), error_(false), max_size_(0),
      parser_(nullptr), data_(data), data_pos_(0) {}

kaitai::kstream::~kstream() { delete parser_; }

std::string kaitai::kstream::data_read(size_t n) {
  if (data_pos_ + n > data_.size()) {
    error_ = true;
    n = data_.size() - data_pos_;
  }
  std::string result = data_.substr(data_pos_, n);
  data_pos_ += n;
  return result;
}

uint64_t kaitai::kstream::data_uint(size_t n, bool little_endian) {
  std::string bytes = data_read(n);
  uint64_t result = 0;
  if (little_endian) {
    for (size_t i = 0; i < bytes.size(); i++)
      result |= static_cast<uint64_t>(static_cast<uint8_t>(bytes[i])) << (8 * i);
  } else {
    for (size_t i = 0; i < bytes.size(); i++)
      result = (result << 8) | static_cast<uint8_t>(bytes[i]);
  }
  return result;
}

veles::dbif::ObjectHandle kaitai::kstream::startChunk(const char* name) {
  if (parser_ == nullptr) return {};
  return parser_->startChunk(name, name);
}

veles::dbif::ObjectHandle kaitai::kstream::endChunk() {
  if (parser_ == nullptr) return {};
  return parser_->endChunk();
}

void kaitai::kstream::seek(uint64_t pos) {
  if (parser_ == nullptr) { data_pos_ = pos; return; }
  parser_->seek(pos);
}

void kaitai::kstream::close() {}

bool kaitai::kstream::is_eof() {
  if (max_size_ != 0 && pos() >= max_size_) return true;
  if (parser_ == nullptr) return error_ || data_pos_ >= data_.size();
  return error_ || parser_->eof();
}

uint64_t kaitai::kstream::pos() {
  if (error_) return 0;
  if (parser_ == nullptr) return data_pos_;
  return parser_->pos();
}

uint64_t kaitai::kstream::size() {
  if (error_) return 0;
  if (parser_ == nullptr) return data_.size();
  return parser_->pos() + parser_->bytesLeft();
}

int8_t kaitai::kstream::read_s1() {
  if (error_) return 0;
  if (parser_ == nullptr) return static_cast<int8_t>(data_uint(1, true));
  return parser_->getByte(current_name_);
}

int16_t kaitai::kstream::read_s2be() {
  if (error_) return 0;
  if (parser_ == nullptr) return static_cast<int16_t>(data_uint(2, false));
  return parser_->getBe16(current_name_, 1)[0];
}

int32_t kaitai::kstream::read_s4be() {
  if (error_) return 0;
  if (parser_ == nullptr) return static_cast<int32_t>(data_uint(4, false));
  return parser_->getBe32(current_name_);
}

int64_t kaitai::kstream::read_s8be() {
  if (error_) return 0;
  if (parser_ == nullptr) return static_cast<int64_t>(data_uint(8, false));
  return parser_->getBe64(current_name_);
}

int16_t kaitai::kstream::read_s2le() {
  if (error_) return 0;
  if (parser_ == nullptr) return static_cast<int16_t>(data_uint(2, true));
  return parser_->getLe16(current_name_, 1)[0];
}

int32_t kaitai::kstream::read_s4le() {
  if (error_) return 0;
  if (parser_ == nullptr) return static_cast<int32_t>(data_uint(4, true));
  return parser_->getLe32(current_name_);
}

int64_t kaitai::kstream::read_s8le() {
  if (error_) return 0;
  if (parser_ == nullptr) return static_cast<int64_t>(data_uint(8, true));
  return parser_->getLe64(current_name_);
}

uint8_t kaitai::kstream::read_u1() {
  if (error_) return 0;
  if (parser_ == nullptr) return static_cast<uint8_t>(data_uint(1, true));
  return parser_->getByte(current_name_);
}

uint16_t kaitai::kstream::read_u2be() {
  if (error_) return 0;
  if (parser_ == nullptr) return static_cast<uint16_t>(data_uint(2, false));
  return parser_->getBe16(current_name_, 1)[0];
}

uint32_t kaitai::kstream::read_u4be() {
  if (error_) return 0;
  if (parser_ == nullptr) return static_cast<uint32_t>(data_uint(4, false));
  return parser_->getBe32(current_name_);
}

uint64_t kaitai::kstream::read_u8be() {
  if (error_) return 0;
  if (parser_ == nullptr) return data_uint(8, false);
  return parser_->getBe64(current_name_);
}

uint16_t kaitai::kstream::read_u2le() {
  if (error_) return 0;
  if (parser_ == nullptr) return static_cast<uint16_t>(data_uint(2, true));
  return parser_->getLe16(current_name_, 1)[0];
}

uint32_t kaitai::kstream::read_u4le() {
  if (error_) return 0;
  if (parser_ == nullptr) return static_cast<uint32_t>(data_uint(4, true));
  return parser_->getLe32(current_name_);
}

uint64_t kaitai::kstream::read_u8le() {
  if (error_) return 0;
  if (parser_ == nullptr) return data_uint(8, true);
  return parser_->getLe64(current_name_);
}

float kaitai::kstream::read_f4be() {
  if (error_) return 0.0f;
  if (parser_ == nullptr) {
    uint32_t raw = static_cast<uint32_t>(data_uint(4, false));
    float ret; memcpy(&ret, &raw, sizeof(float)); return ret;
  }
  return parser_->getFloat32Be(current_name_);
}

double kaitai::kstream::read_f8be() {
  if (error_) return 0.0;
  if (parser_ == nullptr) {
    uint64_t raw = data_uint(8, false);
    double ret; memcpy(&ret, &raw, sizeof(double)); return ret;
  }
  return parser_->getFloat64Be(current_name_);
}

float kaitai::kstream::read_f4le() {
  if (error_) return 0.0f;
  if (parser_ == nullptr) {
    uint32_t raw = static_cast<uint32_t>(data_uint(4, true));
    float ret; memcpy(&ret, &raw, sizeof(float)); return ret;
  }
  return parser_->getFloat32Le(current_name_);
}

double kaitai::kstream::read_f8le() {
  if (error_) return 0.0;
  if (parser_ == nullptr) {
    uint64_t raw = data_uint(8, true);
    double ret; memcpy(&ret, &raw, sizeof(double)); return ret;
  }
  return parser_->getFloat64Le(current_name_);
}

std::string kaitai::kstream::read_str_eos(const char* enc) {
  if (error_) return "";
  if (parser_ == nullptr) {
    std::string s = data_read(data_.size() - data_pos_);
    return bytes_to_string(std::vector<uint8_t>(s.begin(), s.end()), enc);
  }
  return bytes_to_string(parser_->getBytes(current_name_, parser_->bytesLeft()),
                         enc);
}

std::string kaitai::kstream::read_str_byte_limit(size_t len, const char* enc) {
  if (error_) return "";
  if (parser_ == nullptr) {
    std::string s = data_read(len);
    return bytes_to_string(std::vector<uint8_t>(s.begin(), s.end()), enc);
  }
  return bytes_to_string(parser_->getBytes(current_name_, len), enc);
}

std::string kaitai::kstream::read_strz(const char* enc, char term, bool include,
                                       bool consume, bool /*eos_error*/) {
  if (error_) return "";
  if (parser_ == nullptr) {
    size_t end = data_pos_;
    while (end < data_.size() &&
           static_cast<uint8_t>(data_[end]) != static_cast<uint8_t>(term))
      end++;
    bool has_term = (end < data_.size());
    std::string result;
    if (include && consume && has_term) {
      result = data_.substr(data_pos_, end - data_pos_ + 1);
      data_pos_ = end + 1;
    } else {
      result = data_.substr(data_pos_, end - data_pos_);
      data_pos_ = end;
      if (consume && has_term) data_pos_++;
    }
    return bytes_to_string(std::vector<uint8_t>(result.begin(), result.end()),
                           enc);
  }
  auto data = parser_->getBytesUntil(current_name_, term, include && consume);
  if (consume && !include) parser_->skip(1);
  return bytes_to_string(data, enc);
}

std::string kaitai::kstream::read_bytes(size_t len) {
  if (error_) return {};
  if (parser_ == nullptr) return data_read(len);
  // Hack to avoid double chunks when allocating new io from fixed length data
  if (current_name_ != nullptr && strncmp(current_name_, "_skip_me_", 9) == 0) {
    parser_->skip(len);
    return std::string(len, '\0');
  }
  auto result = parser_->getBytes(current_name_, len);
  return std::string(result.begin(), result.end());
}

std::string kaitai::kstream::read_bytes_full() {
  if (error_) return {};
  if (parser_ == nullptr) return data_read(data_.size() - data_pos_);
  return read_bytes(parser_->bytesLeft());
}

std::string kaitai::kstream::ensure_fixed_contents(
    const std::string& expected) {
  if (error_) return {};
  auto result = read_bytes(expected.size());
  if (result != expected) error_ = true;
  return result;
}

std::string kaitai::kstream::bytes_to_string(const std::vector<uint8_t>& bytes,
                                             const char* /*src_enc*/) {
  std::string res;
  for (auto byte : bytes) {
    res += byte;
  }
  return res;
}

void kaitai::kstream::pushName(const char* name) {
  names_stack_.emplace_back(name);
  current_name_ = names_stack_.back().c_str();
}

void kaitai::kstream::popName() {
  if (!names_stack_.empty()) {
    names_stack_.pop_back();
  }
  if (!names_stack_.empty()) {
    current_name_ = names_stack_.back().c_str();
  } else {
    current_name_ = nullptr;
  }
}

}  // namespace kaitai
}  // namespace veles
