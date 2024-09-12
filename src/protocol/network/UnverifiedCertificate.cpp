#include "protocol/network/UnverifiedCertificate.h"
#include <algorithm>

namespace protocol {

UnverifiedCertificate::UnverifiedCertificate(UnverifiedCertificate &&other)
    : mRawToken(std::move(other.mRawToken)),
      mParentUnverifiedCertificate(
          std::move(other.mParentUnverifiedCertificate)) {}

UnverifiedCertificate::UnverifiedCertificate(const UnverifiedCertificate &other)
    : mRawToken(other.mRawToken) {
  if (other.mParentUnverifiedCertificate) {
    mParentUnverifiedCertificate = std::make_unique<UnverifiedCertificate>(
        *other.mParentUnverifiedCertificate);
  }
}

UnverifiedCertificate::UnverifiedCertificate(
    WebToken const &rawToken,
    std::unique_ptr<UnverifiedCertificate> parentUnverifiedCertificate)
    : mRawToken(rawToken) {
  mParentUnverifiedCertificate = std::move(parentUnverifiedCertificate);
}

std::string UnverifiedCertificate::toString() const {
  Json::Value root;
  Json::Value chain(Json::arrayValue);
  addToChain(chain);
  root["chain"] = chain;
  Json::FastWriter writer;
  std::string retstr = writer.write(root);
  return retstr;
}

void UnverifiedCertificate::addToChain(Json::Value &chain) const {
  std::string retstr;
  if (mParentUnverifiedCertificate) {
    mParentUnverifiedCertificate->addToChain(chain);
  }
  auto raw = mRawToken.toString();
  Json::Value cert(raw);
  chain.append(cert);
}

UnverifiedCertificate
UnverifiedCertificate::fromString(std::string const &input) {
  Json::Value root;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse(input.c_str(), root, false);

  if (!parsingSuccessful || !root.isObject()) {
  }

  const Json::Value &chain = root["chain"];
  if (!chain.isArray()) {
  }

  std::unique_ptr<UnverifiedCertificate> parentCertificate;
  for (const auto &jwt : chain) {
    if (jwt.isString()) {
      std::string tokenStr = jwt.asString();
      WebToken webToken(tokenStr);
      std::unique_ptr<UnverifiedCertificate> certificate =
          std::make_unique<UnverifiedCertificate>(webToken,
                                                  std::move(parentCertificate));
      parentCertificate = std::move(certificate);
    }
  }
  return UnverifiedCertificate(*parentCertificate);
}
} // namespace protocol