#pragma once

#include "protocol/Global.h"
#include "protocol/common/util/DataIO.h"
#include <cstdint>

namespace protocol {
class StringByteOutput : public BytesDataOutput {
public:
  std::string *mBuffer;

  [[nodiscard]] constexpr explicit StringByteOutput(std::string &str) noexcept
      : mBuffer(std::addressof(str)) {}

public:
  virtual ~StringByteOutput() = default;
  virtual void writeBytes(void const *data, uint64_t bytes);
};
} // namespace protocol