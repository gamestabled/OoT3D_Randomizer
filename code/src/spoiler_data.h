#ifndef _SPOILER_DATA_H_
#define _SPOILER_DATA_H_

#include "../include/z3D/z3D.h"

#define SPOILER_SPHERES_MAX                 50
#define SPOILER_ITEMS_MAX                   512
#define SPOILER_STRING_DATA_SIZE            16384

typedef enum {
    SPOILER_CHK_NONE,
    SPOILER_CHK_ALWAYS_COLLECTED,
    SPOILER_CHK_CHEST,
    SPOILER_CHK_COLLECTABLE,
    SPOILER_CHK_GOLD_SKULLTULA,
    SPOILER_CHK_ITEM_GET_INF,
    SPOILER_CHK_EVENT_CHK_INF,
    SPOILER_CHK_INF_TABLE,
    SPOILER_CHK_COW,
    SPOILER_CHK_MINIGAME,
    SPOILER_CHK_SCRUB,
    SPOILER_CHK_BIGGORON,
    SPOILER_CHK_GERUDO_TOKEN,
    SPOILER_CHK_POE_POINTS,
    SPOILER_CHK_SHOP_ITEM,
} SpoilerCollectionCheckType;

typedef struct {
    u16 LocationStrOffset;
    u16 ItemStrOffset;
    SpoilerCollectionCheckType CollectionCheckType;
    u8 LocationScene;
    u8 LocationFlag;
} SpoilerItemLocation;

typedef struct {
    u8 ItemCount;
    u16 ItemLocationsOffset;
} SpoilerSphere;

typedef struct {
    u8 SphereCount;
    u16 ItemLocationsCount;
    SpoilerSphere Spheres[SPOILER_SPHERES_MAX];
    SpoilerItemLocation ItemLocations[SPOILER_ITEMS_MAX];
    u16 SphereItemLocations[SPOILER_ITEMS_MAX];
    char StringData[SPOILER_STRING_DATA_SIZE];
} SpoilerData;

extern SpoilerData gSpoilerData;

char *SpoilerData_GetItemLocationString(u16 itemIndex);
char *SpoilerData_GetItemNameString(u16 itemIndex);
SpoilerItemLocation GetSpoilerItemLocation(u8 sphere, u16 itemIndex);
u8 SpoilerData_GetIsItemLocationCollected(u16 itemIndex);
u8 SpoilerData_ChestCheck(SpoilerItemLocation itemLoc);
u8 SpoilerData_CollectableCheck(SpoilerItemLocation itemLoc);
u8 SpoilerData_ItemGetInfCheck(u8 slot);
u8 SpoilerData_InfTableCheck(u8 offset, u8 bit);
u8 SpoilerData_UpgradeCheck(u8 bit);
u8 SpoilerData_CowCheck(SpoilerItemLocation itemLoc);
u8 SpoilerData_FishingCheck(SpoilerItemLocation itemLoc);
u8 SpoilerData_ScrubCheck(SpoilerItemLocation itemLoc);
u8 SpoilerData_BiggoronCheck();
u8 SpoilerData_GerudoTokenCheck();
u8 SpoilerData_BigPoePointsCheck();
u8 SpoilerData_ShopItemCheck(SpoilerItemLocation itemLoc);

#endif // _SPOILER_DATA_H_