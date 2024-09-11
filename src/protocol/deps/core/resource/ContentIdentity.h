#pragma once
#include "protocol/Global.h"
#include "protocol/deps/utility/UUID.h"

namespace protocol {
class ContentIdentity {
public:
  mce::UUID uuid;
  bool valid;

  ContentIdentity();
  ContentIdentity(ContentIdentity &&);
  ContentIdentity(ContentIdentity const &);
  explicit ContentIdentity(mce::UUID const &uuid);

  std::string asString() const;
  mce::UUID const &getAsUUID() const;
  bool isValid() const;
  bool operator!=(ContentIdentity const &rhs) const;
  ContentIdentity &operator=(ContentIdentity &&rhs);
  ContentIdentity &operator=(ContentIdentity const &rhs);
  bool operator==(ContentIdentity const &rhs) const;
  static ContentIdentity fromString(std::string const &uuidString);
  static ContentIdentity EMPTY;

};
} // namespace protocol