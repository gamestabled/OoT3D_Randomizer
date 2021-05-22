#include "trial.hpp"

namespace Trial {

TrialInfo::TrialInfo(Text name_)
  : name(std::move(name_)) {}

  TrialInfo::~TrialInfo() = default;

  TrialInfo ForestTrial = TrialInfo(Text{"the Forest Trial", /*french*/"", /*spanish*/""});
  TrialInfo FireTrial   = TrialInfo(Text{"the Fire Trial",   /*french*/"", /*spanish*/""});
  TrialInfo WaterTrial  = TrialInfo(Text{"the Water Trial",  /*french*/"", /*spanish*/""});
  TrialInfo SpiritTrial = TrialInfo(Text{"the Spirit Trial", /*french*/"", /*spanish*/""});
  TrialInfo ShadowTrial = TrialInfo(Text{"the Shadow Trial", /*french*/"", /*spanish*/""});
  TrialInfo LightTrial  = TrialInfo(Text{"the Light Trial",  /*french*/"", /*spanish*/""});

  const TrialArray trialList = {
    &ForestTrial,
    &FireTrial,
    &WaterTrial,
    &SpiritTrial,
    &ShadowTrial,
    &LightTrial,
  };

} //namespace Trial
