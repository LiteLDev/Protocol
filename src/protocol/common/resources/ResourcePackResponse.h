#pragma once

#include "protocol/deps/StdInt.h"

namespace protocol {
enum class ResourcePackResponse : int8 {
  Cancel = 0x1,
  Downloading = 0x2,
  DownloadingFinished = 0x3,
  ResourcePackStackFinished = 0x4,
};
}