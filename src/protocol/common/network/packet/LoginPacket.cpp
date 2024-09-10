#include "protocol/common/network/packet/LoginPacket.h"
#include "protocol/common/SharedConstants.h"
namespace protocol {
LoginPacket::LoginPacket()
    : Packet(), mClientNetworkVersion(0), mConnectionRequest() {}

LoginPacket::LoginPacket(int clientNetworkVersion,
                         ConnectionRequest const &connectionRequest)
    : mClientNetworkVersion(clientNetworkVersion) {
  mConnectionRequest = std::make_unique<ConnectionRequest>(connectionRequest);
}

MinecraftPacketIds LoginPacket::getId() const {
  return MinecraftPacketIds::Login;
}

std::string LoginPacket::getName() const { return "LoginPacket"; }

void LoginPacket::write(BinaryStream &stream) const {
  stream.writeSignedBigEndianInt(mClientNetworkVersion);
  auto data = mConnectionRequest->toString();
  stream.writeString(data);
};

bool LoginPacket::disallowBatching() const { return true; };

StreamReadResult LoginPacket::_read(ReadOnlyBinaryStream &stream) {
  mClientNetworkVersion = stream.getSignedBigEndianInt();
  if (SharedConstants::NetworkProtocolVersion == mClientNetworkVersion) {
    auto connectionRequestString = stream.getString();
    auto Certificate = ConnectionRequest::fromString(connectionRequestString);
    mConnectionRequest = std::make_unique<ConnectionRequest>(Certificate);
  } else {
    auto Length = stream.getLength();
    stream.setReadPointer(Length);
  }
  return stream.getReadCompleteResult();
};

} // namespace protocol