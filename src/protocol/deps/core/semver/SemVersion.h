#pragma once

#include "protocol/Global.h"

namespace protocol {
class SemVersion {
public:
  struct any_version_constructor;

  enum class MatchType : int {
    Full = 0x0,
    Partial = 0x1,
    None = 0x2,
  };

  enum class ParseOption : int {
    AllowWildcards = 0x0,
    NoWildcards = 0x1,
  };

  struct any_version_constructor {};

  ushort mMajor;
  ushort mMinor;
  ushort mPatch;
  std::string mPreRelease;
  std::string mBuildMeta;
  std::string mFullVersionString;
  bool mValidVersion;
  bool mAnyVersion;

public:
  SemVersion();
  SemVersion(class SemVersion const &);
  explicit SemVersion(struct SemVersion::any_version_constructor);
  SemVersion(ushort major, ushort minor, ushort patch,
             std::string const &preRelease, std::string const &buildMeta);

  std::string const &asString() const;
  ushort getMajor() const;
  ushort getMinor() const;
  ushort getPatch() const;
  std::string const &getPreRelease() const;
  bool isAnyVersion() const;
  bool isValid() const;
  bool operator!=(class SemVersion const &rhs) const;
  bool operator<(class SemVersion const &rhs) const;
  bool operator<=(class SemVersion const &rhs) const;
  class SemVersion &operator=(class SemVersion const &);
  bool operator==(class SemVersion const &rhs) const;
  bool operator>(class SemVersion const &rhs) const;
  bool operator>=(class SemVersion const &rhs) const;
  bool satisfies(class SemVersion const &neededVersion) const;
  ~SemVersion();

  static SemVersion::MatchType fromJson(class Json::Value const &json,
                                        class SemVersion &output,
                                        SemVersion::ParseOption parseOption);
  static SemVersion::MatchType fromJsonArray(class Json::Value const &jsonArray,
                                             class SemVersion &output);
  static SemVersion::MatchType fromString(std::string const &src,
                                          class SemVersion &output,
                                          SemVersion::ParseOption parseOption);
  static struct any_version_constructor const AnyVersionConstructor;
  void _parseVersionToString();
};
} // namespace protocol