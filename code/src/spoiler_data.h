#ifndef _SPOILER_DATA_H_
#define _SPOILER_DATA_H_

#include "s_spoiler_data.h"

#include "z3D/z3D.h"

extern SpoilerData gSpoilerData;

SpoilerItemLocation* SpoilerData_ItemLoc(u16 itemIndex);
char* SpoilerData_StringData(u16 itemIndex);

char* SpoilerData_GetItemLocationString(u16 itemIndex);
char* SpoilerData_GetItemNameString(u16 itemIndex);
u8 SpoilerData_GetIsItemLocationCollected(u16 itemIndex);
u8 SpoilerData_ChestCheck(SpoilerItemLocation* itemLoc);
u8 SpoilerData_CollectableCheck(SpoilerItemLocation* itemLoc);
u8 SpoilerData_ItemGetInfCheck(u8 slot);
u8 SpoilerData_InfTableCheck(u8 offset, u8 bit);
u8 SpoilerData_UpgradeCheck(u8 bit);
u8 SpoilerData_CowCheck(SpoilerItemLocation* itemLoc);
u8 SpoilerData_FishingCheck(SpoilerItemLocation* itemLoc);
u8 SpoilerData_ScrubCheck(SpoilerItemLocation* itemLoc);
u8 SpoilerData_BiggoronCheck(u8 mask);
u8 SpoilerData_GerudoTokenCheck();
u8 SpoilerData_BigPoePointsCheck();
u8 SpoilerData_ShopItemCheck(SpoilerItemLocation* itemLoc);
u8 SpoilerData_MagicBeansCheck(SpoilerItemLocation* itemLoc);
u8 SpoilerData_GetIsItemLocationRevealed(u16 itemIndex);

#endif // _SPOILER_DATA_H_
