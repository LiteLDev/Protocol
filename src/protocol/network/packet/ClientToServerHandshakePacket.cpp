#include "protocol/network/packet/ClientToServerHandshakePacket.h"

namespace protocol {
ClientToServerHandshakePacket::ClientToServerHandshakePacket() : Packet(){};

MinecraftPacketIds ClientToServerHandshakePacket::getId() const {
  return MinecraftPacketIds::ClientToServerHandshake;
};

std::string ClientToServerHandshakePacket::getName() const {
  return "ClientToServerHandshakePacket";
};

void ClientToServerHandshakePacket::write(class BinaryStream &) const { ; };

StreamReadResult
ClientToServerHandshakePacket::_read(ReadOnlyBinaryStream &stream) {
  return stream.getReadCompleteResult();
};

} // namespace protocol