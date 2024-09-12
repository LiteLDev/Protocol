#pragma once
#include "protocol/Global.h"

namespace protocol {
class WebToken {
public:
  std::string mHeader;
  Json::Value mHeaderInfo;
  std::string mData;
  Json::Value mDataInfo;
  std::string mSignature;

  WebToken();
  explicit WebToken(std::string token);
  WebToken(const WebToken &other);

  ~WebToken() = default;

  std::string toString() const;

private:
  void _parse(class Json::Value &value, std::string const &data);
};
} // namespace protocol