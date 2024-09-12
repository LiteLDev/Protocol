#pragma once

#include "protocol/Global.h"
#include "protocol/deps/core/resource/ContentIdentity.h"
#include "protocol/deps/core/string/HashedString.h"
#include "protocol/math/Vec2.h"
#include "protocol/math/Vec3.h"
#include "protocol/network/Packet.h"
#include "protocol/network/enums/GameType.h"
#include "protocol/network/enums/ServerAuthMovementMode.h"
#include "protocol/world/ActorRuntimeID.h"
#include "protocol/world/ActorUniqueID.h"

namespace protocol {
struct ItemData {
public:
  HashedString mName;
  short mId;
  bool mIsComponentBased;

public:
  ~ItemData() = default;
};

// todo
class StartGamePacket : public Packet {
public:
  // LevelSettings mSettings;
  ActorUniqueID mEntityId;
  ActorRuntimeID mRuntimeId;
  GameType mEntityGameType;
  Vec3 mPos;
  Vec2 mRot;
  std::string mLevelId;
  std::string mLevelName;
  ContentIdentity mTemplateContentIdentity;
  mce::UUID mWorldTemplateId;
  bool mIsTrial;

  // SyncedPlayerMovementSettings
  ServerAuthMovementMode AuthorityMode;
  int mRewindHistorySize;
  bool ServerAuthBlockBreaking;

  uint64 mLevelCurrentTime;
  int mEnchantmentSeed;
  std::string mMultiplayerCorrelationId;
  std::vector<ItemData> mItemData;
  bool mEnableItemStackNetManager;
  std::string mServerVersion;
  // CompoundTag mPlayerPropertyData;
  uint64 mServerBlockTypeRegistryChecksum;
  bool mServerEnabledClientSideGeneration;
  bool mBlockNetworkIdsAreHashes;
  bool mHardcore;

  // std::vector<std::pair<std::string, CompoundTag>> mBlockProperties;

public:
  virtual ~StartGamePacket();
  virtual MinecraftPacketIds getId() const;
  virtual std::string getName() const;
  virtual void write(class BinaryStream &stream) const;
  virtual StreamReadResult _read(ReadOnlyBinaryStream &stream);

  StartGamePacket();

  // NOLINTEND
};
} // namespace protocol