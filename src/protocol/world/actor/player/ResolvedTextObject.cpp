#include "protocol/world/actor/player/ResolvedTextObject.h"
#include "json/writer.h"

namespace protocol {

ResolvedTextObject::~ResolvedTextObject() = default;

std::string ResolvedTextObject::getAsJsonString() const {
  Json::FastWriter v3;
  return v3.write(mResolvedTextObjectJson);
};

Json::Value const &ResolvedTextObject::getJson() const {
  return mResolvedTextObjectJson;
};

} // namespace protocol