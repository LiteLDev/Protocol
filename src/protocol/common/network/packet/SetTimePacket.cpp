#include "protocol/common/network/packet/SetTimePacket.h"

namespace protocol {

MinecraftPacketIds SetTimePacket::getId() const {
  return MinecraftPacketIds::SetTime;
};

std::string SetTimePacket::getName() const { return "SetTimePacket"; };

void SetTimePacket::write(class BinaryStream &stream) const {
  stream.writeVarInt(mTime);
};

StreamReadResult SetTimePacket::_read(class ReadOnlyBinaryStream &stream) {
  mTime = stream.getVarInt();
  return stream.getReadCompleteResult();
};

SetTimePacket::SetTimePacket() : Packet(), mTime(0){};

SetTimePacket::SetTimePacket(int time) : Packet(), mTime(time){};
} // namespace protocol