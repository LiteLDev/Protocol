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
void BytesDataOutput::writeByte(char v) { writeBytes(&v, 1); };
void BytesDataOutput::writeShort(short v) { writeBytes(&v, 2); };
void BytesDataOutput::writeInt(int v) { writeBytes(&v, 4); };
void BytesDataOutput::writeLongLong(int64_t v) { writeBytes(&v, 8); };

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

uint8_t BytesDataInput::readByte() {
  uint8_t result;
  readBytes(&result, 1);
  return result;
};

short BytesDataInput::readShort() {
  short result;
  readBytes(&result, 2);
  return result;
};

int BytesDataInput::readInt() {
  int result;
  readBytes(&result, 4);
  return result;
};

int64_t BytesDataInput::readLongLong() {
  int64_t result;
  readBytes(&result, 8);
  return result;
};

} // namespace protocol