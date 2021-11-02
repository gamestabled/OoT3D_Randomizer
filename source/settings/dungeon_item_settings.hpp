#pragma once

#include "setting.hpp"

class DungeonItemSettings : public SettingsGroup {
public:
    DungeonItemSettings();

    void update();

    Setting randomizeDungeonItems;
    Setting mapsAndCompasses;
    Setting smallKeys;
    Setting gerudoKeys;
    Setting bossKeys;
    Setting ganonsBossKey;
    Setting lacsMedallionCount;
    Setting lacsStoneCount;
    Setting lacsRewardCount;
    Setting lacsDungeonCount;
    Setting lacsTokenCount;

    static const std::string ganonsKeyLACSDesc;

    enum class MapsAndCompassesSetting {
        StartWith = 0,
        Vanilla = 1,
        OwnDungeon = 2,
        AnyDungeon = 3,
        Overworld = 4,
        Anywhere = 5,
    };

    enum class SmallKeysSetting {
        StartWith = 0,
        Vanilla = 1,
        OwnDungeon = 2,
        AnyDungeon = 3,
        Overworld = 4,
        Anywhere = 5,
    };

    enum class BossKeysSetting {
        StartWith = 0,
        Vanilla = 1,
        OwnDungeon = 2,
        AnyDungeon = 3,
        Overworld = 4,
        Anywhere = 5,
    };

    enum class GanonsBossKeySetting {
        StartWith = 0,
        Vanilla = 1,
        OwnDungeon = 2,
        AnyDungeon = 3,
        Overworld = 4,
        Anywhere = 5,
        LACSVanilla = 6,
        LACSMedallions = 7,
        LACSStones = 8,
        LACSRewards = 9,
        LACSDungeons = 10,
        LACSTokens = 11,
    };

};
