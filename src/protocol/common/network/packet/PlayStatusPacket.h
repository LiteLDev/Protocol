#pragma once

#include "protocol/Global.h"
#include "protocol/common/network/Packet.h"
#include "protocol/common/network/enums/PlayStatus.h"

namespace protocol {
class PlayStatusPacket : public Packet {
public:
  PlayStatus mStatus;

  virtual ~PlayStatusPacket() = default;
  virtual MinecraftPacketIds getId() const;
  virtual std::string getName() const;
  virtual void write(class BinaryStream &stream) const;
  virtual StreamReadResult _read(class ReadOnlyBinaryStream &stream);

  PlayStatusPacket();
  explicit PlayStatusPacket(PlayStatus status);
};

} // namespace protocol