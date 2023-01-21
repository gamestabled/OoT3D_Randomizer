#include "z3D/z3D.h"
#include "dungeon_rewards.h"

// This will be overwritten by the app only if rewards are at End of Dungeons
u32 rDungeonRewardOverrides[DUNGEON_REWARDS_COUNT] = {
    R_KOKIRI_EMERALD,  R_GORON_RUBY,       R_ZORA_SAPPHIRE,    R_FOREST_MEDALLION, R_FIRE_MEDALLION,
    R_WATER_MEDALLION, R_SPIRIT_MEDALLION, R_SHADOW_MEDALLION, R_LIGHT_MEDALLION,
};
