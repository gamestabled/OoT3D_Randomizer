#pragma once

#include "setting.hpp"

class OpenSettings : public SettingsGroup {
public:
    OpenSettings();

    void update();

    Setting randomizeSettings;
    Setting forest;
    Setting kakarikoGate;
    Setting doorOfTime;
    Setting zorasFountain;
    Setting gerudoFortress;
    Setting rainbowBridge;
    Setting stoneCount;
    Setting medallionCount;
    Setting rewardCount;
    Setting dungeonCount;
    Setting tokenCount;
    Setting randomGanonsTrials;
    Setting trialCount;

    enum class OpenForest : size_t {
        Closed = 0,
        Open = 1,
        ClosedDeku = 2,
    };

    enum class RainbowBridge : size_t {
        Open = 0,
        Vanilla = 1,
        Stones = 2,
        Medallions = 3,
        Rewards = 4,
        Dungeons = 5,
        Tokens = 6,
    };
};
