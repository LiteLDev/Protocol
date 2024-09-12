#include "protocol/network/packet/PlayStatusPacket.h"

namespace protocol {
PlayStatusPacket::PlayStatusPacket() : Packet(){};

PlayStatusPacket::PlayStatusPacket(PlayStatus status)
    : Packet(), mStatus(status){};

MinecraftPacketIds PlayStatusPacket::getId() const {
  return MinecraftPacketIds::PlayStatus;
};

std::string PlayStatusPacket::getName() const { return "PlayStatusPacket"; };

void PlayStatusPacket::write(class BinaryStream &stream) const {
  stream.writeSignedBigEndianInt(magic_enum::enum_integer<PlayStatus>(mStatus));
};

StreamReadResult PlayStatusPacket::_read(class ReadOnlyBinaryStream &stream) {
  auto status =
      magic_enum::enum_cast<PlayStatus>(stream.getSignedBigEndianInt());
  if (status) {
    mStatus = status.value();
  }
  return stream.getReadCompleteResult();
};

} // namespace protocol