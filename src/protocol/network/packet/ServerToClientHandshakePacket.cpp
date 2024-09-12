#include "protocol/network/packet/ServerToClientHandshakePacket.h"

namespace protocol {
ServerToClientHandshakePacket::ServerToClientHandshakePacket()
    : Packet(), mData(){};

ServerToClientHandshakePacket::ServerToClientHandshakePacket(
    std::string const &webTokenData)
    : Packet(), mData(webTokenData){};

MinecraftPacketIds ServerToClientHandshakePacket::getId() const {
  return MinecraftPacketIds::ServerToClientHandshake;
};

std::string ServerToClientHandshakePacket::getName() const {
  return "ServerToClientHandshakePacket";
};

void ServerToClientHandshakePacket::write(class BinaryStream &stream) const {
  stream.writeString(mData);
};

StreamReadResult
ServerToClientHandshakePacket::_read(class ReadOnlyBinaryStream &stream) {
  mData = stream.getString();
  return stream.getReadCompleteResult();
};

} // namespace protocol