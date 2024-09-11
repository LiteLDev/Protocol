#pragma once

#include "protocol/Global.h"

namespace protocol::inline utils::hash_utils {

template <class T> constexpr void hashCombine(T const &v, size_t &seed) {
  seed ^= v + 0x9e3779b9ull + (seed << 6ull) + (seed >> 2ull);
}

[[nodiscard]] constexpr uint64 doHash(std::string_view x) {
  // hash_64_fnv1a
  uint64 hash = 0xcbf29ce484222325;
  constexpr uint64 prime = 0x100000001b3;
  for (int8 c : x) {
    hash ^= c;
    hash *= prime;
  }
  return hash;
}

[[nodiscard]] constexpr uint64 doHash2(std::string_view x) {
  uint64 rval = 0;
  for (size_t i = 0; i < x.size(); i++) {
    rval ^= ((i & 1) == 0) ? (~((rval << 7) ^ x[i] ^ (rval >> 3)))
                           : (~((rval << 11) ^ x[i] ^ (rval >> 5)));
  }
  return rval;
}

[[nodiscard]] constexpr uint64 doHash3(std::string_view x) {
  uint64 rval = 5381;
  for (int8 c : x) {
    rval = ((rval << 5) + rval) + c;
  }
  return rval;
}

template <class T>
[[nodiscard]] constexpr uint64 hashType(std::vector<T> const &v) {
  size_t seed = v.size();
  for (auto const &x : v) {
    hashCombine(std::hash<T>{}(x), seed);
  }
  return seed;
}
} // namespace protocol::inline utils::hash_utils

namespace protocol::inline literals::inline hash_literals {
[[nodiscard]] consteval uint64 operator""_h(char const *x, size_t len) {
  return protocol::hash_utils::doHash({x, len});
}
} // namespace protocol::inline literals::inline hash_literals