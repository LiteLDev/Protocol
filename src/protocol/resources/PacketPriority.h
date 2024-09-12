#pragma once
#include "protocol/deps/base/StdInt.h"

namespace protocol {
enum class PacketPriority : int32 {
  Immediate = 0x0,
  High = 0x1,
  Medium = 0x2,
  Low = 0x3,
  Count = 0x4,
};
}