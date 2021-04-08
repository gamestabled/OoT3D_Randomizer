#include "z3D/z3D.h"
#include "dungeon_rewards.h"
#include "message.h"

#define DUNGEON_REWARD( \
        textId_, bitMask_, itemId_, actorParam_, objectId_, objectModelIdx_) \
    { .textId = textId_, .bitMask = bitMask_, .objectId = objectId_, \
      .objectModelIdx = objectModelIdx_, .itemId = itemId_, .actorParam = actorParam_ }

u32 rDungeonRewardOverrides[LIGHT_MEDALLION + 1] = {
    KOKIRI_EMERALD,
    GORON_RUBY,
    ZORA_SAPPHIRE,
    FOREST_MEDALLION,
    FIRE_MEDALLION,
    WATER_MEDALLION,
    SPIRIT_MEDALLION,
    SHADOW_MEDALLION,
    LIGHT_MEDALLION,
 };

const char DungeonRewardNames[][25] = {
    "Kokiri Emerald",
    "Goron Ruby",
    "Zora's Sapphire",
    "Forest Medallion",
    "Fire Medallion",
    "Water Medallion",
    "Spirit Medallion",
    "Shadow Medallion",
    "Light Medallion",
};

static const DungeonRewardInfo rDungeonRewardTable[] = {
    [KOKIRI_EMERALD]   = DUNGEON_REWARD(0x80, 0x00040000, ITEM_KOKIRI_EMERALD,   0x13, 0x019C, 0x00),
    [GORON_RUBY]       = DUNGEON_REWARD(0x81, 0x00080000, ITEM_GORON_RUBY,       0x14, 0x019D, 0x00),
    [ZORA_SAPPHIRE]    = DUNGEON_REWARD(0x82, 0x00100000, ITEM_ZORA_SAPPHIRE,    0x15, 0x019E, 0x00),
    [FOREST_MEDALLION] = DUNGEON_REWARD(0x3E, 0x00000001, ITEM_MEDALLION_FOREST, 0x0B, 0x00BA, 0x01),
    [FIRE_MEDALLION]   = DUNGEON_REWARD(0x3C, 0x00000002, ITEM_MEDALLION_FIRE,   0x09, 0x00BA, 0x02),
    [WATER_MEDALLION]  = DUNGEON_REWARD(0x3D, 0x00000004, ITEM_MEDALLION_WATER,  0x0A, 0x00BA, 0x03),
    [SPIRIT_MEDALLION] = DUNGEON_REWARD(0x3F, 0x00000008, ITEM_MEDALLION_SPIRIT, 0x0C, 0x00BA, 0x04),
    [SHADOW_MEDALLION] = DUNGEON_REWARD(0x41, 0x00000010, ITEM_MEDALLION_SHADOW, 0x0D, 0x00BA, 0x05),
    [LIGHT_MEDALLION]  = DUNGEON_REWARD(0x40, 0x00000020, ITEM_MEDALLION_LIGHT,  0x0E, 0x00BA, 0x00),
};

u32 DungeonReward_GetOverrideText(u32 incomingTextId) {
    // commenting out for now
    // for (u32 i = KOKIRI_EMERALD; i <= LIGHT_MEDALLION; ++i) {
    //     if (rDungeonRewardTable[i].textId == incomingTextId) {
    //         return rDungeonRewardTable[rDungeonRewardOverrides[i]].textId;
    //     }
    // }
    return incomingTextId;
}

void DungeonReward_OverrideItemGive(GlobalContext* globalCtx, u8 incomingItem) {
    // if ((incomingItem >= ITEM_MEDALLION_FOREST) && (incomingItem < ITEM_KOKIRI_EMERALD)) {
    //     Item_Give(globalCtx, rDungeonRewardTable[rDungeonRewardOverrides[(incomingItem - ITEM_MEDALLION_FOREST) + FOREST_MEDALLION]].itemId);
    // } else if ((incomingItem >= ITEM_KOKIRI_EMERALD) && (incomingItem <= ITEM_ZORA_SAPPHIRE)) {
    //     Item_Give(globalCtx, rDungeonRewardTable[rDungeonRewardOverrides[incomingItem - ITEM_KOKIRI_EMERALD]].itemId);
    // }
}

u32 DungeonReward_GetBitMask(u32 dungeonReward) {
    return rDungeonRewardTable[rDungeonRewardOverrides[dungeonReward]].bitMask;
}

const u32* DungeonReward_GetBitMaskAddr(u32 dungeonReward) {
    return &rDungeonRewardTable[rDungeonRewardOverrides[dungeonReward]].bitMask;
}

const char* DungeonReward_GetName(u32 dungeonReward) {
    return DungeonRewardNames[rDungeonRewardOverrides[dungeonReward]];
}

const DungeonRewardInfo* DungeonReward_GetInfoByActor(Actor* reward) {
    switch(reward->params & 0xFF) {
        case 0x09:
            return &rDungeonRewardTable[rDungeonRewardOverrides[FIRE_MEDALLION]];
        case 0x0A:
            return &rDungeonRewardTable[rDungeonRewardOverrides[WATER_MEDALLION]];
        case 0x0B:
            return &rDungeonRewardTable[rDungeonRewardOverrides[FOREST_MEDALLION]];
        case 0x0C:
            return &rDungeonRewardTable[rDungeonRewardOverrides[SPIRIT_MEDALLION]];
        case 0x0D:
            return &rDungeonRewardTable[rDungeonRewardOverrides[SHADOW_MEDALLION]];
        case 0x0E:
            return &rDungeonRewardTable[rDungeonRewardOverrides[LIGHT_MEDALLION]];
        case 0x13:
            return &rDungeonRewardTable[rDungeonRewardOverrides[KOKIRI_EMERALD]];
        case 0x14:
            return &rDungeonRewardTable[rDungeonRewardOverrides[GORON_RUBY]];
        case 0x15:
            return &rDungeonRewardTable[rDungeonRewardOverrides[ZORA_SAPPHIRE]];
        default:
            return NULL;
    }
}
