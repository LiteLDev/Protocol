#include "protocol/common/util/DataIO.h"

namespace protocol {

void BytesDataOutput::writeString(std::string_view v) {
  writeShort(v.length());
  writeBytes(v.data(), v.length());
};
void BytesDataOutput::writeLongString(std::string_view v) {
  writeInt(v.length());
  writeBytes(v.data(), v.length());
};
void BytesDataOutput::writeFloat(float v) { writeBytes(&v, 4); };
void BytesDataOutput::writeDouble(double v) { writeBytes(&v, 8); };
void BytesDataOutput::writeByte(int8 v) { writeBytes(&v, 1); };
void BytesDataOutput::writeShort(int16 v) { writeBytes(&v, 2); };
void BytesDataOutput::writeInt(int32 v) { writeBytes(&v, 4); };
void BytesDataOutput::writeLongLong(int64 v) { writeBytes(&v, 8); };

std::string BytesDataInput::readString() {
  auto len = readShort();
  if (len < 0) {
    return "";
  }
  std::string result;
  result.resize(len);
  readBytes(result.data(), len);
  return result;
};

std::string BytesDataInput::readLongString() {
  auto len = readInt();
  if (len < 0) {
    return "";
  }
  std::string result;
  result.resize(len);
  readBytes(result.data(), len);
  return result;
};

float BytesDataInput::readFloat() {
  float result;
  readBytes(&result, 4);
  return result;
};

double BytesDataInput::readDouble() {
  double result;
  readBytes(&result, 8);
  return result;
};

uint8 BytesDataInput::readByte() {
  uint8 result;
  readBytes(&result, 1);
  return result;
};

int16 BytesDataInput::readShort() {
  int16 result;
  readBytes(&result, 2);
  return result;
};

int32 BytesDataInput::readInt() {
  int32 result;
  readBytes(&result, 4);
  return result;
};

int64 BytesDataInput::readLongLong() {
  int64 result;
  readBytes(&result, 8);
  return result;
};

} // namespace protocol