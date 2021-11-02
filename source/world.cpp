#include "world.hpp"

void World::update() {
    mainSettings.update();
    generateSettings.update();
}

void World::reset() {
    locationTable.reset();
    //todo: more
}

std::string World::getSettingsHash() {
    return ""; //TODO
}
