#include "spoiler_data.h"

#include "settings.h"
#include "gorons.h"

SpoilerData gSpoilerData = {0};

char *SpoilerData_GetItemLocationString(u16 itemIndex)
{
    return &gSpoilerData.StringData[gSpoilerData.ItemLocations[itemIndex].LocationStrOffset];
}

char *SpoilerData_GetItemNameString(u16 itemIndex)
{
    return &gSpoilerData.StringData[gSpoilerData.ItemLocations[itemIndex].ItemStrOffset];
}

SpoilerItemLocation GetSpoilerItemLocation(u8 sphere, u16 itemIndex)
{
    return gSpoilerData.ItemLocations[gSpoilerData.SphereItemLocations[gSpoilerData.Spheres[sphere].ItemLocationsOffset]];
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

u8 SpoilerData_CowCheck(SpoilerItemLocation itemLoc)
{
    if (gGlobalContext->sceneNum == itemLoc.LocationScene) {
        return (gGlobalContext->actorCtx.flags.collect & (itemLoc.LocationFlag << 0x18)) != 0;
    } else {
      return (gSaveContext.sceneFlags[itemLoc.LocationScene].collect & (itemLoc.LocationFlag << 0x18)) != 0;
    }
}

u8 SpoilerData_FishingCheck(SpoilerItemLocation itemLoc)
{
    return (gSaveContext.fishingStats.flags & (1 << itemLoc.LocationFlag)) != 0;
}

u8 SpoilerData_ScrubCheck(SpoilerItemLocation itemLoc)
{
    return (gSaveContext.sceneFlags[itemLoc.LocationScene].unk & (1 << itemLoc.LocationFlag)) != 0;
}

u8 SpoilerData_BiggoronCheck(u8 mask)
{
    return (gSaveContext.biggoronTrades & mask) != 0;
}

u8 SpoilerData_GerudoTokenCheck()
{
    if (gSettingsContext.gerudoFortress == GERUDOFORTRESS_OPEN) {
        // Gerudo token check shouldn't be in the playthrough if the fortress is open, but just in case
        return 1;
    } else {
        // Check all four carpenter rescue flags
        return EventCheck(0x90) != 0 &&
               EventCheck(0x91) != 0 &&
               EventCheck(0x92) != 0 &&
               EventCheck(0x93) != 0;
    }
}

u8 SpoilerData_BigPoePointsCheck()
{
    return gSaveContext.bigPoePoints >= (gSettingsContext.bigPoeTargetCount * 100);
}

u8 SpoilerData_ShopItemCheck(SpoilerItemLocation itemLoc)
{
    u32 itemBit = 1 << itemLoc.LocationFlag;
    return (gSaveContext.sceneFlags[itemLoc.LocationScene].unk & itemBit) != 0;
}

u8 SpoilerData_MagicBeansCheck(SpoilerItemLocation itemLoc)
{
    if (gSettingsContext.shuffleMagicBeans) {
        return SpoilerData_CollectableCheck(itemLoc);
    } else {
        return gSaveContext.magic_beans_available == 10;
    }
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
            return EventCheck(itemLoc.LocationFlag) != 0;
        }
        case SPOILER_CHK_INF_TABLE: { // Check a flag set in event_check_inf
            return SpoilerData_InfTableCheck(itemLoc.LocationScene, itemLoc.LocationFlag);
        }
        case SPOILER_CHK_COW: {
            return SpoilerData_CowCheck(itemLoc);
        }
        case SPOILER_CHK_MINIGAME: {
            return SpoilerData_FishingCheck(itemLoc);
        }
        case SPOILER_CHK_SCRUB: {
            return SpoilerData_ScrubCheck(itemLoc);
        }
        case SPOILER_CHK_BIGGORON: {
            return SpoilerData_BiggoronCheck(itemLoc.LocationFlag);
        }
        case SPOILER_CHK_GERUDO_TOKEN: {
            return SpoilerData_GerudoTokenCheck();
        }
        case SPOILER_CHK_POE_POINTS: {
            return SpoilerData_BigPoePointsCheck();
        }
        case SPOILER_CHK_SHOP_ITEM: {
            return SpoilerData_ShopItemCheck(itemLoc);
        }
        case SPOILER_CHK_MAGIC_BEANS: {
            return SpoilerData_MagicBeansCheck(itemLoc);
        }
        default: {
            return 0;
        }
    }
    return 0;
}
