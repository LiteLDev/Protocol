#pragma once

namespace protocol {
enum class PacketPriority : int {
  Immediate = 0x0,
  High = 0x1,
  Medium = 0x2,
  Low = 0x3,
  Count = 0x4,
};
}