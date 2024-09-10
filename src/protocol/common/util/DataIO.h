#pragma once

#include "protocol/Global.h"
#include <cstdint>

namespace protocol {
class IDataOutput {
public:
  virtual ~IDataOutput() = default;
  virtual void writeString(std::string_view v) = 0;
  virtual void writeLongString(std::string_view v) = 0;
  virtual void writeFloat(float v) = 0;
  virtual void writeDouble(double v) = 0;
  virtual void writeByte(char v) = 0;
  virtual void writeShort(short v) = 0;
  virtual void writeInt(int v) = 0;
  virtual void writeLongLong(int64_t v) = 0;
  virtual void writeBytes(void const *data, uint64_t bytes) = 0;
};

class IDataInput {
public:
  virtual ~IDataInput() = default;
  virtual std::string readString() = 0;
  virtual std::string readLongString() = 0;
  virtual float readFloat() = 0;
  virtual double readDouble() = 0;
  virtual uint8_t readByte() = 0;
  virtual short readShort() = 0;
  virtual int readInt() = 0;
  virtual int64_t readLongLong() = 0;
  virtual bool readBytes(void *, uint64_t) = 0;
  virtual uint64_t numBytesLeft() const = 0;
};

class BytesDataOutput : public IDataOutput {
public:
  virtual ~BytesDataOutput() = default;
  virtual void writeString(std::string_view v);
  virtual void writeLongString(std::string_view v);
  virtual void writeFloat(float);
  virtual void writeDouble(double);
  virtual void writeByte(char v);
  virtual void writeShort(short);
  virtual void writeInt(int);
  virtual void writeLongLong(int64_t);
};

class BytesDataInput : public IDataInput {
public:
  virtual ~BytesDataInput() = default;
  virtual std::string readString();
  virtual std::string readLongString();
  virtual float readFloat();
  virtual double readDouble();
  virtual uint8_t readByte();
  virtual short readShort();
  virtual int readInt();
  virtual int64_t readLongLong();
};

} // namespace protocol
