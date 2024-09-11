#include "protocol/common/network/packet/ResourcePacksInfoPacket.h"
#include <cstdint>

namespace protocol {
PackInfoData::PackInfoData(mce::UUID const &guid, SemVersion const &version,
                           uint64_t packSize, std::string const &contentKey,
                           std::string const &subpackName,
                           ContentIdentity const &contentIdentity,
                           bool hasScripts, bool isRayTracingCapable)
    : mPackIdVersion(PackIdVersion(guid, version, PackType::Invalid)),
      mPackSize(packSize), mContentKey(contentKey), mSubpackName(subpackName),
      mContentIdentity(contentIdentity), mHasScripts(hasScripts),
      mIsRayTracingCapable(isRayTracingCapable){};

uint64 PacksInfoData::getBehaviorPackSize() const {
  return mBehaviorPacks.size();
};

uint64 PacksInfoData::getResourcePackSize() const {
  return mResourcePacks.size();
};

ResourcePacksInfoPacket::ResourcePacksInfoPacket()
    : Packet(), mData(PacksInfoData()){};

ResourcePacksInfoPacket::ResourcePacksInfoPacket(
    bool texturePackRequired, std::vector<PackInfoData> &behaviorPacks,
    std::vector<PackInfoData> &resourcePacks, bool forceServerPacksEnabled,
    std::vector<std::pair<std::string, std::string>> &&cdnUrls, bool hasScripts)
    : Packet(), mData(PacksInfoData(texturePackRequired, hasScripts, false,
                                    forceServerPacksEnabled, behaviorPacks,
                                    resourcePacks)),
      mCDNUrls(std::move(cdnUrls)){};

ResourcePacksInfoPacket::~ResourcePacksInfoPacket() = default;

MinecraftPacketIds ResourcePacksInfoPacket::getId() const {
  return MinecraftPacketIds::ResourcePacksInfo;
};

std::string ResourcePacksInfoPacket::getName() const {
  return "ResourcePacksInfoPacket";
};

void ResourcePacksInfoPacket::write(BinaryStream &stream) const {
  stream.writeBool(mData.mResourcePackRequired);
  stream.writeBool(mData.mHasExceptions);
  stream.writeBool(mData.mHasScripts);
  stream.writeBool(mData.mForceServerPacksEnabled);

  stream.writeUnsignedShort(mData.getBehaviorPackSize());
  for (auto const &pack : mData.mBehaviorPacks) {
    stream.writeString(pack.mPackIdVersion.mId.asString());
    stream.writeString(pack.mPackIdVersion.mVersion.asString());
    stream.writeUnsignedInt64(pack.mPackSize);
    stream.writeString(pack.mContentKey);
    stream.writeString(pack.mSubpackName);
    stream.writeString(pack.mContentIdentity.asString());
    stream.writeBool(pack.mHasScripts);
  }

  stream.writeUnsignedShort(mData.getResourcePackSize());
  for (auto const &pack : mData.mResourcePacks) {
    stream.writeString(pack.mPackIdVersion.mId.asString());
    stream.writeString(pack.mPackIdVersion.mVersion.asString());
    stream.writeUnsignedInt64(pack.mPackSize);
    stream.writeString(pack.mContentKey);
    stream.writeString(pack.mSubpackName);
    stream.writeString(pack.mContentIdentity.asString());
    stream.writeBool(pack.mHasScripts);
    stream.writeBool(pack.mIsRayTracingCapable);
  }

  stream.writeUnsignedVarInt(mCDNUrls.size());
  for (auto const &url : mCDNUrls) {
    stream.writeString(url.first);
    stream.writeString(url.second);
  }
};

StreamReadResult ResourcePacksInfoPacket::_read(ReadOnlyBinaryStream &stream) {
  mData.mResourcePackRequired = stream.getBool();
  mData.mHasExceptions = stream.getBool();
  mData.mHasScripts = stream.getBool();
  mData.mForceServerPacksEnabled = stream.getBool();

  auto behaviorPackSize = stream.getUnsignedShort();
  for (uint64 i = 0; i < behaviorPackSize; i++) {
    auto id = mce::UUID::fromString(stream.getString());
    SemVersion(packVersion);
    SemVersion::fromString(stream.getString(), packVersion,
                           SemVersion::ParseOption::NoWildcards);
    auto packSize = stream.getUnsignedInt64();
    auto contentKey = stream.getString();
    auto subpackName = stream.getString();
    auto contentIdentity = ContentIdentity::fromString(stream.getString());
    auto hasScripts = stream.getBool();

    mData.mBehaviorPacks.push_back(
        PackInfoData(id, packVersion, packSize, contentKey, subpackName,
                     contentIdentity, hasScripts, false));
  }

  auto resourcePackSize = stream.getUnsignedShort();
  for (uint64 i = 0; i < resourcePackSize; i++) {
    auto id = mce::UUID::fromString(stream.getString());
    SemVersion(packVersion);
    SemVersion::fromString(stream.getString(), packVersion,
                           SemVersion::ParseOption::NoWildcards);
    auto packSize = stream.getUnsignedInt64();
    auto contentKey = stream.getString();
    auto subpackName = stream.getString();
    auto contentIdentity = ContentIdentity::fromString(stream.getString());
    auto hasScripts = stream.getBool();
    auto isRayTracingCapable = stream.getBool();

    mData.mResourcePacks.push_back(
        PackInfoData(id, packVersion, packSize, contentKey, subpackName,
                     contentIdentity, hasScripts, isRayTracingCapable));
  }

  auto cdnUrlsSize = stream.getUnsignedVarInt();
  for (uint64 i = 0; i < cdnUrlsSize; i++) {
    auto url = std::make_pair(stream.getString(), stream.getString());
    mCDNUrls.push_back(url);
  };

  return stream.getReadCompleteResult();
}

} // namespace protocol