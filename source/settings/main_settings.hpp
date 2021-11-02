#pragma once

#include "setting.hpp"
#include "open_settings.hpp"
#include "world_settings.hpp"
#include "shuffle_settings.hpp"
#include "dungeon_item_settings.hpp"

class MainSettings {
public:
    MainSettings();

    void update();

    OpenSettings openSettings;
    WorldSettings worldSettings;
    ShuffleSettings shuffleSettings;
    DungeonItemSettings dungeonSettings;
};
