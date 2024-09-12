#pragma once

#include "protocol/Global.h"
#include "protocol/deps/utility/UUID.h"

namespace protocol {
struct ActorUniqueID {
public:
  int64 id{};

public:
  ActorUniqueID() = default;
  ActorUniqueID(int64 id);
  uint64 getHash() const;
  static struct ActorUniqueID fromUUID(class mce::UUID const &);
  static struct ActorUniqueID const INVALID_ID;
};
} // namespace protocol

namespace std {
template <> class hash<protocol::ActorUniqueID> {
public:
  size_t operator()(protocol::ActorUniqueID const &id) const {
    return id.getHash();
  }
};
} // namespace std