#pragma once

namespace protocol {
enum class StreamReadResult : __int32 {
  Malformed = 0x0,
  Valid = 0x1,
};
}