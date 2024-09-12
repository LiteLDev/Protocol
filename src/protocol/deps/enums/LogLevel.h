#pragma once
#include "protocol/deps/base/StdInt.h"

namespace protocol {
enum class LogLevel : int32 {
  Verbose = 0x0,
  Info = 0x1,
  Warning = 0x2,
  Error = 0x3,
  Count = 0x4,
};
}