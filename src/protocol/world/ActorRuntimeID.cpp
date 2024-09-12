#include "protocol/world/ActorRuntimeID.h"

namespace protocol {
uint64 ActorRuntimeID::getHash() const { return id; }
} // namespace protocol