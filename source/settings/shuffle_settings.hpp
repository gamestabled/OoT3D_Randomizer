#pragma once

#include "setting.hpp"

class ShuffleSettings : public SettingsGroup {
public:
    ShuffleSettings();

    void update();

    Setting randomizeShuffle;
    Setting shuffleRewards;
    Setting linksPocketItem;
    Setting shuffleSongs;
    Setting shuffleShops;
    Setting shuffleTokens;
    Setting shuffleScrubs;
    Setting shuffleCows;
    Setting shuffleKokiriSword;
    Setting shuffleOcarinas;
    Setting shuffleWeirdEgg;
    Setting shuffleGerudoToken;
    Setting shuffleMagicBeans;
    Setting shuffleMerchants;
    Setting shuffleAdultTradeQuest;

    enum class RewardSetting {
        EndOfDungeon = 0,
        AnyDungeon = 1,
        Overworld = 2,
        Anywhere = 3,
    };
};
