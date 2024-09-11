#pragma once
#include "protocol/Global.h"

namespace protocol::Utils {

namespace detail {

constexpr uint8 encode_lookup(uint8 c) {
  return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
         "abcdefghijklmnopqrstuvwxyz"
         "0123456789+/"[c];
}
constexpr uint8 decode_lookup(uint8 c) {
  if (c >= 'A' && c <= 'Z')
    return c - 'A';
  if (c >= 'a' && c <= 'z')
    return c - 71;
  if (c >= '0' && c <= '9')
    return c + 4;
  if (c == '+')
    return 62;
  if (c == '/')
    return 63;
  return 64;
}
} // namespace detail

constexpr size_t get_decode_length(std::string_view in) {
  uint8 count = 0;
  size_t input_size = in.size();
  for (auto it = in.rbegin(); *it == '='; ++it) {
    ++count;
  }
  input_size -= count;     // remove padding size
  count = 0;               // reset padding counter
  while (input_size % 4) { // redo padding
    input_size++;
    count++;
  }
  return ((6 * input_size) / 8) - count;
}

inline std::string base64_decode(std::string const &str) {

  size_t input_size = str.size();
  size_t output_size = get_decode_length(str);
  std::string out;
  out.resize(output_size);
  for (size_t i = 0, j = 0; i < input_size;) {
    uint32 c1 = (i > input_size || str[i] == '=')
                      ? 0 & i++
                      : detail::decode_lookup(str[i++]);
    uint32 c2 = (i > input_size || str[i] == '=')
                      ? 0 & i++
                      : detail::decode_lookup(str[i++]);
    uint32 c3 = (i > input_size || str[i] == '=')
                      ? 0 & i++
                      : detail::decode_lookup(str[i++]);
    uint32 c4 = (i > input_size || str[i] == '=')
                      ? 0 & i++
                      : detail::decode_lookup(str[i++]);

    uint32 data =
        (c1 << 3 * 6) + (c2 << 2 * 6) + (c3 << 1 * 6) + (c4 << 0 * 6);

    if (j < output_size)
      out[j++] = static_cast<char>((data >> 2 * 8) & 0xFF);
    if (j < output_size)
      out[j++] = static_cast<char>((data >> 1 * 8) & 0xFF);
    if (j < output_size)
      out[j++] = static_cast<char>((data >> 0 * 8) & 0xFF);
  }
  return out;
}

inline std::string base64_url_to_standard(std::string encoded) {
  auto retstr = encoded;
  std::replace(retstr.begin(), retstr.end(), '-', '+');
  std::replace(retstr.begin(), retstr.end(), '_', '/');
  return retstr;
}

inline std::string base64url_decode(std::string encoded) {
  auto newencoded = base64_url_to_standard(encoded);
  return base64_decode(newencoded);
}

} // namespace protocol::Utils