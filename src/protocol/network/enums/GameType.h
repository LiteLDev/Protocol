#pragma once
#include "protocol/deps/base/StdInt.h"

namespace protocol {
enum class GameType : int32 {
  Undefined = -1,
  Survival = 0,
  Creative = 1,
  Adventure = 2,
  Default = 5,
  Spectator = 6,
  WorldDefault = 0,
};
}