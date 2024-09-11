#pragma once

#include "protocol/Global.h"
#include "protocol/common/network/Packet.h"
#include "protocol/common/network/enums/connection/DisconnectFailReason.h"

namespace protocol {
class DisconnectPacket : public Packet {
public:
  bool mSkipMessage;
  std::string mMessage;
  Connection::DisconnectFailReason mReason;

public:
  virtual ~DisconnectPacket() = default;
  virtual MinecraftPacketIds getId() const;
  virtual std::string getName() const;
  virtual void write(class BinaryStream &stream) const;
  virtual StreamReadResult _read(class ReadOnlyBinaryStream &stream);

  DisconnectPacket();
  DisconnectPacket(Connection::DisconnectFailReason, std::string const &, bool);
};
} // namespace protocol