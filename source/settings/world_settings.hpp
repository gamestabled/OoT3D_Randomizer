#pragma once

#include "setting.hpp"

class WorldSettings : public SettingsGroup {
public:
    WorldSettings();

    void update();

    Setting randomizeWorld;
    Setting startingAge;
    Setting shuffleEntrances;
    Setting shuffleDungeonEntrances;
    Setting shuffleOverworldEntrances;
    Setting shuffleInteriorEntrances;
    Setting bombchusInLogic;
    Setting ammoDrops;
    Setting heartDropRefill;
    Setting mqDungeonCount;
    Setting setDungeonTypes;
    Setting mqDeku;
    Setting mqDodongo;
    Setting mqJabu;
    Setting mqForest;
    Setting mqFire;
    Setting mqWater;
    Setting mqSpirit;
    Setting mqShadow;
    Setting mqBotW;
    Setting mqIceCavern;
    Setting mqGTG;
    Setting mqCastle;

    enum class AgeSetting {
        Adult = 0,
        Child = 1,
        Random = 2,
    };

    enum class ShuffleInteriorEntrances {
        Off = 0,
        Simple = 1,
        All = 2,
    };

    enum class AmmoDrops {
        Vanilla = 0,
        Bombchu = 1,
        None = 2,
    };

    enum class HeartDropRefills {
        Vanilla = 0,
        NoDrop = 1,
        NoRefill = 2,
        NoDropRefill = 3,
    };

    enum class DungeonSetting {
        Vanilla = 0,
        MQ = 1,
        Random = 2,
    };

    enum class MQDungeonCount {
        Random = 13,
    };

    bool tooManyMQDungeonsSelectedError = false;
    bool notEnoughMQDungeonsSelectedError = false;

private:
    size_t dungeonsOfType(DungeonSetting type);

    static const std::string setDungeonTypesDesc;
    std::vector<Setting*> dungeonSettings;
};
