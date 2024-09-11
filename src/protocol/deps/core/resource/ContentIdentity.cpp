#include "protocol/deps/core/resource/ContentIdentity.h"
#include <utility>

namespace protocol {

ContentIdentity::ContentIdentity() : uuid(mce::UUID()), valid(false){};

ContentIdentity::ContentIdentity(ContentIdentity &&other) {
  *this = std::move(other);
};

ContentIdentity::ContentIdentity(ContentIdentity const &other) {
  *this = other;
};

ContentIdentity::ContentIdentity(mce::UUID const &uuid)
    : uuid(uuid), valid(false) {
  mce::UUID(rhs);
  valid = !uuid == rhs;
};

std::string ContentIdentity::asString() const { return uuid.asString(); };

mce::UUID const &ContentIdentity::getAsUUID() const { return uuid; };

bool ContentIdentity::isValid() const { return valid; };

bool ContentIdentity::operator!=(ContentIdentity const &rhs) const {
  return !(*this == rhs);
};

ContentIdentity &ContentIdentity::operator=(ContentIdentity &&rhs) {
  *this = std::move(rhs);
  return *this;
};

ContentIdentity &ContentIdentity::operator=(ContentIdentity const &rhs) {
  *this = rhs;
  return *this;
};

bool ContentIdentity::operator==(ContentIdentity const &rhs) const {
  return uuid == rhs.uuid;
};

ContentIdentity ContentIdentity::fromString(std::string const &uuidString) {
  auto uuid = mce::UUID::fromString(uuidString);
  return ContentIdentity(uuid);
};

ContentIdentity ContentIdentity::EMPTY = {};

} // namespace protocol