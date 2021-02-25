#include "playthrough.hpp"
#include "location_access.hpp"
#include "logic.hpp"
#include "random.hpp"
#include "spoiler_log.hpp"
#include "../code/src/item_override.h"
#include "fill.hpp"

#include <3ds.h>
#include <algorithm>
#include <cstdio>
#include <string>
#include <unistd.h>

namespace Playthrough {

    int Playthrough_Init(u32 seed) {
        Random_Init(seed);
        int success  = 0;

        while (success == 0) {
          overrides.clear();
          ItemReset();
          Exits::AccessReset();

          Settings::UpdateSettings();
          Logic::UpdateHelpers();
          success = Fill();
        }

        GenerateHash();

        if (Settings::GenerateSpoilerLog) {
          //write logs
          printf("\x1b[9;10HWriting Spoiler Log...");
          if (SpoilerLog_Write()) {
            printf("Done");
          } else {
            printf("Failed");
          }


          printf("\x1b[10;10HWriting Placement Log...");
          if (PlacementLog_Write()) {
            printf("Done\n");
          } else {
            printf("Failed\n");
          }
        } else {
          playthroughLocations = {};
        }

        return 1;
    }

    //used for generating a lot of seeds at once
    int Playthrough_Repeat(int count /*= 1*/) {
      printf("\x1b[0;0HGENERATING %d SEEDS", count);
      u32 repeatedSeed = 0;
      for (int i = 0; i < count; i++) {
        repeatedSeed = rand() % 0xFFFFFFFF;
        Settings::seed = std::to_string(repeatedSeed);
        Playthrough_Init(repeatedSeed);

        printf("\x1b[15;15HSeeds Generated: %d\n", i + 1);
      }

      return 1;
    }

    //idk where else to put this so it goes here
    s16 GetRandomPrice() {
      return 5 * ((Random() % 19) + 1);
    }
}
