#include "protocol/deps/utility/UUID.h"
#include <regex>

namespace protocol {

mce::UUID mce::UUID::random() {
  return {ll::random_utils::rand<uint64>(), ll::random_utils::rand<uint64>()};
}

uint64 mce::UUID::getMostSignificantBits() const { return a; }
uint64 mce::UUID::getLeastSignificantBits() const { return b; }

std::string mce::UUID::asString() const {
  std::ostringstream oss;
  oss << std::hex << std::setfill('0') << std::setw(8)
      << (getMostSignificantBits() >> 32) << '-' << std::setw(4)
      << ((getMostSignificantBits() >> 16) & 0xFFFF) << '-' << std::setw(4)
      << (getMostSignificantBits() & 0xFFFF) << '-' << std::setw(4)
      << ((getLeastSignificantBits() >> 48) & 0xFFFF) << '-' << std::setw(12)
      << (getLeastSignificantBits() & 0xFFFFFFFFFFFF);
  return oss.str();
};

bool mce::UUID::isEmpty() const { return *this == EMPTY; };

bool mce::UUID::operator<(class mce::UUID const &) const {
  return std::tie(a, b) < std::tie(a, b);
};

bool mce::UUID::canParse(std::string const &in) {
  std::regex UUIDRegex("[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-"
                       "fA-F0-9]{4}-[a-fA-F0-9]{12}");
  std::smatch match;
  return std::regex_match(in, match, UUIDRegex);
};

class mce::UUID mce::UUID::fromString(std::string const &in) {
  std::regex UUIDRegex("[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-"
                       "fA-F0-9]{4}-[a-fA-F0-9]{12}");
  std::smatch match;
  if (!std::regex_match(in, match, UUIDRegex)) {
    return UUID();
  }

  uint64_t mostSignificantBits = 0;
  uint64_t leastSignificantBits = 0;
  int count = 0;

  for (char c : in) {
    if (c == '-')
      continue;

    int value;
    if (c >= '0' && c <= '9') {
      value = c - '0';
    } else if (c >= 'a' && c <= 'f') {
      value = c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
      value = c - 'A' + 10;
    } else {
      throw std::invalid_argument("Invalid character in UUID string");
    }

    if (count < 16) {
      mostSignificantBits = (mostSignificantBits << 4) | value;
    } else {
      leastSignificantBits = (leastSignificantBits << 4) | value;
    }
    ++count;
  }
  return UUID(mostSignificantBits, leastSignificantBits);
};

class mce::UUID mce::UUID::EMPTY = {};

uint64 mce::UUID::STRING_LENGTH = 36;

} // namespace protocol