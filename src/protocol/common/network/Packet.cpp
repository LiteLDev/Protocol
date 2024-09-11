#include "protocol/common/network/Packet.h"

namespace protocol {

Packet::~Packet() = default;
bool Packet::checkSize(uint64 a1, bool a2) const {
  if (a1 >= 0xA00001 && a2) {
    return false;
  } else {
    return true;
  }
}

ExtendedStreamReadResult Packet::read(ReadOnlyBinaryStream &bitStream) {
  auto id = bitStream.getUnsignedVarInt();
  mClientSubId = (SubClientId)((id >> 12) & 0xF);
  
  auto retstr = _read(bitStream);
  if (retstr == StreamReadResult::Valid) {
    retstr = bitStream.getReadCompleteResult();
  }
  return ExtendedStreamReadResult(retstr);
}

bool Packet::disallowBatching() const { return false; }

bool Packet::isValid() const { return true; }

bool Packet::readNoHeader(ReadOnlyBinaryStream &stream,
                          SubClientId const &subClientId) {
  mClientSubId = subClientId;
  auto result = read(stream);
  return result.result != StreamReadResult::Malformed;
}

void Packet::writeWithHeader(SubClientId subClientId,
                             BinaryStream &bitstream) const {
  auto id = (int)getId();
  bitstream.writeUnsignedVarInt(id | ((int)subClientId << 10) |
                                ((int)mClientSubId << 12));
  return write(bitstream);
}
} // namespace protocol