#pragma once

#include "protocol/Global.h"
#include "protocol/common/network/Packet.h"
#include "protocol/common/resources/ResourcePackResponse.h"

namespace protocol {
class ResourcePackClientResponsePacket : public Packet {
public:
  std::set<std::string> mDownloadingPacks;
  ResourcePackResponse mResponse;

public:
  virtual ~ResourcePackClientResponsePacket() = default;
  virtual MinecraftPacketIds getId() const;
  virtual std::string getName() const;
  virtual void write(class BinaryStream &stream) const;
  virtual StreamReadResult _read(class ReadOnlyBinaryStream &stream);

  ResourcePackClientResponsePacket();
  ResourcePackClientResponsePacket(ResourcePackResponse response);

  std::set<std::string> const &getDownloadingPacks() const;
  bool isResponse(ResourcePackResponse haveThis) const;
};
} // namespace protocol