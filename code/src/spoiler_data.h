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
    SPOILER_CHK_MAGIC_BEANS,
} SpoilerCollectionCheckType;

// Location groups for checks, used to group the checks by logical location
typedef enum {
    GROUP_NO_GROUP,
    GROUP_KOKIRI_FOREST,                                  // 0x55, 0x28
    GROUP_LOST_WOODS,                                     // 0x5B, 0x56
    GROUP_DUNGEON_DEKU_TREE,                              // 0x00, 0x11
    GROUP_DUNGEON_FOREST_TEMPLE,                          // 0x03
    GROUP_KAKARIKO,                                       // 0x37, 0x42, 0x3F, 0x40, 0x41, 0x48, 0x52, 0x53
    GROUP_DUNGEON_BOTTOM_OF_THE_WELL,                     // 0x08
    GROUP_DUNGEON_SHADOW_TEMPLE,                          // 0x07
    GROUP_DEATH_MOUNTAIN,                                 // 0x60, 0x61
    GROUP_GORON_CITY,                                     // 0x62
    GROUP_DUNGEON_DODONGOS_CAVERN,                        // 0x01, 0x12
    GROUP_DUNGEON_FIRE_TEMPLE,                            // 0x04
    GROUP_ZORAS_RIVER,                                    // 0x54
    GROUP_ZORAS_DOMAIN,                                   // 0x58, 0x59
    GROUP_DUNGEON_JABUJABUS_BELLY,                        // 0x02, 0x13
    GROUP_DUNGEON_ICE_CAVERN,                             // 0x09
    GROUP_HYRULE_FIELD,                                   // 0x51
    GROUP_LON_LON_RANCH,                                  // 0x4C
    GROUP_LAKE_HYLIA,                                     // 0x57
    GROUP_DUNGEON_WATER_TEMPLE,                           // 0x05
    GROUP_GERUDO_VALLEY,                                  // 0x5A, 0x5D, 0x0C, 0x5E, 0x5C
    GROUP_GERUDO_TRAINING_GROUND,                         // 0x0B
    GROUP_DUNGEON_SPIRIT_TEMPLE,                          // 0x06
    GROUP_HYRULE_CASTLE,                                  // 0x10, 0x4B, 0x35, 0x42, 0x4D, 0x5F, 0x4A
    GROUP_DUNGEON_GANONS_CASTLE,                          // 0x0A, 0x0D, 0x0E, 0x0F
    SPOILER_COLLECTION_GROUP_COUNT,
    // Grottos are all 0x3E
} SpoilerCollectionCheckGroup;

typedef enum {
    COLLECTTYPE_NORMAL,
    COLLECTTYPE_REPEATABLE,
    COLLECTTYPE_NEVER,
} SpoilerItemCollectType;

typedef enum {
    REVEALTYPE_NORMAL,
    REVEALTYPE_SCENE,
    REVEALTYPE_ALWAYS,
} SpoilerItemRevealType;

typedef struct {
    u16 LocationStrOffset;
    u16 ItemStrOffset;
    SpoilerCollectionCheckType CollectionCheckType;
    u8 LocationScene;
    u8 LocationFlag;
    SpoilerCollectionCheckGroup Group;
    SpoilerItemCollectType CollectType;
    SpoilerItemRevealType RevealType;
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
    u16 GroupItemCounts[SPOILER_COLLECTION_GROUP_COUNT];
    u16 GroupOffsets[SPOILER_COLLECTION_GROUP_COUNT];
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
u8 SpoilerData_BiggoronCheck(u8 mask);
u8 SpoilerData_GerudoTokenCheck();
u8 SpoilerData_BigPoePointsCheck();
u8 SpoilerData_ShopItemCheck(SpoilerItemLocation itemLoc);
u8 SpoilerData_MagicBeansCheck(SpoilerItemLocation itemLoc);
u8 SpoilerData_GetIsItemLocationRevealed(u16 itemIndex);

#endif // _SPOILER_DATA_H_