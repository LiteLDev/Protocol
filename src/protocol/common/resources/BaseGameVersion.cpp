#include "protocol/common/resources/BaseGameVersion.h"

namespace protocol {
BaseGameVersion::BaseGameVersion() : mSemVersion(), mNeverCompatible(false){};

BaseGameVersion::BaseGameVersion(BaseGameVersion const &rhs)
    : mSemVersion(rhs.mSemVersion), mNeverCompatible(rhs.mNeverCompatible){};

BaseGameVersion::BaseGameVersion(SemVersion const &semVersion) {
  if (semVersion.isAnyVersion()) {
    mSemVersion = semVersion;
  } else {
    auto Major = semVersion.getMajor();
    auto Minor = semVersion.getMinor();
    auto Patch = semVersion.getPatch();
    SemVersion tempVersion(Major, Minor, Patch, "", "");
    mSemVersion = tempVersion;
  }
};

BaseGameVersion::BaseGameVersion(ushort major, uint minor, uint patch)
    : mSemVersion(SemVersion(major, minor, patch, "", "")),
      mNeverCompatible(false){};

SemVersion const &BaseGameVersion::asSemVersion() const { return mSemVersion; };

std::string const &BaseGameVersion::asString() const {
  if (isValid()) {
    return mSemVersion.asString();
  } else {
    return "";
  }
};

ushort BaseGameVersion::getMajor() const { return mSemVersion.getMajor(); };

ushort BaseGameVersion::getMinor() const { return mSemVersion.getMinor(); };

ushort BaseGameVersion::getPatch() const { return mSemVersion.getPatch(); };

bool BaseGameVersion::isAnyVersion() const {
  return mSemVersion.isAnyVersion();
};

bool BaseGameVersion::isCompatibleWith(
    BaseGameVersion const &baseGameVersion) const {
  if (isValid()) {
    if (!isAnyVersion()) {
      return *this <= baseGameVersion;
    }
  }
  return true;
};

bool BaseGameVersion::isNeverCompatible() const { return mNeverCompatible; };

bool BaseGameVersion::isValid() const {
  return mNeverCompatible || mSemVersion.isValid();
};

bool BaseGameVersion::operator!=(BaseGameVersion const &rhs) const {
  if (mNeverCompatible && rhs.mNeverCompatible) {
    return false;
  }
  if (!mNeverCompatible) {
    return !(mSemVersion == rhs.mSemVersion);
  }
  return true;
};

bool BaseGameVersion::operator<(BaseGameVersion const &rhs) const {
  return mSemVersion < rhs.mSemVersion;
};

bool BaseGameVersion::operator<=(BaseGameVersion const &rhs) const {
  return mSemVersion <= rhs.mSemVersion;
};

BaseGameVersion &BaseGameVersion::operator=(BaseGameVersion const &rhs) {
  mSemVersion = rhs.mSemVersion;
  mNeverCompatible = rhs.mNeverCompatible;
  return *this;
};

bool BaseGameVersion::operator==(BaseGameVersion const &rhs) const {
  if (mNeverCompatible && rhs.mNeverCompatible) {
    return true;
  }
  if (!mNeverCompatible) {
    return mSemVersion == rhs.mSemVersion;
  }
  return false;
};

bool BaseGameVersion::operator>(BaseGameVersion const &rhs) const {
  return mSemVersion > rhs.mSemVersion;
};

bool BaseGameVersion::operator>=(BaseGameVersion const &rhs) const {
  return mSemVersion >= rhs.mSemVersion;
};

SemVersion::MatchType BaseGameVersion::fromString(std::string const &source,
                                                  BaseGameVersion &output) {

  SemVersion::MatchType matchType = SemVersion::fromString(
      source, output.mSemVersion, SemVersion::ParseOption::AllowWildcards);
  output.mNeverCompatible = false;

  if (matchType == SemVersion::MatchType::None) {
    SemVersion tempVersion;
    output.mSemVersion = tempVersion;
  } else if (!output.mSemVersion.isAnyVersion()) {
    uint16 major = output.mSemVersion.getMajor();
    uint16 minor = output.mSemVersion.getMinor();
    uint16 patch = output.mSemVersion.getPatch();
    std::string preRelease;
    std::string buildMeta;
    SemVersion tempVersion(major, minor, patch, "", "");
    output.mSemVersion = tempVersion;
  }

  return matchType;
};

} // namespace protocol