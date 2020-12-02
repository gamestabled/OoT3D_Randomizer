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

typedef struct {
    u32 textId;
    u32 bitMask;
    s16 objectId;
    s8 objectModelIdx;
    u8 itemId;
    u8 actorParam;
} DungeonRewardInfo;

u32 DungeonReward_GetOverrideText(u32 incomingTextId);
const DungeonRewardInfo* DungeonReward_GetInfoByActor(Actor* reward);
