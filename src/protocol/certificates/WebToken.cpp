#include "protocol/certificates/WebToken.h"
#include "protocol/utility/Base64.h"

namespace protocol {
WebToken::WebToken(std::string token) {
  std::vector<std::string> parts;
  size_t pos = 0;

  while ((pos = token.find('.')) != std::string::npos) {
    parts.emplace_back(token.substr(0, pos));
    token.erase(0, pos + 1);
  }

  parts.emplace_back(token);

  if (parts.size() == 3) {
    mHeader = parts[0];
    mData = parts[1];
    mSignature = parts[2];
  }

  _parse(mHeaderInfo, mHeader);
  _parse(mDataInfo, mData);
}

WebToken::WebToken() {
  mHeader = std::string();
  mHeaderInfo = Json::Value(Json::ValueType::nullValue);
  mData = std::string();
  mDataInfo = Json::Value(Json::ValueType::nullValue);
  mSignature = std::string();
}

WebToken::WebToken(const WebToken &other)
    : mHeader(other.mHeader), mHeaderInfo(other.mHeaderInfo),
      mData(other.mData), mDataInfo(other.mDataInfo),
      mSignature(other.mSignature) {}

std::string WebToken::toString() const {
  return mHeader + "." + mData + "." + mSignature;
}

void WebToken::_parse(class Json::Value &value, std::string const &data) {
  if (data.empty())
    return;
  auto decodedData = protocol::Utils::base64url_decode(data);

  Json::Reader reader;
  reader.parse(decodedData, value);
}

} // namespace protocol
