#include "protocol/network/packet/ResourcePackClientResponsePacket.h"

namespace protocol {

MinecraftPacketIds ResourcePackClientResponsePacket::getId() const {
  return MinecraftPacketIds::ResourcePackClientResponse;
};

std::string ResourcePackClientResponsePacket::getName() const {
  return "ResourcePackClientResponsePacket";
};

void ResourcePackClientResponsePacket::write(BinaryStream &stream) const {
  stream.writeByte(magic_enum::enum_integer(mResponse));
  stream.writeUnsignedShort(mDownloadingPacks.size());
  for (auto const &pack : mDownloadingPacks) {
    stream.writeString(pack);
  }
};

StreamReadResult
ResourcePackClientResponsePacket::_read(ReadOnlyBinaryStream &stream) {
  auto response = magic_enum::enum_cast<ResourcePackResponse>(stream.getByte());
  if (response) {
    mResponse = response.value();
  }
  auto size = stream.getUnsignedShort();
  for (uint64 i = 0; i < size; i++) {
    mDownloadingPacks.emplace(stream.getString());
  }
  return stream.getReadCompleteResult();
};

ResourcePackClientResponsePacket::ResourcePackClientResponsePacket()
    : Packet(), mDownloadingPacks(), mResponse(ResourcePackResponse::Cancel){};

ResourcePackClientResponsePacket::ResourcePackClientResponsePacket(
    ResourcePackResponse response)
    : Packet(), mDownloadingPacks(), mResponse(response){};

std::set<std::string> const &
ResourcePackClientResponsePacket::getDownloadingPacks() const {
  return mDownloadingPacks;
};

bool ResourcePackClientResponsePacket::isResponse(
    ResourcePackResponse haveThis) const {
  return mResponse == haveThis;
};

} // namespace protocol