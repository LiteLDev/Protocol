#include "protocol/deps/core/semver/SemVersion.h"
#include <regex>

namespace protocol {
SemVersion::SemVersion()
    : mMajor(0), mMinor(0), mPatch(0), mPreRelease(""), mBuildMeta(""),
      mFullVersionString(""), mValidVersion(false), mAnyVersion(false){};

SemVersion::SemVersion(class SemVersion const &other)
    : mPatch(other.mPatch), mPreRelease(other.mPreRelease),
      mBuildMeta(other.mBuildMeta),
      mFullVersionString(other.mFullVersionString),
      mValidVersion(other.mValidVersion), mAnyVersion(other.mAnyVersion){};

SemVersion::SemVersion(struct SemVersion::any_version_constructor)
    : mMajor(0), mMinor(0), mPatch(0), mPreRelease(""), mBuildMeta(""),
      mFullVersionString("*"), mValidVersion(true), mAnyVersion(true){};

SemVersion::SemVersion(ushort major, ushort minor, ushort patch,
                       std::string const &preRelease,
                       std::string const &buildMeta)
    : mMajor(major), mMinor(minor), mPatch(patch), mPreRelease(preRelease),
      mBuildMeta(buildMeta), mFullVersionString(""), mValidVersion(true),
      mAnyVersion(false) {
  _parseVersionToString();
};

std::string const &SemVersion::asString() const { return mFullVersionString; };

ushort SemVersion::getMajor() const { return mMajor; };

ushort SemVersion::getMinor() const { return mMinor; };

ushort SemVersion::getPatch() const { return mPatch; };

std::string const &SemVersion::getPreRelease() const { return mPreRelease; };

bool SemVersion::isAnyVersion() const { return mAnyVersion; };

bool SemVersion::isValid() const { return mValidVersion; };

bool SemVersion::operator!=(SemVersion const &rhs) const {
  return !(*this == rhs);
};

void _versionSplit(std::vector<std::string> &result, const std::string &str,
                   char delimiter) {
  size_t start = 0;
  size_t end = str.find(delimiter);
  while (end != std::string::npos) {
    result.push_back(str.substr(start, end - start));
    start = end + 1;
    end = str.find(delimiter, start);
  }
  result.push_back(str.substr(start));
}

bool SemVersion::operator<(SemVersion const &rhs) const {
  if (mAnyVersion && !rhs.mAnyVersion) {
    return false;
  }
  if (!mAnyVersion && rhs.mAnyVersion) {
    return true;
  }
  if (mAnyVersion && rhs.mAnyVersion) {
    return false;
  }

  auto thisTuple = std::make_tuple(mMajor, mMinor, mPatch);
  auto rhsTuple = std::make_tuple(rhs.mMajor, rhs.mMinor, rhs.mPatch);

  if (thisTuple == rhsTuple) {
    if (mPreRelease.empty() && rhs.mPreRelease.empty()) {
      return false;
    }
    if (mPreRelease.empty()) {
      return false;
    }
    if (rhs.mPreRelease.empty()) {
      return true;
    }

    std::vector<std::string> thisPreReleaseIds;
    std::vector<std::string> rhsPreReleaseIds;
    _versionSplit(thisPreReleaseIds, mPreRelease, '.');
    _versionSplit(rhsPreReleaseIds, rhs.mPreRelease, '.');

    for (size_t i = 0;
         i < std::min(thisPreReleaseIds.size(), rhsPreReleaseIds.size()); ++i) {
      const std::string &thisId = thisPreReleaseIds[i];
      const std::string &rhsId = rhsPreReleaseIds[i];

      bool thisIsIntegral =
          std::all_of(thisId.begin(), thisId.end(), ::isdigit);
      bool rhsIsIntegral = std::all_of(rhsId.begin(), rhsId.end(), ::isdigit);

      if (thisIsIntegral && rhsIsIntegral) {
        int thisNum = std::stoi(thisId);
        int rhsNum = std::stoi(rhsId);
        if (thisNum != rhsNum) {
          return thisNum < rhsNum;
        }
      } else if (thisIsIntegral != rhsIsIntegral) {
        return thisIsIntegral;
      } else {
        if (thisId != rhsId) {
          return thisId < rhsId;
        }
      }
    }
    return thisPreReleaseIds.size() < rhsPreReleaseIds.size();
  }
  return thisTuple < rhsTuple;
};

bool SemVersion::operator<=(SemVersion const &rhs) const {
  return !(*this > rhs);
};

SemVersion &SemVersion::operator=(SemVersion const &rhs) {
  this->mMajor = rhs.mMajor;
  this->mPatch = rhs.mPatch;
  this->mPreRelease = rhs.mPreRelease;
  this->mBuildMeta = rhs.mBuildMeta;
  this->mFullVersionString = rhs.mFullVersionString;
  this->mValidVersion = rhs.mValidVersion;
  return *this;
};

bool SemVersion::operator==(SemVersion const &rhs) const {
  if (mAnyVersion && rhs.mAnyVersion) {
    return true;
  }

  if (!mAnyVersion && !rhs.mAnyVersion) {
    auto thisTuple = std::make_tuple(mMajor, mMinor, mPatch, mPreRelease);
    auto rhsTuple =
        std::make_tuple(rhs.mMajor, rhs.mMinor, rhs.mPatch, rhs.mPreRelease);
    return thisTuple == rhsTuple;
  }

  return false;
};

bool SemVersion::operator>(SemVersion const &rhs) const {
  return !(*this == rhs) && !(*this < rhs);
};

bool SemVersion::operator>=(SemVersion const &rhs) const {
  return !(*this < rhs);
};

bool SemVersion::satisfies(SemVersion const &neededVersion) const {
  return mAnyVersion || neededVersion.mAnyVersion ||
         (mMajor == neededVersion.mMajor && mMinor >= neededVersion.mMinor);
};

SemVersion::~SemVersion() = default;

SemVersion::MatchType
SemVersion::fromJson(Json::Value const &json, SemVersion &output,
                     SemVersion::ParseOption parseOption) {
  if (json.isArray()) {
    return fromJsonArray(json, output);
  }
  if (!json.isString()) {
    return SemVersion::MatchType::None;
  }
  std::string defaultValue;
  std::string src = json.asString();
  MatchType result = fromString(src, output, parseOption);
  return result;
};

SemVersion::MatchType SemVersion::fromJsonArray(Json::Value const &jsonArray,
                                                SemVersion &output) {
  if (!jsonArray.isArray()) {
    return SemVersion::MatchType::None;
  }
  if (jsonArray.size() != 3) {
    return SemVersion::MatchType::None;
  }
  const Json::Value &majorValue = jsonArray[0];
  const Json::Value &minorValue = jsonArray[1];
  const Json::Value &patchValue = jsonArray[2];
  if (!majorValue.isUInt() || !minorValue.isUInt() || !patchValue.isUInt()) {
    return SemVersion::MatchType::None;
  }
  output.mMajor = majorValue.asUInt();
  output.mMinor = minorValue.asUInt();
  output.mPatch = patchValue.asUInt();
  output._parseVersionToString();
  output.mValidVersion = true;
  return SemVersion::MatchType::Full;
};

SemVersion::MatchType
SemVersion::fromString(std::string const &src, SemVersion &output,
                       SemVersion::ParseOption parseOption) {
  static const std::string SemVerRegexStr =
      "^(0|[1-9][0-9]*)(\\.(0|[1-9][0-9]*)(\\.(0|[1-9][0-9]*)(?:\\-((?:(?:(?:(?"
      ":0[0-9]*[A-Za-z-])|[1-9A-Za-z-])[0-9A-Za-z-]*)|0)(?:\\.(?:(?:(?:(?:0[0-"
      "9]*[A-Za-z-])|[1-9A-Za-z-])[0-9A-Za-z-]*)|0))*))?(?:\\+([0-9A-Za-z-]+(?:"
      "\\.[0-9A-Za-z-]+)*))?)?)?";
  static const std::regex SemVerRegex(SemVerRegexStr);

  if (src == "*") {
    output = SemVersion(); // Assuming a constructor that sets to "any version"
    if (parseOption == SemVersion::ParseOption::NoWildcards) {
      output.mValidVersion = false;
      return SemVersion::MatchType::None;
    }
    return SemVersion::MatchType::Full;
  }

  std::smatch results;
  if (std::regex_search(src, results, SemVerRegex) &&
      results.length(0) == src.length()) {
    output.mMajor = std::stoi(results[1].str());
    output.mMinor = results[3].matched ? std::stoi(results[3].str()) : 0;
    output.mPatch = results[5].matched ? std::stoi(results[5].str()) : 0;
    output.mPreRelease = results[6].matched ? results[6].str() : "";
    output.mBuildMeta = results[7].matched ? results[7].str() : "";
    output._parseVersionToString();
    output.mValidVersion = true;
    return SemVersion::MatchType::Full;
  } else {
    output.mFullVersionString = src;
    return SemVersion::MatchType::None;
  }
};

SemVersion::any_version_constructor const AnyVersionConstructor{

};

void SemVersion::_parseVersionToString() {
  std::ostringstream oss;
  oss << mMajor << '.' << mMinor << '.' << mPatch;

  if (!mPreRelease.empty()) {
    oss << '-' << mPreRelease;
  }

  if (!mBuildMeta.empty()) {
    oss << '+' << mBuildMeta;
  }
  mFullVersionString = oss.str();
};
} // namespace protocol