#pragma once

#include "protocol/Global.h"
#include "protocol/common/network/ConnectionRequest.h"
#include "protocol/common/network/Packet.h"

namespace protocol {
class LoginPacket : public Packet {
public:
  int mClientNetworkVersion;
  std::unique_ptr<ConnectionRequest> mConnectionRequest;

  virtual ~LoginPacket() = default;
  virtual MinecraftPacketIds getId() const;
  virtual std::string getName() const;
  virtual void write(class BinaryStream &stream) const;
  virtual bool disallowBatching() const;
  virtual StreamReadResult _read(class ReadOnlyBinaryStream &stream);

  LoginPacket();
  LoginPacket(int clientNetworkVersion,
              ConnectionRequest const &connectionRequest);
};
} // namespace protocol