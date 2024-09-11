#include "protocol/deps/Utility/BinaryStream.h"
#include <cstdint>

namespace protocol {
ReadOnlyBinaryStream::ReadOnlyBinaryStream()
    : mBuffer(std::addressof(mOwnedBuffer)) {}

ReadOnlyBinaryStream::ReadOnlyBinaryStream(std::string &&buffer)
    : mOwnedBuffer(std::move(buffer)), mBuffer(std::addressof(mOwnedBuffer)) {}

ReadOnlyBinaryStream::ReadOnlyBinaryStream(std::string const &buffer,
                                           bool copyBuffer) {
  if (copyBuffer) {
    mOwnedBuffer = buffer;
    mBuffer = std::addressof(mOwnedBuffer);
  } else {
    mBuffer = std::addressof(buffer);
  }
}

ReadOnlyBinaryStream::~ReadOnlyBinaryStream() = default;

bool ReadOnlyBinaryStream::read(void *target, uint64 num) {
  if (mHasOverflowed) {
    return false;
  }
  uint64 newReadPointer = num + mReadPointer;
  if (newReadPointer < mReadPointer || newReadPointer > mBuffer->length()) {
    mHasOverflowed = true;
    return false;
  }
  if (mBuffer->length() < mReadPointer) {
    return false;
  }
  const char *source = mBuffer->data() + mReadPointer;
  if (num == 1) {
    *static_cast<char *>(target) = *source;
  } else {
    std::memcpy(target, source, num);
  }
  mReadPointer = newReadPointer;
  return true;
}

bool ReadOnlyBinaryStream::canReadBool() const {
  return mReadPointer != -1LL && mReadPointer < mBuffer->length();
};

// todo
void ReadOnlyBinaryStream::ensureReadCompleted() const {
  if (mHasOverflowed) {
    return;
  }

  return;
};

bool ReadOnlyBinaryStream::getBool() {
  auto byte = getByte();
  return byte != 0;
};

uint8 ReadOnlyBinaryStream::getByte() {
  uint8 value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
}

double ReadOnlyBinaryStream::getDouble() {
  double value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

float ReadOnlyBinaryStream::getFloat() {
  float value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

int32 ReadOnlyBinaryStream::getSignedBigEndianInt() {
  int32 value = 0;
  if (read<>(&value)) {
    return _byteswap_ulong(value);
  }
  return _byteswap_ulong(value);
}

int32 ReadOnlyBinaryStream::getSignedInt() {
  int32 value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

int64 ReadOnlyBinaryStream::getSignedInt64() {
  int64 value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

int16 ReadOnlyBinaryStream::getSignedShort() {
  int16 value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

std::string ReadOnlyBinaryStream::getString(uint64 maxLength) {
  std::string outString;
  getString(outString, maxLength);
  return outString;
};

void ReadOnlyBinaryStream::getString(std::string &outString, uint64 maxLength) {
  auto length = getUnsignedVarInt();
  if (length > maxLength && maxLength != 0) {
    return;
  }
  if (length > 0) {
    outString = mBuffer->substr(mReadPointer, length);
    mReadPointer += length;
  }
  return;
};

uint8 ReadOnlyBinaryStream::getUnsignedChar() {
  uint8 value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

uint32 ReadOnlyBinaryStream::getUnsignedInt() {
  uint32 value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

uint64 ReadOnlyBinaryStream::getUnsignedInt64() {
  uint64 value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

uint16 ReadOnlyBinaryStream::getUnsignedShort() {
  uint16 value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

uint32 ReadOnlyBinaryStream::getUnsignedVarInt() {
  int32 value = 0;
  int32 shift = 0;
  uint8 b;
  while (((b = getByte()) & 0x80) == 0x80) {
    value |= (long)(b & 0x7F) << (shift++ * 7);
  }
  return value | ((long)(b & 0x7F) << (shift * 7));
};

uint64 ReadOnlyBinaryStream::getUnsignedVarInt64() {
  int64 value = 0;
  int32 shift = 0;
  uint8 b;
  while (((b = getByte()) & 0x80) == 0x80) {
    value |= (long)(b & 0x7F) << (shift++ * 7);
  }
  return value | ((long)(b & 0x7F) << (shift * 7));
};

int32 ReadOnlyBinaryStream::getVarInt() {
  uint32 decoded_value;

  decoded_value = getUnsignedVarInt();
  if ((decoded_value & 1) != 0)
    return ~(decoded_value >> 1);
  else
    return decoded_value >> 1;
};

int64 ReadOnlyBinaryStream::getVarInt64() {
  uint64 decoded_value;

  decoded_value = getUnsignedVarInt64();
  if ((decoded_value & 1) != 0)
    return ~(decoded_value >> 1);
  else
    return decoded_value >> 1;
};

bool ReadOnlyBinaryStream::hasOverflowed() const { return mHasOverflowed; };

StreamReadResult ReadOnlyBinaryStream::getReadCompleteResult() {
  StreamReadResult result = StreamReadResult::Malformed;
  if (!mHasOverflowed)
    return (StreamReadResult)(mBuffer->length() == mReadPointer);
  return result;
};

size_t ReadOnlyBinaryStream::getLength() const { return mBuffer->length(); }

void ReadOnlyBinaryStream::setReadPointer(size_t pos) {
  if (pos <= mBuffer->length())
    mReadPointer = pos;
  else
    mReadPointer = mBuffer->length();
}

////////////////BinaryStream////////////////
BinaryStream::BinaryStream() : mBuffer(std::addressof(mOwnedBuffer)) {
  ReadOnlyBinaryStream::mBuffer = mBuffer;
}

BinaryStream::BinaryStream(std::string &buffer, bool copyBuffer) {
  if (copyBuffer) {
    mOwnedBuffer = buffer;
    mBuffer = std::addressof(mOwnedBuffer);
  } else {
    mBuffer = std::addressof(buffer);
  }
  ReadOnlyBinaryStream::mBuffer = mBuffer;
}

BinaryStream::~BinaryStream() = default;

void BinaryStream::reset() {
  mBuffer = std::addressof(mOwnedBuffer);
  mReadPointer = 0LL;
};

void BinaryStream::writeBool(bool data) { writeByte(data); };

void BinaryStream::writeByte(uint8 data) { write<uint8>(data); };

void BinaryStream::writeDouble(double data) { write<double>(data); };

void BinaryStream::writeFloat(float data) { write<float>(data); };

void BinaryStream::writeSignedBigEndianInt(int32 data) {
  auto value = _byteswap_ulong(data);
  write<int32>(value);
};

void BinaryStream::writeSignedInt(int32 data) { write<int32>(data); };

void BinaryStream::writeSignedInt64(int64 data) { write<int64>(data); };

void BinaryStream::writeSignedShort(int16 data) { write<int16>(data); };

void BinaryStream::writeString(std::string_view data) {
  writeUnsignedVarInt((uint32)data.size());
  mBuffer->append(data);
};

void BinaryStream::writeUnsignedChar(uint8 data) { write<uint8>(data); };

void BinaryStream::writeUnsignedInt(uint32 data) { write<uint32>(data); };

void BinaryStream::writeUnsignedInt64(uint64 data) { write<uint64>(data); };

void BinaryStream::writeUnsignedShort(uint16 data) { write<uint16>(data); };

void BinaryStream::writeUnsignedVarInt(uint32 data) {
  uint8 next_byte;
  do {
    next_byte = data & 0x7F;
    data >>= 7;
    if (data)
      next_byte |= 0x80u;
    writeByte(next_byte);
  } while (data);
};

void BinaryStream::writeUnsignedVarInt64(uint64 data) {
  uint8 next_byte;
  do {
    next_byte = data & 0x7F;
    data >>= 7;
    if (data)
      next_byte |= 0x80u;
    writeByte(next_byte);
  } while (data);
};
void BinaryStream::writeVarInt(int32 data) {
  if (data >= 0)
    writeUnsignedVarInt(2 * data);
  else
    writeUnsignedVarInt(~(2 * data));
};
void BinaryStream::writeVarInt64(int64 data) {
  if (data >= 0)
    writeUnsignedVarInt64(2 * data);
  else
    writeUnsignedVarInt64(~(2 * data));
};

void BinaryStream::_writeInteger(int32 data) { write<int32>(data); };
void BinaryStream::_writeInteger(int16 data) { write<int16>(data); };
void BinaryStream::_writeInteger(int8 data) { write<int8>(data); };
void BinaryStream::_writeInteger(uint32 data) { write<uint32>(data); };
void BinaryStream::_writeInteger(uint16 data) { write<uint16>(data); };

void BinaryStream::write(void const *origin, uint64 num) {
  mBuffer->append((const char *)(origin), num);
}

std::string BinaryStream::getAndReleaseData() { return std::move(*mBuffer); }
} // namespace protocol
