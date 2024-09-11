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
  virtual bool read(void *target, uint64 num);

  template <typename T> bool read(T *target) { return read(target, sizeof(T)); }

  bool canReadBool() const;
  void ensureReadCompleted() const;
  bool getBool();
  uint8 getByte();
  double getDouble();
  float getFloat();
  int32 getSignedBigEndianInt();
  int32 getSignedInt();
  int64 getSignedInt64();
  int16 getSignedShort();
  std::string getString(uint64 = 0);
  void getString(std::string &, uint64 = 0);
  uint8 getUnsignedChar();
  uint32 getUnsignedInt();
  uint64 getUnsignedInt64();
  uint16 getUnsignedShort();
  uint32 getUnsignedVarInt();
  uint64 getUnsignedVarInt64();
  int32 getVarInt();
  int64 getVarInt64();
  bool hasOverflowed() const;
  StreamReadResult getReadCompleteResult();

  size_t getLength() const;
  void setReadPointer(size_t pos);

  void readVectorList(std::vector<uint32> &);
};

class BinaryStream : public ReadOnlyBinaryStream {
public:
  std::string mOwnedBuffer;
  std::string *mBuffer;

  BinaryStream();
  BinaryStream(std::string &buffer, bool copyBuffer);

  virtual ~BinaryStream();

  void reset();
  void writeBool(bool data);
  void writeByte(uint8 data);
  void writeDouble(double data);
  void writeFloat(float data);
  void writeSignedBigEndianInt(int32 data);
  void writeSignedInt(int32 data);
  void writeSignedInt64(int64 data);
  void writeSignedShort(int16 data);
  void writeString(std::string_view data);
  void writeUnsignedChar(uint8 data);
  void writeUnsignedInt(uint32 data);
  void writeUnsignedInt64(uint64 data);
  void writeUnsignedShort(uint16 data);
  void writeUnsignedVarInt(uint32 data);
  void writeUnsignedVarInt64(uint64 data);
  void writeVarInt(int32 data);
  void writeVarInt64(int64 data);

private:
  void _writeInteger(int32);
  void _writeInteger(int16);
  void _writeInteger(int8);
  void _writeInteger(uint32);
  void _writeInteger(uint16);

public:
  void write(void const *origin, uint64 num);
  template <typename T> void write(T value) {
    write((uint8 *)&value, sizeof(T));
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