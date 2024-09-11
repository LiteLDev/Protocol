#include "protocol/deps/core/resource/ResourceHelper.h"

namespace protocol {
PackIdVersion::PackIdVersion()
    : mId(mce::UUID()), mVersion(SemVersion()), mPackType(PackType::Invalid){};

PackIdVersion::PackIdVersion(mce::UUID const &id, SemVersion const &version,
                             PackType packType)
    : mId(id), mVersion(version), mPackType(packType){};

std::string PackIdVersion::asString() const {
  std::string idStr = mId.asString();
  std::string versionStr = mVersion.asString();
  return idStr + "_" + versionStr;
};

bool PackIdVersion::operator!=(PackIdVersion const &rhs) const {
  return !(*this == rhs);
};

bool PackIdVersion::operator<(PackIdVersion const &rhs) const {
  auto lhs_tuple =
      std::make_tuple(std::cref(this->mId), std::cref(this->mVersion));
  auto rhs_tuple = std::make_tuple(std::cref(rhs.mId), std::cref(rhs.mVersion));
  return lhs_tuple < rhs_tuple;
};

bool PackIdVersion::operator==(PackIdVersion const &rhs) const {
  if (mId == rhs.mId) {
    return mVersion == rhs.mVersion;
  }
  return false;
};

bool PackIdVersion::satisfies(PackIdVersion const &rhs) const {
  if (mId == rhs.mId) {
    return mVersion == rhs.mVersion;
  }
  return false;
};
PackIdVersion::~PackIdVersion() = default;

// PackIdVersion PackIdVersion::fromString(std::string const &){};

} // namespace protocol