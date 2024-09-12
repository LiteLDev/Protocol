#include "protocol/world/ActorUniqueID.h"

namespace protocol {

ActorUniqueID::ActorUniqueID(int64 id) : id(id) {}

uint64 ActorUniqueID::getHash() const { return id; };

ActorUniqueID ActorUniqueID::fromUUID(mce::UUID const &uuid) {
  auto MostSignificantBits = uuid.getMostSignificantBits();
  auto id = uuid.getLeastSignificantBits() ^ MostSignificantBits;
  return ActorUniqueID(id);
};

ActorUniqueID const ActorUniqueID::INVALID_ID{};

} // namespace protocol