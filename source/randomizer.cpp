#include "randomizer.hpp"
#include "world.hpp"
#include "new_playthrough.hpp"

void GenerateRandomizer() {
    World* world = World::getWorld();

    //save cached settings
    //save cached cosmetics

    if (world->generateSettings.seed.empty()) {
        world->generateSettings.seed = std::to_string(rand());
    } else if (world->generateSettings.seed.rfind("seed_testing_count", 0) == 0) {
        const int count = std::stoi(world->generateSettings.seed.substr(18), nullptr);
        NewPlaythrough::repeat(count);
        return;
    }

    try {
        NewPlaythrough* playthrough = new NewPlaythrough(std::hash<std::string>{}(world->generateSettings.seed));
    } catch (...) {
        // we can make some specified playthrough generation exceptions to handle
    }

    //etc..
    //WriteAllPatches
//   //Restore settings that were set to a specific value for vanilla logic
//   if (Settings::Logic.Is(LOGIC_VANILLA)) {
//       for (Option* setting : Settings::vanillaLogicDefaults) {
//           setting->RestoreDelayedOption();
//       }
//       Settings::Keysanity.RestoreDelayedOption();
//   }

}

