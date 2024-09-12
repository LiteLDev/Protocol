#pragma once

#include "protocol/Global.h"
#include "protocol/network/Packet.h"

namespace protocol {
class ClientToServerHandshakePacket : public Packet {
public:
  virtual ~ClientToServerHandshakePacket() = default;
  virtual MinecraftPacketIds getId() const;
  virtual std::string getName() const;
  virtual void write(class BinaryStream &stream) const;
  virtual StreamReadResult _read(class ReadOnlyBinaryStream &stream);

  ClientToServerHandshakePacket();
};

} // namespace protocol