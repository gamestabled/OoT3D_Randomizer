#include "spoiler_data.h"

SpoilerData gSpoilerData = {0};

char *SpoilerData_GetItemLocationString(u16 itemIndex)
{
    return &gSpoilerData.StringData[gSpoilerData.ItemLocations[itemIndex].LocationStrOffset];
}

char *SpoilerData_GetItemNameString(u16 itemIndex)
{
    return &gSpoilerData.StringData[gSpoilerData.ItemLocations[itemIndex].ItemStrOffset];
}

u8 SpoilerData_ChestCheck(SpoilerItemLocation itemLoc)
{
    if (gGlobalContext->sceneNum == itemLoc.LocationScene) {
        return (gGlobalContext->actorCtx.flags.chest & (1 << itemLoc.LocationFlag)) != 0;
    } else {
        return (gSaveContext.sceneFlags[itemLoc.LocationScene].chest & (1 << itemLoc.LocationFlag)) != 0;
    }
}

u8 SpoilerData_CollectableCheck(SpoilerItemLocation itemLoc)
{
    if (gGlobalContext->sceneNum == itemLoc.LocationScene) {
        return (gGlobalContext->actorCtx.flags.collect & (1 << itemLoc.LocationFlag)) != 0;
    } else {
      return (gSaveContext.sceneFlags[itemLoc.LocationScene].collect & (1 << itemLoc.LocationFlag)) != 0;
    }
}

u8 SpoilerData_ItemGetInfCheck(u8 slot)
{
    u16 inf = gSaveContext.itemGetInf[slot / 16];
    u16 swapped = ((inf & 0xFF00) >> 8) | ((inf & 0x00FF) << 8); // Swap low and high byte
    u16 flag = 1 << (slot % 16);
    return (swapped & flag) != 0;
}

u8 SpoilerData_InfTableCheck(u8 offset, u8 bit)
{
    u16 inf = gSaveContext.infTable[offset];
    u16 swapped = ((inf & 0xFF00) >> 8) | ((inf & 0x00FF) << 8); // Swap low and high byte
    u16 flag = 1 << bit;
    return (swapped & flag) != 0;
}

u8 SpoilerData_QuestItemCheck(u8 slot)
{
    return (gSaveContext.questItems & (1 << slot)) != 0;
}

u8 SpoilerData_UpgradeCheck(u8 bit)
{
    return (gSaveContext.upgrades & (1 << bit)) != 0;
}

u8 SpoilerData_GetIsItemLocationCollected(u16 itemIndex)
{
    if (itemIndex >= gSpoilerData.ItemLocationsCount) {
        return 0;
    }

    SpoilerItemLocation itemLoc = gSpoilerData.ItemLocations[itemIndex];
    switch (itemLoc.CollectionCheckType) {
        case SPOILER_CHK_NONE: { // Not ever 'collectable' (Ganon, or any item that didn't have a type set)
            return 0;
        }
        case SPOILER_CHK_ALWAYS_COLLECTED: { // Items that are considered always collected, like Link's Pocket
            return 1;
        }
        case SPOILER_CHK_CHEST: { // Chest
            return SpoilerData_ChestCheck(itemLoc);
        }
        case SPOILER_CHK_COLLECTABLE: { // Placed in world, saved in the collect flags of a scene
            return SpoilerData_CollectableCheck(itemLoc);
        }
        case SPOILER_CHK_GOLD_SKULLTULA: { // Gold skulltula
            return gSaveContext.gsFlags[itemLoc.LocationScene] & itemLoc.LocationFlag;
        }
        case SPOILER_CHK_ITEM_GET_INF: { // Check a flag set in item_get_inf
            return SpoilerData_ItemGetInfCheck(itemLoc.LocationFlag);
        }
        case SPOILER_CHK_EVENT_CHK_INF: { // Check a flag set in event_check_inf
            return EventCheck(itemLoc.LocationFlag);
        }
        case SPOILER_CHK_INF_TABLE: { // Check a flag set in event_check_inf
            return SpoilerData_InfTableCheck(itemLoc.LocationScene, itemLoc.LocationFlag);
        }
        case SPOILER_CHK_QUEST_ITEM: { // Check a flag set in questItems
            return SpoilerData_QuestItemCheck(itemLoc.LocationFlag);
        }
        default: {
            return 0;
        }
    }
    return 0;
}