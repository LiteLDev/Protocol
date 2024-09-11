#pragma once
#include "protocol/Global.h"

namespace protocol {
class NetworkPeer {
public:
  using PacketRecvTimepoint = std::chrono::steady_clock::time_point;

  enum class Reliability : int32 {
    Reliable = 0x0,
    ReliableOrdered = 0x1,
    Unreliable = 0x2,
    UnreliableSequenced = 0x3,
  };
};
} // namespace protocol