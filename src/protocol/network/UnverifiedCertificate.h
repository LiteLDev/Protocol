#pragma once
#include "protocol/Global.h"
#include "protocol/certificates/WebToken.h"

namespace protocol {
class UnverifiedCertificate {
public:
  WebToken const mRawToken;
  std::unique_ptr<UnverifiedCertificate> mParentUnverifiedCertificate;

  UnverifiedCertificate(UnverifiedCertificate &&other);
  UnverifiedCertificate(const UnverifiedCertificate &other);
  ~UnverifiedCertificate() = default;

  std::string toString() const;

  void addToChain(class Json::Value &chain) const;

  static UnverifiedCertificate fromString(std::string const &input);

  UnverifiedCertificate(
      WebToken const &rawToken,
      std::unique_ptr<UnverifiedCertificate> parentUnverifiedCertificate);
};

} // namespace protocol