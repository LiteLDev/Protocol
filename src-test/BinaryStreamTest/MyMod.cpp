#include "MyMod.h"

#include <filesystem>
#include <memory>

#include "ll/api/mod/RegisterHelper.h"

#include "mc/deps/core/utility/BinaryStream.h"
#include "mc/deps/core/utility/ReadOnlyBinaryStream.h"
#include "protocol/deps/Utility/BinaryStream.h"

namespace my_mod {

static std::unique_ptr<MyMod> instance;

MyMod &MyMod::getInstance() { return *instance; }

bool MyMod::load() {
  getSelf().getLogger().debug("Loading...");
  // Code for loading the mod goes here.
  return true;
}

bool MyMod::enable() {
  auto &logger = getSelf().getLogger();
  {

    {
      BinaryStream(stream);
      stream.writeBool(false);
      stream.writeByte(10);
      stream.writeDouble(2.01);
      stream.writeFloat(3.01f);
      stream.writeSignedBigEndianInt(40);
      stream.writeSignedInt(50);
      stream.writeSignedInt64(-60);
      stream.writeSignedShort(70);
      stream.writeString("800");
      stream.writeUnsignedChar(90);
      stream.writeUnsignedInt(1000);
      stream.writeUnsignedInt64(11000);
      stream.writeUnsignedShort(12000);
      stream.writeUnsignedVarInt(13000000);
      stream.writeUnsignedVarInt64(1400000000);
      stream.writeVarInt(-1500000);
      stream.writeVarInt64(-16000000);

      logger.warn("Protocol BinaryStream Test..(Get)");
      auto newstream =
          protocol::ReadOnlyBinaryStream(stream.getAndReleaseData(), true);

      auto resultBool = newstream.getBool();
      logger.warn("Bool Result: {}", resultBool);
      auto resultByte = newstream.getByte();
      logger.warn("Byte Result: {}", resultByte);
      auto resultDouble = newstream.getDouble();
      logger.warn("Double Result: {}", resultDouble);
      auto resultFloat = newstream.getFloat();
      logger.warn("Float Result: {}", resultFloat);
      auto resultSignedBigEndianInt = newstream.getSignedBigEndianInt();
      logger.warn("SignedBigEndianInt Result: {}", resultSignedBigEndianInt);
      auto resultSignedInt = newstream.getSignedInt();
      logger.warn("SignedInt Result: {}", resultSignedInt);
      auto resultSignedInt64 = newstream.getSignedInt64();
      logger.warn("SignedInt64 Result: {}", resultSignedInt64);
      auto resultSignedShort = newstream.getSignedShort();
      logger.warn("SignedShort Result: {}", resultSignedShort);
      auto resultString = newstream.getString(100);
      logger.warn("String Result: {}", resultString);
      auto resultUnsignedChar = newstream.getUnsignedChar();
      logger.warn("UnsignedChar Result: {}", resultUnsignedChar);
      auto resultUnsignedInt = newstream.getUnsignedInt();
      logger.warn("UnsignedInt Result: {}", resultUnsignedInt);
      auto resultUnsignedInt64 = newstream.getUnsignedInt64();
      logger.warn("UnsignedInt64 Result: {}", resultUnsignedInt64);
      auto resultUnsignedShort = newstream.getUnsignedShort();
      logger.warn("UnsignedShort Result: {}", resultUnsignedShort);
      auto resultUnsignedVarInt = newstream.getUnsignedVarInt();
      logger.warn("UnsignedVarInt Result: {}", resultUnsignedVarInt);
      auto resultUnsignedVarInt64 = newstream.getUnsignedVarInt64();
      logger.warn("UnsignedVarInt64 Result: {}", resultUnsignedVarInt64);
      auto resultVarInt = newstream.getVarInt();
      logger.warn("VarInt Result: {}", resultVarInt);
      auto resultVarInt64 = newstream.getVarInt64();
      logger.warn("VarInt64 Result: {}", resultVarInt64);
    }
  }

  {
    logger.warn("Protocol BinaryStream Test.. (Write)");
    protocol::BinaryStream(stream);
    stream.writeBool(false);
    stream.writeByte(10);
    stream.writeDouble(2.01);
    stream.writeFloat(3.01f);
    stream.writeSignedBigEndianInt(40);
    stream.writeSignedInt(50);
    stream.writeSignedInt64(-60);
    stream.writeSignedShort(70);
    stream.writeString("800");
    stream.writeUnsignedChar(90);
    stream.writeUnsignedInt(1000);
    stream.writeUnsignedInt64(11000);
    stream.writeUnsignedShort(12000);
    stream.writeUnsignedVarInt(13000000);
    stream.writeUnsignedVarInt64(1400000000);
    stream.writeVarInt(-1500000);
    stream.writeVarInt64(-16000000);

    auto newstream = ReadOnlyBinaryStream(stream.getAndReleaseData(), true);
    auto resultBool = newstream.getBool();
    logger.warn("Bool Result: {}", resultBool.value());
    auto resultByte = newstream.getByte();
    logger.warn("Byte Result: {}", resultByte.value());
    auto resultDouble = newstream.getDouble();
    logger.warn("Double Result: {}", resultDouble.value());
    auto resultFloat = newstream.getFloat();
    logger.warn("Float Result: {}", resultFloat.value());
    auto resultSignedBigEndianInt = newstream.getSignedBigEndianInt();
    logger.warn("SignedBigEndianInt Result: {}",
                resultSignedBigEndianInt.value());
    auto resultSignedInt = newstream.getSignedInt();
    logger.warn("SignedInt Result: {}", resultSignedInt.value());
    auto resultSignedInt64 = newstream.getSignedInt64();
    logger.warn("SignedInt64 Result: {}", resultSignedInt64.value());
    auto resultSignedShort = newstream.getSignedShort();
    logger.warn("SignedShort Result: {}", resultSignedShort.value());
    auto resultString = newstream.getString(100);
    logger.warn("String Result: {}", resultString.value());
    auto resultUnsignedChar = newstream.getUnsignedChar();
    logger.warn("UnsignedChar Result: {}", resultUnsignedChar.value());
    auto resultUnsignedInt = newstream.getUnsignedInt();
    logger.warn("UnsignedInt Result: {}", resultUnsignedInt.value());
    auto resultUnsignedInt64 = newstream.getUnsignedInt64();
    logger.warn("UnsignedInt64 Result: {}", resultUnsignedInt64.value());
    auto resultUnsignedShort = newstream.getUnsignedShort();
    logger.warn("UnsignedShort Result: {}", resultUnsignedShort.value());
    auto resultUnsignedVarInt = newstream.getUnsignedVarInt();
    logger.warn("UnsignedVarInt Result: {}", resultUnsignedVarInt.value());
    auto resultUnsignedVarInt64 = newstream.getUnsignedVarInt64();
    logger.warn("UnsignedVarInt64 Result: {}", resultUnsignedVarInt64.value());
    auto resultVarInt = newstream.getVarInt();
    logger.warn("VarInt Result: {}", resultVarInt.value());
    auto resultVarInt64 = newstream.getVarInt64();
    logger.warn("VarInt64 Result: {}", resultVarInt64.value());
  }
  return true;
}

bool MyMod::disable() {
  getSelf().getLogger().debug("Disabling...");
  // Code for disabling the mod goes here.
  return true;
}

} // namespace my_mod

LL_REGISTER_MOD(my_mod::MyMod, my_mod::instance);

#include "ll/api/memory/Hook.h"
#include "mc/network/packet/LoginPacket.h"
#include "protocol/common/network/packet/LoginPacket.h"

LL_AUTO_TYPE_INSTANCE_HOOK(LoginPacketRead, HookPriority::Normal, LoginPacket,
                           "?_read@LoginPacket@@EEAA?AV?$Result@XVerror_code@"
                           "std@@@Bedrock@@AEAVReadOnlyBinaryStream@@@Z",
                           Bedrock::Result<void>,
                           ReadOnlyBinaryStream &stream) {

  auto &logger = my_mod::MyMod::getInstance().getSelf().getLogger();
  logger.warn("LoginPacketRead");
  protocol::ReadOnlyBinaryStream newreadstream(*stream.mBuffer, false);
  protocol::LoginPacket(pkt);
  pkt.read(newreadstream);

  protocol::BinaryStream(newstream);
  pkt.writeWithHeader((protocol::SubClientId)mClientSubId, newstream);

  auto out = newstream.getAndReleaseData();

  if (out == *stream.mBuffer) {
    logger.warn("LoginPacket Same");
  } else {
    logger.error("LoginPacket Not same {} {}", out.size(),
                 stream.mBuffer->size());
  }
  return origin(stream);
}