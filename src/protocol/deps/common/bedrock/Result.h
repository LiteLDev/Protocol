#pragma once
#include "protocol/Global.h"
#include "protocol/deps/Common/Bedrock/ErrorInfo.h"
#include <system_error>

#pragma warning(push)
#pragma warning(disable : 4702)
#include "nonstd/expected.hpp"
#pragma warning(pop)

namespace protocol {
namespace Bedrock {
template <typename T, typename Err>
class Result : public nonstd::expected<T, ErrorInfo<Err>> {
public:
  using Base = nonstd::expected<T, ErrorInfo<Err>>;
  using Base::Base;
};

namespace Detail {
template <typename E = std::error_code>
static Bedrock::ErrorInfo<E> createError(std::errc error) {
  Bedrock::ErrorInfo<E> info;
  info.mError = std::make_error_code(error);
  return info;
}
} // namespace Detail
}; // namespace Bedrock
} // namespace protocol