#include "main_settings.hpp"

MainSettings::MainSettings() :
    openSettings(),
    worldSettings(),
    shuffleSettings(),
    dungeonSettings() {
}

void MainSettings::update() {
    openSettings.update();
    worldSettings.update();
    shuffleSettings.update();
    dungeonSettings.update();
}
