#pragma once
#include "protocol/Global.h"
#include "protocol/common/certificates/Certificate.h"
#include "protocol/common/certificates/WebToken.h"
#include "protocol/common/network/UnverifiedCertificate.h"
#include <cstdint>

namespace protocol {

class ConnectionRequest {
public:
  std::unique_ptr<UnverifiedCertificate> mCertificateData;
  std::unique_ptr<Certificate> mCertificate;
  std::unique_ptr<WebToken> mRawToken;
  uint8_t mClientSubId;

  ConnectionRequest(ConnectionRequest const &other);
  ~ConnectionRequest() = default;

  std::string toString();

  static ConnectionRequest fromString(std::string const &str);

private:
  ConnectionRequest(std::unique_ptr<class WebToken> rawToken,
                    std::string const &certificateString);
};
} // namespace protocol