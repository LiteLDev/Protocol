#pragma once
#include "protocol/Global.h"
#include "protocol/common/util/DataIO.h"
namespace protocol {
class StringByteInput : public BytesDataInput {
public:
  size_t mIdx;
  std::string_view mBuffer;

  [[nodiscard]] constexpr StringByteInput(std::string_view sv,
                                          size_t offset = 0) noexcept
      : mIdx(offset), mBuffer(sv) {}

public:
  virtual ~StringByteInput() = default;
  virtual bool readBytes(void *, uint64_t);
  virtual uint64_t numBytesLeft() const;
};
} // namespace protocol