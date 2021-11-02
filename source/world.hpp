#pragma once

#include <vector>

#include "settings/main_settings.hpp"
#include "settings/generate_settings.hpp"

#include "locations/new_location_table.hpp"

#include "items/new_item_table.hpp"

class World {
public:
    static World* getWorld(int worldNum) {
        if (worldNum >= (int)worlds.size()) {
            worlds.resize(worldNum + 1);
            worlds[worldNum] = new World();
        }
        return worlds[worldNum];
    }

    static World* getWorld() {
        return getWorld(0);
    }

    static void deleteWorld(int worldNum) {
        delete worlds[worldNum];
        worlds[worldNum] = nullptr;
    }

    static void deleteWorld() {
        for (auto& world : worlds) {
            delete world;
            world = nullptr;
        }
    }

    void update();

    static void updateAll() {
        for (auto world : worlds) {
            world->update();
        }
    }

    void reset();
    std::string getSettingsHash();

    MainSettings mainSettings;
    GenerateSettings generateSettings;

    NewItemTable itemTable;
    NewLocationTable locationTable;

private:
    inline static std::vector<World*> worlds;
};
