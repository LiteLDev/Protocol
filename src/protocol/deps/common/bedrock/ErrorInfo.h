#pragma once

#include "protocol/Global.h"
#include "protocol/deps/Common/Bedrock/CallStack.h"

namespace protocol {
namespace Bedrock {

template <typename E = std::error_code> struct ErrorInfo {
public:
  ErrorInfo() = default;

  [[nodiscard]] constexpr E &code() { return mError; }
  [[nodiscard]] constexpr E const &code() const { return mError; }

  E mError;
  CallStack mCallStack;
  std::vector<ErrorInfo> mStackErrors;
};

}; // namespace Bedrock

} // namespace protocol