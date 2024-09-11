#pragma once

#include "protocol/Global.h"
#include "protocol/common/network/Packet.h"
#include "protocol/common/resources/BaseGameVersion.h"
#include "protocol/common/world/level/PackInstanceId.h"
#include "protocol/common/world/level/storage/Experiments.h"

namespace protocol {

class ResourcePackStackPacket : public Packet {
public:
  std::vector<PackInstanceId> mAddOnIdsAndVersions;
  std::vector<PackInstanceId> mTexturePackIdsAndVersions;
  BaseGameVersion mBaseGameVersion;
  bool mTexturePackRequired;
  Experiments mExperiments;
  bool mHasEditorPacks;

public:
  virtual ~ResourcePackStackPacket() = default;
  virtual MinecraftPacketIds getId() const;
  virtual std::string getName() const;
  virtual void write(BinaryStream &stream) const;
  virtual StreamReadResult _read(ReadOnlyBinaryStream &stream);

  ResourcePackStackPacket();
  ResourcePackStackPacket(std::vector<struct PackInstanceId>,
                          std::vector<struct PackInstanceId>,
                          BaseGameVersion const &, bool, Experiments const &,
                          bool);
};
} // namespace protocol