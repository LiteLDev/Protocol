#pragma once

#include "protocol/Global.h"
#include "protocol/common/network/Packet.h"

namespace protocol {
class ServerToClientHandshakePacket : public Packet {
public:
  std::string mData;

  virtual ~ServerToClientHandshakePacket() = default;
  virtual MinecraftPacketIds getId() const;
  virtual std::string getName() const;
  virtual void write(class BinaryStream &stream) const;
  virtual StreamReadResult _read(class ReadOnlyBinaryStream &stream);

  ServerToClientHandshakePacket();
  explicit ServerToClientHandshakePacket(std::string const &webTokenData);
};

} // namespace protocol