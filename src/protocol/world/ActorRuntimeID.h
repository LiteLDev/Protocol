#pragma once

#include "protocol/Global.h"
#include "protocol/deps/utility/UUID.h"

namespace protocol {
class ActorRuntimeID {
public:
  uint64 id;

  [[nodiscard]] constexpr ActorRuntimeID() : id(0) {}
  [[nodiscard]] constexpr ActorRuntimeID(uint64 x) : id(x) {}

  [[nodiscard]] constexpr operator uint64() const { return id; }

  [[nodiscard]] uint64 getHash() const;
};
} // namespace protocol

namespace std {
template <> class hash<protocol::ActorRuntimeID> {
public:
  size_t operator()(protocol::ActorRuntimeID const &id) const {
    return std::hash<int64>()(id.getHash());
  }
};
} // namespace std