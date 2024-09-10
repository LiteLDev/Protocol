#pragma once

namespace protocol {
class IPacketHandlerDispatcher {
public:
  virtual ~IPacketHandlerDispatcher() = default;
};
} // namespace protocol