#pragma once

#include "protocol/Global.h"
#include "protocol/deps/core/semver/SemVersion.h"

namespace protocol {
class BaseGameVersion {
public:
  SemVersion mSemVersion;
  bool mNeverCompatible;

  BaseGameVersion();
  BaseGameVersion(class BaseGameVersion const &rhs);
  explicit BaseGameVersion(class SemVersion const &semVersion);

  BaseGameVersion(ushort major, uint minor, uint patch);
  SemVersion const &asSemVersion() const;
  std::string const &asString() const;
  ushort getMajor() const;
  ushort getMinor() const;
  ushort getPatch() const;
  bool isAnyVersion() const;
  bool isCompatibleWith(class BaseGameVersion const &baseGameVersion) const;
  bool isNeverCompatible() const;
  bool isValid() const;
  bool operator!=(class BaseGameVersion const &rhs) const;
  bool operator<(class BaseGameVersion const &rhs) const;
  bool operator<=(class BaseGameVersion const &rhs) const;
  BaseGameVersion &operator=(class BaseGameVersion const &);
  bool operator==(class BaseGameVersion const &rhs) const;
  bool operator>(class BaseGameVersion const &rhs) const;
  bool operator>=(class BaseGameVersion const &rhs) const;
  ~BaseGameVersion() = default;
  static SemVersion::MatchType fromString(std::string const &source,
                                          class BaseGameVersion &output);
  static class BaseGameVersion const ANY;
  static class BaseGameVersion const EMPTY;
  static class BaseGameVersion const INCOMPATIBLE;
};

} // namespace protocol