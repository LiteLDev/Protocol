#pragma once

#include "protocol/Global.h"
#include "protocol/common/network/Packet.h"
#include "protocol/common/network/enums/TextPacketType.h"
#include "protocol/common/world/actor/player/ResolvedTextObject.h"

namespace protocol {
class TextPacket : public Packet {
public:
  TextPacketType mType;
  std::string mAuthor;
  std::string mMessage;
  std::string mFilteredMessage;
  bool mHasFilteredMessage;
  std::vector<std::string> mParams;
  bool mLocalize;
  std::string mXuid;
  std::string mPlatformId;

  [[nodiscard]] inline static TextPacket
  createRawMessage(std::string_view msg) {
    auto res = TextPacket{};
    res.mType = TextPacketType::Raw;
    res.mMessage.assign(msg);
    return res;
  }

public:
  virtual ~TextPacket() = default;
  virtual MinecraftPacketIds getId() const;
  virtual std::string getName() const;
  virtual void write(BinaryStream &stream) const;
  virtual StreamReadResult _read(ReadOnlyBinaryStream &stream);

  TextPacket();

  static TextPacket createAnnouncement(std::string const &author,
                                       std::string const &message,
                                       std::string const &xuid,
                                       std::string const &platformId);

  static TextPacket createChat(std::string const &, std::string const &,
                               std::optional<std::string>, std::string const &,
                               std::string const &);

  static TextPacket createJukeboxPopup(std::string const &message,
                                       std::vector<std::string> const &params);

  static TextPacket createRawJsonObjectMessage(std::string const &rawJson);

  static TextPacket createSystemMessage(std::string const &message);

  static TextPacket
  createTextObjectMessage(ResolvedTextObject const &resolvedTextObject,
                          std::string fromXuid, std::string fromPlatformId);

  static TextPacket
  createTextObjectWhisperMessage(ResolvedTextObject const &resolvedTextObject,
                                 std::string const &xuid,
                                 std::string const &platformId);

  static TextPacket
  createTextObjectWhisperMessage(std::string const &message,
                                 std::string const &xuid,
                                 std::string const &platformId);

  static TextPacket createTranslated(std::string const &message,
                                     std::vector<std::string> const &params);

  static TextPacket createTranslatedAnnouncement(std::string const &author,
                                                 std::string const &message,
                                                 std::string const &xuid,
                                                 std::string const &platformId);

  static TextPacket createWhisper(std::string const &author,
                                  std::string const &message,
                                  std::string const &xuid,
                                  std::string const &platformId);

  TextPacket(TextPacketType, std::string const &, std::string const &,
             std::optional<std::string>, std::vector<std::string> const &, bool,
             std::string const &, std::string const &);
};
} // namespace protocol