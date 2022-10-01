#include "trial.hpp"

namespace Trial {

TrialInfo::TrialInfo(Text name_)
  : name(std::move(name_)) {}

  TrialInfo::~TrialInfo() = default;

  TrialInfo ForestTrial = TrialInfo(Text{"the Forest Trial", /*french*/"l'épreuve de la forêt",   /*spanish*/"la prueba del bosque",     /*italian*/"la prova della Foresta", /*german*/"Deutsch"});
  TrialInfo FireTrial   = TrialInfo(Text{"the Fire Trial",   /*french*/"l'épreuve du feu",        /*spanish*/"la prueba del fuego",      /*italian*/"la prova del Fuoco",     /*german*/"Deutsch"});
  TrialInfo WaterTrial  = TrialInfo(Text{"the Water Trial",  /*french*/"l'épreuve de l'eau",      /*spanish*/"la prueba del agua",       /*italian*/"la prova dell'Acqua",    /*german*/"Deutsch"});
  TrialInfo SpiritTrial = TrialInfo(Text{"the Spirit Trial", /*french*/"l'épreuve de l'esprit",   /*spanish*/"la prueba del espíritu",   /*italian*/"la prova dello Spirito", /*german*/"Deutsch"});
  TrialInfo ShadowTrial = TrialInfo(Text{"the Shadow Trial", /*french*/"l'épreuve de l'ombre",    /*spanish*/"la prueba de las sombras", /*italian*/"la prova dell'Ombra",    /*german*/"Deutsch"});
  TrialInfo LightTrial  = TrialInfo(Text{"the Light Trial",  /*french*/"l'épreuve de la lumière", /*spanish*/"la prueba de la luz",      /*italian*/"la prova della Luce",    /*german*/"Deutsch"});

  const TrialArray trialList = {
    &ForestTrial,
    &FireTrial,
    &WaterTrial,
    &SpiritTrial,
    &ShadowTrial,
    &LightTrial,
  };

} //namespace Trial
