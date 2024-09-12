#include "protocol/certificates/Certificate.h"

namespace protocol {

Certificate::Certificate(Certificate &&other)
    : mIsValid(other.mIsValid),
      mParentCertificate(std::move(other.mParentCertificate)),
      mUnverifiedCertificate(std::move(other.mUnverifiedCertificate)) {}

Certificate::Certificate(Certificate const &other)
    : mUnverifiedCertificate(other.mUnverifiedCertificate) {
  if (other.mParentCertificate) {
    mParentCertificate =
        std::make_unique<Certificate>(*other.mParentCertificate);
  } else {
    mParentCertificate = nullptr;
  }
  mIsValid = other.mIsValid;
}

Certificate::Certificate(UnverifiedCertificate const &unverifiedCertificate,
                         std::unique_ptr<Certificate> parentCertificate)
    : mUnverifiedCertificate(unverifiedCertificate),
      mParentCertificate(std::move(parentCertificate)), mIsValid(false) {}

std::string Certificate::toString() const {
  return mUnverifiedCertificate.toString();
}

} // namespace protocol