#pragma once
#include "protocol/Global.h"
#include "protocol/deps/Common/Bedrock/LogLevel.h"
#include "protocol/deps/Enums/LogAreaID.h"
namespace protocol {
namespace Bedrock {

struct CallStack {

  struct Context;
  struct Frame;
  struct FrameWithContext;

  struct Context {
  public:
    std::string mMessage;
    std::optional<::protocol::Bedrock::LogLevel> mLogLevel;
    std::optional<::protocol::LogAreaID> mLogAreaID;

  public:
    Context(std::string value, std::optional<::protocol::Bedrock::LogLevel>,
            std::optional<::protocol::LogAreaID> logArea);
  };

  struct Frame {
  public:
    void *address[3];
  };

  struct FrameWithContext {
  public:
    Frame mFrame;
    std::optional<Context> mContext;

  public:
    // NOLINTBEGIN
    FrameWithContext(
        struct Bedrock::CallStack::Frame &&frame,
        std::optional<struct Bedrock::CallStack::Context> &&context);

    // NOLINTEND
  };
};
} // namespace Bedrock
} // namespace protocol