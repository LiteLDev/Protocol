#pragma once

#include "protocol/Global.h"
#include "protocol/common/network/Packet.h"

namespace protocol {
class SetTimePacket : public Packet {
public:
  int mTime; // this+0x30

public:
  virtual ~SetTimePacket() = default;
  virtual MinecraftPacketIds getId() const;
  virtual std::string getName() const;
  virtual void write(class BinaryStream &stream) const;
  virtual StreamReadResult _read(class ReadOnlyBinaryStream &stream);

  SetTimePacket();
  explicit SetTimePacket(int time);

};
} // namespace protocol