#include "protocol/common/network/ConnectionRequest.h"
#include "protocol/common/util/StringByteInput.h"
#include "protocol/common/util/StringByteOutput.h"

namespace protocol {
ConnectionRequest::ConnectionRequest(ConnectionRequest const &other)
    : mClientSubId(other.mClientSubId) {
  if (other.mCertificateData) {
    mCertificateData =
        std::make_unique<UnverifiedCertificate>(*other.mCertificateData);
  }
  if (other.mCertificate) {
    mCertificate = std::make_unique<Certificate>(*other.mCertificate);
  }
  if (other.mRawToken) {
    mRawToken = std::make_unique<WebToken>(*other.mRawToken);
  }
}
ConnectionRequest::ConnectionRequest(std::unique_ptr<WebToken> rawToken,
                                     std::string const &certificateString)
    : mRawToken(std::move(rawToken)) {
  mClientSubId = 0;
  auto certificate = UnverifiedCertificate::fromString(certificateString);
  mCertificateData = std::make_unique<UnverifiedCertificate>(certificate);
}

std::string ConnectionRequest::toString() {
  std::string retstr;
  StringByteOutput out(retstr);

  if (mCertificateData) {
    auto cont = mCertificateData->toString();
    out.writeLongString(cont);
  } else {
    auto cont = mCertificate->toString();
    out.writeLongString(cont);
  }

  if (mRawToken) {
    auto str = mRawToken->toString();
    out.writeLongString(str);
  } else {
    out.writeLongString("");
  }
  return retstr;
}

ConnectionRequest ConnectionRequest::fromString(const std::string &str) {
  StringByteInput in(str);
  auto certificateDataString = in.readLongString();
  auto connectionRequestToken = in.readLongString();

  auto rewtoken =
      std::make_unique<WebToken, std::string &>(connectionRequestToken);

  return ConnectionRequest(std::move(rewtoken), certificateDataString);
}

} // namespace protocol