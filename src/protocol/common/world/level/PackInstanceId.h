#pragma once

#include "protocol/Global.h"
#include "protocol/deps/core/resource/ResourceHelper.h"

namespace protocol {
struct PackInstanceId {
public:
  PackIdVersion mPackId;
  std::string mSubpackName;

public:
  PackInstanceId(PackInstanceId &&);
  PackInstanceId(PackIdVersion const &packId, std::string const &subpackName);

  ~PackInstanceId() = default;
};
} // namespace protocol