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

bool ReadOnlyBinaryStream::read(void *target, uint64_t num) {
  if (mHasOverflowed) {
    return false;
  }
  uint64_t newReadPointer = num + mReadPointer;
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

uint8_t ReadOnlyBinaryStream::getByte() {
  uint8_t value = 0;
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

int32_t ReadOnlyBinaryStream::getSignedBigEndianInt() {
  int32_t value = 0;
  if (read<>(&value)) {
    return _byteswap_ulong(value);
  }
  return _byteswap_ulong(value);
}

int32_t ReadOnlyBinaryStream::getSignedInt() {
  int32_t value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

int64_t ReadOnlyBinaryStream::getSignedInt64() {
  int64_t value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

int16_t ReadOnlyBinaryStream::getSignedShort() {
  int16_t value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

std::string ReadOnlyBinaryStream::getString(uint64_t maxLength) {
  std::string outString;
  getString(outString, maxLength);
  return outString;
};

void ReadOnlyBinaryStream::getString(std::string &outString,
                                     uint64_t maxLength) {
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

uint8_t ReadOnlyBinaryStream::getUnsignedChar() {
  uint8_t value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

uint32_t ReadOnlyBinaryStream::getUnsignedInt() {
  uint32_t value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

uint64_t ReadOnlyBinaryStream::getUnsignedInt64() {
  uint64_t value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

uint16_t ReadOnlyBinaryStream::getUnsignedShort() {
  uint16_t value = 0;
  if (read<>(&value)) {
    return value;
  }
  return value;
};

uint32_t ReadOnlyBinaryStream::getUnsignedVarInt() {
  int32_t value = 0;
  int shift = 0;
  uint8_t b;
  while (((b = getByte()) & 0x80) == 0x80) {
    value |= (long)(b & 0x7F) << (shift++ * 7);
  }
  return value | ((long)(b & 0x7F) << (shift * 7));
};

uint64_t ReadOnlyBinaryStream::getUnsignedVarInt64() {
  int64_t value = 0;
  int shift = 0;
  uint8_t b;
  while (((b = getByte()) & 0x80) == 0x80) {
    value |= (long)(b & 0x7F) << (shift++ * 7);
  }
  return value | ((long)(b & 0x7F) << (shift * 7));
};

int32_t ReadOnlyBinaryStream::getVarInt() {
  uint32_t decoded_value;

  decoded_value = getUnsignedVarInt();
  if ((decoded_value & 1) != 0)
    return ~(decoded_value >> 1);
  else
    return decoded_value >> 1;
};

int64_t ReadOnlyBinaryStream::getVarInt64() {
  uint64_t decoded_value;

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

void BinaryStream::writeByte(uint8_t data) { write<uint8_t>(data); };

void BinaryStream::writeDouble(double data) { write<double>(data); };

void BinaryStream::writeFloat(float data) { write<float>(data); };

void BinaryStream::writeSignedBigEndianInt(int32_t data) {
  auto value = _byteswap_ulong(data);
  write<int32_t>(value);
};

void BinaryStream::writeSignedInt(int32_t data) { write<int32_t>(data); };

void BinaryStream::writeSignedInt64(int64_t data) { write<int64_t>(data); };

void BinaryStream::writeSignedShort(int16_t data) { write<int16_t>(data); };

void BinaryStream::writeString(std::string_view data) {
  writeUnsignedVarInt((uint32_t)data.size());
  mBuffer->append(data);
};

void BinaryStream::writeUnsignedChar(uint8_t data) { write<uint8_t>(data); };

void BinaryStream::writeUnsignedInt(uint32_t data) { write<uint32_t>(data); };

void BinaryStream::writeUnsignedInt64(uint64_t data) { write<uint64_t>(data); };

void BinaryStream::writeUnsignedShort(uint16_t data) { write<uint16_t>(data); };

void BinaryStream::writeUnsignedVarInt(uint32_t data) {
  uint8_t next_byte;
  do {
    next_byte = data & 0x7F;
    data >>= 7;
    if (data)
      next_byte |= 0x80u;
    writeByte(next_byte);
  } while (data);
};

void BinaryStream::writeUnsignedVarInt64(uint64_t data) {
  uint8_t next_byte;
  do {
    next_byte = data & 0x7F;
    data >>= 7;
    if (data)
      next_byte |= 0x80u;
    writeByte(next_byte);
  } while (data);
};
void BinaryStream::writeVarInt(int32_t data) {
  if (data >= 0)
    writeUnsignedVarInt(2 * data);
  else
    writeUnsignedVarInt(~(2 * data));
};
void BinaryStream::writeVarInt64(int64_t data) {
  if (data >= 0)
    writeUnsignedVarInt64(2 * data);
  else
    writeUnsignedVarInt64(~(2 * data));
};

void BinaryStream::_writeInteger(int32_t data) { write<int32_t>(data); };
void BinaryStream::_writeInteger(int16_t data) { write<int16_t>(data); };
void BinaryStream::_writeInteger(int8_t data) { write<int8_t>(data); };
void BinaryStream::_writeInteger(uint32_t data) { write<uint32_t>(data); };
void BinaryStream::_writeInteger(uint16_t data) { write<uint16_t>(data); };

void BinaryStream::write(void const *origin, uint64_t num) {
  mBuffer->append((const char *)(origin), num);
}

std::string BinaryStream::getAndReleaseData() { return std::move(*mBuffer); }
} // namespace protocol
