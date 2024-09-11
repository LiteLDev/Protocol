#include "protocol/deps/core/resource/ContentIdentity.h"
#include <utility>

namespace protocol {

ContentIdentity::ContentIdentity() : uuid(mce::UUID()), valid(false){};

ContentIdentity::ContentIdentity(ContentIdentity &&other) {
  uuid = std::move(other.uuid);
  valid = other.valid;
};

ContentIdentity::ContentIdentity(ContentIdentity const &other) {
  uuid = other.uuid;
  valid = other.valid;
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
  if (this != &rhs) {
    uuid = std::move(rhs.uuid);
    valid = rhs.valid;
  }
  return *this;
};

ContentIdentity &ContentIdentity::operator=(ContentIdentity const &rhs) {
  if (this != &rhs) {
    uuid = rhs.uuid;
    valid = rhs.valid;
  }
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