#pragma once
#include "protocol/Global.h"
#include "protocol/network/UnverifiedCertificate.h"

namespace protocol {
class Certificate {
  UnverifiedCertificate mUnverifiedCertificate;
  std::unique_ptr<Certificate> mParentCertificate;
  bool mIsValid;

public:
  Certificate(Certificate &&other);
  Certificate(Certificate const &other);

  ~Certificate() = default;

  std::string toString() const;

  Certificate(UnverifiedCertificate const &unverifiedCertificate,
              std::unique_ptr<Certificate> parentCertificate);
};
} // namespace protocol