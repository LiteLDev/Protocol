#include "protocol/util/StringByteOutput.h"

namespace protocol {

void StringByteOutput::writeBytes(void const *data, uint64 bytes) {
  mBuffer->append((char const *)data, bytes);
}
} // namespace protocol