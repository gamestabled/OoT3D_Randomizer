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

        overrides.clear();
        ItemReset();
        Exits::AccessReset();

        Settings::UpdateSettings();
        Logic::UpdateHelpers();
        Fill_Init();

        GenerateHash();

        //write logs
        printf("\x1b[9;10H");
        if (SpoilerLog_Write()) {
          printf("Wrote spoiler log");
        } else {
          printf("Failed to write spoiler log");
        }

        printf("\x1b[10;10H");
        if (PlacementLog_Write()) {
          printf("Wrote placement log\n");
        } else {
          printf("Failed to write placement log\n");
        }

        return 1;
    }

    //used for testing
    int Playthrough_Repeat(int count /*= 1*/) {

      u32 repeatedSeed = 0;
      for (int i = 0; i < count; i++) {
        ItemReset();
        repeatedSeed = rand() % 0xFFFFFFFF;
        Playthrough_Init(repeatedSeed);

        PlacementLog_Msg(" --- ");
        std::string seedStr = std::to_string(repeatedSeed);
        PlacementLog_Msg(seedStr);
        PlacementLog_Msg("\n");

        printf("\x1b[15;15HSeeds Generated: %d\n", i + 1);
      }

      printf("\x1b[10;10H");
      if (PlacementLog_Write()) {
        printf("Wrote placement log\n");
      } else {
        printf("Failed to write placement log\n");
      }

      return 1;
    }

    //idk where else to put this so it goes here
    s16 GetRandomPrice() {
      return 5 * ((Random() % 19) + 1);
    }
}
