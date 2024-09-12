#include "protocol/world/level/PackInstanceId.h"

namespace protocol {
PackInstanceId::PackInstanceId(PackInstanceId &&other)
    : mPackId(other.mPackId), mSubpackName(other.mSubpackName) {}

PackInstanceId::PackInstanceId(PackIdVersion const &packId,
                               std::string const &subpackName)
    : mPackId(packId), mSubpackName(subpackName){};

} // namespace protocol