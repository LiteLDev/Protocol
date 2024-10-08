#include "protocol/util/StringByteInput.h"

namespace protocol {

bool StringByteInput::readBytes(void *data, uint64 bytes) {
  auto M_len = mBuffer.length();
  if (mIdx != M_len) {
    auto v6 = numBytesLeft();
    if (v6 < bytes)
      bytes = v6;
    memcpy(data, &mBuffer.data()[mIdx], bytes);
    mIdx += bytes;
  }
  return mIdx != M_len;
};

uint64 StringByteInput::numBytesLeft() const {
  return mBuffer.length() - mIdx;
};

} // namespace protocol