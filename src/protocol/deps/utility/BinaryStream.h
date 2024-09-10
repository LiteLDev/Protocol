#pragma once
#include "protocol/Global.h"
#include "protocol/deps/common/bedrock/Result.h"
#include "protocol/deps/enums/StreamReadResult.h"
#include <cstdint>

namespace protocol {
class ReadOnlyBinaryStream {
public:
  size_t mReadPointer{};
  bool mHasOverflowed{};
  std::string mOwnedBuffer;
  const std::string *mBuffer;

  explicit ReadOnlyBinaryStream();
  explicit ReadOnlyBinaryStream(std::string &&buffer);
  ReadOnlyBinaryStream(std::string const &buffer, bool copyBuffer);

  virtual ~ReadOnlyBinaryStream();
  virtual bool read(void *target, uint64_t num);

  template <typename T> bool read(T *target) { return read(target, sizeof(T)); }

  bool canReadBool() const;
  void ensureReadCompleted() const;
  bool getBool();
  uint8_t getByte();
  double getDouble();
  float getFloat();
  int32_t getSignedBigEndianInt();
  int32_t getSignedInt();
  int64_t getSignedInt64();
  int16_t getSignedShort();
  std::string getString(uint64_t = 0);
  void getString(std::string &, uint64_t = 0);
  uint8_t getUnsignedChar();
  uint32_t getUnsignedInt();
  uint64_t getUnsignedInt64();
  uint16_t getUnsignedShort();
  uint32_t getUnsignedVarInt();
  uint64_t getUnsignedVarInt64();
  int32_t getVarInt();
  int64_t getVarInt64();
  bool hasOverflowed() const;
  StreamReadResult getReadCompleteResult();

  size_t getLength() const;
  void setReadPointer(size_t pos);

  void readVectorList(std::vector<uint32_t> &);
};

class BinaryStream : public ReadOnlyBinaryStream {
  std::string mOwnedBuffer;
  std::string *mBuffer;

public:
  BinaryStream();
  BinaryStream(std::string &buffer, bool copyBuffer);

  virtual ~BinaryStream();

  void reset();
  void writeBool(bool data);
  void writeByte(uint8_t data);
  void writeDouble(double data);
  void writeFloat(float data);
  void writeSignedBigEndianInt(int32_t data);
  void writeSignedInt(int32_t data);
  void writeSignedInt64(int64_t data);
  void writeSignedShort(int16_t data);
  void writeString(std::string_view data);
  void writeUnsignedChar(uint8_t data);
  void writeUnsignedInt(uint32_t data);
  void writeUnsignedInt64(uint64_t data);
  void writeUnsignedShort(uint16_t data);
  void writeUnsignedVarInt(uint32_t data);
  void writeUnsignedVarInt64(uint64_t data);
  void writeVarInt(int32_t data);
  void writeVarInt64(int64_t data);

private:
  void _writeInteger(int32_t);
  void _writeInteger(int16_t);
  void _writeInteger(int8_t);
  void _writeInteger(uint32_t);
  void _writeInteger(uint16_t);

public:
  void write(void const *origin, uint64_t num);
  template <typename T> void write(T value) {
    write((uint8_t *)&value, sizeof(T));
  }

  std::string getAndReleaseData();
};

struct ExtendedStreamReadResult {
  StreamReadResult result;
  std::string resultContext;

  ExtendedStreamReadResult(
      StreamReadResult result = StreamReadResult::Malformed,
      std::string resultContext = "") {}

  bool isValid() { return result == StreamReadResult::Valid; }

  bool isMalformed() { return result == StreamReadResult::Malformed; }

  operator bool() { return isValid(); }

  operator std::string() { return resultContext; }
};

} // namespace protocol