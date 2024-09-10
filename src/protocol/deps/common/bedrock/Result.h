#pragma once
#include "protocol/Global.h"
#include "protocol/deps/Common/Bedrock/ErrorInfo.h"

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
}; // namespace Bedrock
} // namespace protocol