#pragma once
#include "protocol/Global.h"
#include "protocol/deps/core/resource/PackType.h"
#include "protocol/deps/core/semver/SemVersion.h"
#include "protocol/deps/utility/UUID.h"

namespace protocol {
struct PackIdVersion {
public:
  mce::UUID mId;
  SemVersion mVersion;
  PackType mPackType;

public:
  PackIdVersion();
  PackIdVersion(class mce::UUID const &id, class SemVersion const &version,
                PackType packType);

  std::string asString() const;
  bool operator!=(struct PackIdVersion const &rhs) const;
  bool operator<(struct PackIdVersion const &rhs) const;
  bool operator==(struct PackIdVersion const &rhs) const;
  bool satisfies(struct PackIdVersion const &rhs) const;
  ~PackIdVersion();

  // static struct PackIdVersion fromString(std::string const &);
};
} // namespace protocol