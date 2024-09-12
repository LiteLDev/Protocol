#pragma once

#include "protocol/Global.h"
#include "protocol/world/level/storage/AllExperiments.h"
#include <vector>

namespace protocol {

struct ExperimentData {
  std::string Name;
  bool Enabled;
};

class Experiments {
public:
  std::vector<ExperimentData> mExperimentData;
  std::vector<ExperimentData> mDeprecatedData;
  bool mExperimentsEverToggled;

public:
};
} // namespace protocol