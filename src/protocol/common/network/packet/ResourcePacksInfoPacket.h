#pragma once

#include "protocol/Global.h"
#include "protocol/common/network/Packet.h"
#include "protocol/deps/core/resource/ContentIdentity.h"
#include "protocol/deps/core/resource/ResourceHelper.h"

namespace protocol {

struct PackInfoData {
public:
  PackInfoData() = delete;

  PackIdVersion mPackIdVersion;
  uint64 mPackSize;
  std::string mContentKey;
  std::string mSubpackName;
  ContentIdentity mContentIdentity;
  bool mHasScripts;
  bool mIsRayTracingCapable;
  bool mHasExceptions;

public:
  PackInfoData(mce::UUID const &guid, SemVersion const &version,
               uint64_t packSize, std::string const &contentKey,
               std::string const &subpackName,
               ContentIdentity const &contentIdentity, bool hasScripts,
               bool isRayTracingCapable);

  ~PackInfoData() = default;
};

struct PacksInfoData {
public:
  bool mResourcePackRequired;
  bool mHasScripts;
  bool mHasExceptions;
  bool mForceServerPacksEnabled;
  std::vector<PackInfoData> mBehaviorPacks;
  std::vector<PackInfoData> mResourcePacks;

public:
  uint64 getBehaviorPackSize() const;
  uint64 getResourcePackSize() const;
};

class ResourcePacksInfoPacket : public Packet {
public:
  PacksInfoData mData;
  std::vector<std::pair<std::string, std::string>> mCDNUrls;

public:
  virtual ~ResourcePacksInfoPacket();
  virtual MinecraftPacketIds getId() const;
  virtual std::string getName() const;
  virtual void write(BinaryStream &stream) const;
  virtual StreamReadResult _read(ReadOnlyBinaryStream &stream);

  ResourcePacksInfoPacket();
  ResourcePacksInfoPacket(bool, std::vector<PackInfoData> &,
                          std::vector<PackInfoData> &, bool,
                          std::vector<std::pair<std::string, std::string>> &&,
                          bool);
};
} // namespace protocol