#include "protocol/network/packet/DisconnectPacket.h"

namespace protocol {

DisconnectPacket::DisconnectPacket() : Packet() {}

DisconnectPacket::DisconnectPacket(Connection::DisconnectFailReason reason,
                                   std::string const &message, bool skipMessage)
    : Packet(), mSkipMessage(skipMessage), mMessage(message), mReason(reason){};

MinecraftPacketIds DisconnectPacket::getId() const {
  return MinecraftPacketIds::Disconnect;
};

std::string DisconnectPacket::getName() const { return "DisconnectPacket"; };

void DisconnectPacket::write(class BinaryStream &stream) const {
  stream.writeVarInt(magic_enum::enum_integer(mReason));
  stream.writeBool(mSkipMessage);
  if (mSkipMessage)
    stream.writeString(mMessage);
};

StreamReadResult DisconnectPacket::_read(class ReadOnlyBinaryStream &stream) {
  auto reason = magic_enum::enum_cast<Connection::DisconnectFailReason>(
      stream.getVarInt());
  if (!reason) {
    return StreamReadResult::Malformed;
  }
  mReason = reason.value();
  mSkipMessage = stream.getBool();
  if (mSkipMessage) {
    mMessage = stream.getString();
  }
  return stream.getReadCompleteResult();
};

} // namespace protocol