#pragma once

#include "protocol/Global.h"
#include <cstdint>

namespace protocol {

class PrintStream {
public:
  virtual ~PrintStream();
  virtual void print(std::string const &){};
};

class IDataOutput {
public:
  virtual ~IDataOutput() = default;
  virtual void writeString(std::string_view v) = 0;
  virtual void writeLongString(std::string_view v) = 0;
  virtual void writeFloat(float v) = 0;
  virtual void writeDouble(double v) = 0;
  virtual void writeByte(int8 v) = 0;
  virtual void writeShort(int16 v) = 0;
  virtual void writeInt(int32 v) = 0;
  virtual void writeLongLong(int64 v) = 0;
  virtual void writeBytes(void const *data, uint64 bytes) = 0;
};

class IDataInput {
public:
  virtual ~IDataInput() = default;
  virtual std::string readString() = 0;
  virtual std::string readLongString() = 0;
  virtual float readFloat() = 0;
  virtual double readDouble() = 0;
  virtual uint8 readByte() = 0;
  virtual int16 readShort() = 0;
  virtual int32 readInt() = 0;
  virtual int64 readLongLong() = 0;
  virtual bool readBytes(void *, uint64) = 0;
  virtual uint64 numBytesLeft() const = 0;
};

class BytesDataOutput : public IDataOutput {
public:
  virtual ~BytesDataOutput() = default;
  virtual void writeString(std::string_view v);
  virtual void writeLongString(std::string_view v);
  virtual void writeFloat(float);
  virtual void writeDouble(double);
  virtual void writeByte(int8 v);
  virtual void writeShort(int16);
  virtual void writeInt(int32);
  virtual void writeLongLong(int64);
};

class BytesDataInput : public IDataInput {
public:
  virtual ~BytesDataInput() = default;
  virtual std::string readString();
  virtual std::string readLongString();
  virtual float readFloat();
  virtual double readDouble();
  virtual uint8 readByte();
  virtual int16 readShort();
  virtual int32 readInt();
  virtual int64 readLongLong();
};

} // namespace protocol
