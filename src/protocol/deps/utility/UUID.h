#pragma once
#include "protocol/Global.h"
#include "protocol/deps/utility/HashUtils.h"
#include "protocol/deps/utility/RandomUtils.h"

namespace protocol {

namespace mce {

class UUID {
public:
  uint64 a, b;

  [[nodiscard]] constexpr UUID(uint64 a = 0, uint64 b = 0) : a(a), b(b) {}

  [[nodiscard]] inline UUID(std::string const &uuidStr)
      : UUID(fromString(uuidStr)) {} // NOLINT

  [[nodiscard]] inline UUID(std::string_view uuidStr)
      : UUID(fromString(std::string{uuidStr})) {} // NOLINT

  static mce::UUID random();

  [[nodiscard]] inline mce::UUID fromStringHash(std::string_view sv) {
    return {protocol::hash_utils::doHash(sv),
            protocol::hash_utils::doHash2(sv)};
  }

  [[nodiscard]] inline explicit operator bool() const { return !isEmpty(); }

  [[nodiscard]] inline explicit operator std::string() const {
    return asString();
  }

  [[nodiscard]] constexpr bool operator==(UUID const &other) const {
    return (a == other.a) && (b == other.b);
  }

  [[nodiscard]] constexpr std::strong_ordering
  operator<=>(UUID const &other) const {
    if (a != other.a) {
      return a <=> other.a;
    }
    return b <=> other.b;
  }

public:
  uint64 getMostSignificantBits() const;
  uint64 getLeastSignificantBits() const;
  std::string asString() const;
  bool isEmpty() const;
  bool operator<(class mce::UUID const &) const;
  static bool canParse(std::string const &in);
  static class mce::UUID fromString(std::string const &in);
  static class mce::UUID EMPTY;
  static uint64 STRING_LENGTH;

  // NOLINTEND
};

}; // namespace mce

} // namespace protocol

namespace std {
template <> struct hash<protocol::mce::UUID> {
  size_t operator()(protocol::mce::UUID const &id) const noexcept {
    return id.a ^ (522133279 * id.b);
  }
};
} // namespace std