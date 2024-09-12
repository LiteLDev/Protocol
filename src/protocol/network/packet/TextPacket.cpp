#include "protocol/network/packet/TextPacket.h"

namespace protocol {
MinecraftPacketIds TextPacket::getId() const {
  return MinecraftPacketIds::Text;
};

std::string TextPacket::getName() const { return "TextPacket"; };

void TextPacket::write(BinaryStream &stream) const {
  stream.writeByte(magic_enum::enum_integer(mType));
  stream.writeBool(mLocalize);
  switch (mType) {
  case TextPacketType::Chat:
  case TextPacketType::Whisper:
  case TextPacketType::Announcement:
    stream.writeString(mAuthor);
    stream.writeString(mMessage);
    break;
  case TextPacketType::Raw:
  case TextPacketType::Tip:
  case TextPacketType::SystemMessage:
  case TextPacketType::TextObject:
  case TextPacketType::TextObjectAnnouncement:
  case TextPacketType::TextObjectWhisper:
    stream.writeString(mMessage);
    break;
  case TextPacketType::Translate:
  case TextPacketType::Popup:
  case TextPacketType::JukeboxPopup:
    stream.writeString(mMessage);
    stream.writeUnsignedVarInt(mParams.size());
    for (auto const &param : mParams) {
      stream.writeString(param);
    }
    break;
  default:
    break;
  }
  stream.writeString(mXuid);
  stream.writeString(mPlatformId);
  stream.writeString(mFilteredMessage);
};

StreamReadResult TextPacket::_read(ReadOnlyBinaryStream &stream) {
  auto type = magic_enum::enum_cast<TextPacketType>(stream.getByte());
  if (!type) {
    return stream.getReadCompleteResult();
  }
  mLocalize = stream.getBool();
  mType = type.value();
  switch (mType) {
  case TextPacketType::Chat:
  case TextPacketType::Whisper:
  case TextPacketType::Announcement:
    mAuthor = stream.getString();
    mMessage = stream.getString();
    break;
  case TextPacketType::Raw:
  case TextPacketType::Tip:
  case TextPacketType::SystemMessage:
  case TextPacketType::TextObject:
  case TextPacketType::TextObjectAnnouncement:
  case TextPacketType::TextObjectWhisper:
    mMessage = stream.getString();
    break;
  case TextPacketType::Translate:
  case TextPacketType::Popup:
  case TextPacketType::JukeboxPopup:
    mMessage = stream.getString();
    for (uint64 i = 0; i < stream.getUnsignedVarInt(); i++) {
      mParams.push_back(stream.getString());
    }
    break;
  default:
    break;
  }
  mXuid = stream.getString();
  mPlatformId = stream.getString();
  mFilteredMessage = stream.getString();
  return stream.getReadCompleteResult();
};

TextPacket::TextPacket() : Packet(), mType(TextPacketType::Raw){};

TextPacket TextPacket::createAnnouncement(std::string const &author,
                                          std::string const &message,
                                          std::string const &xuid,
                                          std::string const &platformId) {
  return TextPacket(TextPacketType::Announcement, author, message, {}, {},
                    false, xuid, platformId);
};

TextPacket TextPacket::createChat(std::string const &author,
                                  std::string const &message,
                                  std::optional<std::string> filteredMessage,
                                  std::string const &xuid,
                                  std::string const &platformId) {
  return TextPacket(TextPacketType::Chat, author, message, filteredMessage, {},
                    false, xuid, platformId);
};

TextPacket
TextPacket::createJukeboxPopup(std::string const &message,
                               std::vector<std::string> const &params) {
  return TextPacket(TextPacketType::JukeboxPopup, "", message, {}, params, true,
                    "", "");
};

TextPacket TextPacket::createRawJsonObjectMessage(std::string const &rawJson) {
  return TextPacket(TextPacketType::TextObject, "", rawJson, {}, {}, true, "",
                    "");
};

TextPacket TextPacket::createSystemMessage(std::string const &message) {
  return TextPacket(TextPacketType::SystemMessage, "", message, {}, {}, false,
                    "", "");
};

TextPacket TextPacket::createTextObjectMessage(
    ResolvedTextObject const &resolvedTextObject, std::string fromXuid,
    std::string fromPlatformId) {
  auto AsJsonString = resolvedTextObject.getAsJsonString();
  return TextPacket(TextPacketType::TextObject, "", AsJsonString, {}, {}, false,
                    fromXuid, fromPlatformId);
};

TextPacket TextPacket::createTextObjectWhisperMessage(
    ResolvedTextObject const &resolvedTextObject, std::string const &xuid,
    std::string const &platformId) {
  auto AsJsonString = resolvedTextObject.getAsJsonString();
  return TextPacket(TextPacketType::TextObjectWhisper, "", AsJsonString, {}, {},
                    false, xuid, platformId);
};

TextPacket
TextPacket::createTextObjectWhisperMessage(std::string const &message,
                                           std::string const &xuid,
                                           std::string const &platformId) {
  return TextPacket(TextPacketType::TextObjectWhisper, "", message, {}, {},
                    false, xuid, platformId);
};

TextPacket
TextPacket::createTranslated(std::string const &message,
                             std::vector<std::string> const &params) {
  return TextPacket(TextPacketType::Translate, "", message, {}, params, true,
                    "", "");
};

TextPacket createTranslatedAnnouncement(std::string const &author,
                                        std::string const &message,
                                        std::string const &xuid,
                                        std::string const &platformId) {
  return TextPacket(TextPacketType::Announcement, author, message, {}, {}, true,
                    xuid, platformId);
};

TextPacket TextPacket::createWhisper(std::string const &author,
                                     std::string const &message,
                                     std::string const &xuid,
                                     std::string const &platformId) {
  return TextPacket(TextPacketType::Whisper, author, message, {}, {}, false,
                    xuid, platformId);
};

TextPacket::TextPacket(TextPacketType type, std::string const &author,
                       std::string const &message,
                       std::optional<std::string> filteredMessage,
                       std::vector<std::string> const &params, bool localize,
                       std::string const &xuid, std::string const &platformId)
    : Packet(), mType(type), mAuthor(author), mMessage(message),
      mParams(params), mLocalize(localize), mXuid(xuid),
      mPlatformId(platformId) {
  mHasFilteredMessage = false;
  if (filteredMessage) {
    mHasFilteredMessage = true;
    mFilteredMessage = *filteredMessage;
  }
};
} // namespace protocol