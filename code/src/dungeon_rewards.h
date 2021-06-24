#ifndef _DUNGEON_REWARDS_H_
#define _DUNGEON_REWARDS_H_

#include "z3D/z3D.h"
#include <stddef.h>

typedef enum {
    /* 0x00 */ KOKIRI_EMERALD,
    /* 0x01 */ GORON_RUBY,
    /* 0x02 */ ZORA_SAPPHIRE,
    /* 0x03 */ FOREST_MEDALLION,
    /* 0x04 */ FIRE_MEDALLION,
    /* 0x05 */ WATER_MEDALLION,
    /* 0x06 */ SPIRIT_MEDALLION,
    /* 0x07 */ SHADOW_MEDALLION,
    /* 0x08 */ LIGHT_MEDALLION,
} DungeonReward;

const char* DungeonReward_GetName(u32 dungeonReward);

#endif //_DUNGEON_REWARDS_H_
