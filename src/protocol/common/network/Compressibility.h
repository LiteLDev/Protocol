#pragma once
#include "protocol/deps/StdInt.h"

namespace protocol {
enum class Compressibility : int32 {
  Compressible = 0x0,
  Incompressible = 0x1,
};
}