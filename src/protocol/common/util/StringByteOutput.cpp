#include "protocol/common/util/StringByteOutput.h"

namespace protocol {

void StringByteOutput::writeBytes(void const *data, uint64_t bytes) {
  mBuffer->append((char const *)data, bytes);
}
} // namespace protocol