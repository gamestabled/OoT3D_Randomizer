#ifndef _DUNGEON_REWARDS_H_
#define _DUNGEON_REWARDS_H_

#include "../include/z3D/z3D.h"

typedef enum {
    /* 0x00 */ R_KOKIRI_EMERALD,
    /* 0x01 */ R_GORON_RUBY,
    /* 0x02 */ R_ZORA_SAPPHIRE,
    /* 0x03 */ R_FOREST_MEDALLION,
    /* 0x04 */ R_FIRE_MEDALLION,
    /* 0x05 */ R_WATER_MEDALLION,
    /* 0x06 */ R_SPIRIT_MEDALLION,
    /* 0x07 */ R_SHADOW_MEDALLION,
    /* 0x08 */ R_LIGHT_MEDALLION,
    /* 0x09 */ DUNGEON_REWARDS_COUNT,
} DungeonReward;

extern u32 rDungeonRewardOverrides[DUNGEON_REWARDS_COUNT];

#endif //_DUNGEON_REWARDS_H_
