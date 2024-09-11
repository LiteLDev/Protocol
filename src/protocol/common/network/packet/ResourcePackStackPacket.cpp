#include "protocol/common/network/packet/ResourcePackStackPacket.h"

namespace protocol {

MinecraftPacketIds ResourcePackStackPacket::getId() const {
  return MinecraftPacketIds::ResourcePackStack;
};

std::string ResourcePackStackPacket::getName() const {
  return "ResourcePackStackPacket";
};

void ResourcePackStackPacket::write(BinaryStream &stream) const {
  stream.writeBool(mTexturePackRequired);

  stream.writeUnsignedVarInt(mAddOnIdsAndVersions.size());
  for (auto const &idAndVersion : mAddOnIdsAndVersions) {
    stream.writeString(idAndVersion.mPackId.mId.asString());
    stream.writeString(idAndVersion.mPackId.mVersion.asString());
    stream.writeString(idAndVersion.mSubpackName);
  }
  stream.writeUnsignedVarInt(mTexturePackIdsAndVersions.size());
  for (auto const &idAndVersion : mTexturePackIdsAndVersions) {
    stream.writeString(idAndVersion.mPackId.mId.asString());
    stream.writeString(idAndVersion.mPackId.mVersion.asString());
    stream.writeString(idAndVersion.mSubpackName);
  };
  stream.writeString(mBaseGameVersion.asString());

  stream.writeUnsignedInt(mExperiments.mExperimentData.size());
  for (auto const &exp : mExperiments.mExperimentData) {
    stream.writeString(exp.Name);
    stream.writeBool(exp.Enabled);
  }
  stream.writeBool(mExperiments.mExperimentsEverToggled);

  stream.writeBool(mHasEditorPacks);
}

StreamReadResult ResourcePackStackPacket::_read(ReadOnlyBinaryStream &stream) {
  mTexturePackRequired = stream.getBool();

  auto addOnCount = stream.getUnsignedVarInt();
  for (uint64 i = 0; i < addOnCount; i++) {
    auto id = mce::UUID::fromString(stream.getString());
    SemVersion(version);
    SemVersion::fromString(stream.getString(), version,
                           SemVersion::ParseOption::NoWildcards);
    auto subpackName = stream.getString();
    mAddOnIdsAndVersions.push_back(PackInstanceId(
        PackIdVersion(id, version, PackType::Invalid), subpackName));
  }

  auto texturePackCount = stream.getUnsignedVarInt();
  for (uint64 i = 0; i < texturePackCount; i++) {
    auto id = mce::UUID::fromString(stream.getString());
    SemVersion(version);
    SemVersion::fromString(stream.getString(), version,
                           SemVersion::ParseOption::NoWildcards);
    auto subpackName = stream.getString();
    mTexturePackIdsAndVersions.push_back(PackInstanceId(
        PackIdVersion(id, version, PackType::Invalid), subpackName));
  }

  BaseGameVersion::fromString(stream.getString(), mBaseGameVersion);

  auto num = stream.getUnsignedInt();
  for (uint64 i = 0; i < num; i++) {
    auto name = stream.getString();
    auto enable = stream.getBool();
    mExperiments.mExperimentData.push_back({name, enable});
  }

  mExperiments.mExperimentsEverToggled = stream.getBool();
  mHasEditorPacks = stream.getBool();
  return stream.getReadCompleteResult();
};

ResourcePackStackPacket::ResourcePackStackPacket()
    : Packet(), mTexturePackRequired(false), mHasEditorPacks(false){};

ResourcePackStackPacket::ResourcePackStackPacket(
    std::vector<PackInstanceId> a1, std::vector<PackInstanceId> a2,
    BaseGameVersion const &baseGameVersion, bool texturePackRequireda,
    Experiments const &experiments, bool isExperimentalGameplaya)
    : mAddOnIdsAndVersions(std::move(a1)),
      mTexturePackIdsAndVersions(std::move(a2)),
      mBaseGameVersion(baseGameVersion),
      mTexturePackRequired(texturePackRequireda), mExperiments(experiments),
      mHasEditorPacks(isExperimentalGameplaya) {}
} // namespace protocol