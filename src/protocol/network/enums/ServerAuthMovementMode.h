#pragma once
#include "protocol/deps/base/StdInt.h"

namespace protocol {
enum class ServerAuthMovementMode : schar {
  ClientAuthoritative = 0x0,
  ServerAuthoritative = 0x1,
  ServerAuthoritativeWithRewind = 0x2,
};
}