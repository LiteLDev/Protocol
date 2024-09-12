#pragma once
#include "protocol/Global.h"

namespace protocol {
class ResolvedTextObject {
public:
  const Json::Value mResolvedTextObjectJson;

public:
  std::string getAsJsonString() const;
  Json::Value const &getJson() const;
  ~ResolvedTextObject();
};
} // namespace protocol