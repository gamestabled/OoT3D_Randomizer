#include "z3D/z3D.h"
#include "dungeon_rewards.h"

u32 rDungeonRewardOverrides[LIGHT_MEDALLION + 1] = {
    KOKIRI_EMERALD,  GORON_RUBY,       ZORA_SAPPHIRE,    FOREST_MEDALLION, FIRE_MEDALLION,
    WATER_MEDALLION, SPIRIT_MEDALLION, SHADOW_MEDALLION, LIGHT_MEDALLION,
};

const char DungeonRewardNames[][25] = {
    "Kokiri Emerald",  "Goron Ruby",       "Zora's Sapphire",  "Forest Medallion", "Fire Medallion",
    "Water Medallion", "Spirit Medallion", "Shadow Medallion", "Light Medallion",
};

const char* DungeonReward_GetName(u32 dungeonReward) {
    return DungeonRewardNames[rDungeonRewardOverrides[dungeonReward]];
}
