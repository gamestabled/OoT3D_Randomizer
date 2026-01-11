#ifndef _SAVEFILE_H_
#define _SAVEFILE_H_

#include "z3D/z3D.h"
#include "z3D/z3Dscene.h"

#define SAVEFILE_SCENES_DISCOVERED_IDX_COUNT 4
#define SAVEFILE_ENTRANCES_DISCOVERED_IDX_COUNT 66

u8 SaveFile_GetMedallionCount(void);
u8 SaveFile_GetStoneCount(void);
u8 SaveFile_GetDungeonCount(void);
u8 SaveFile_GetIsSceneDiscovered(u8 sceneNum);
void SaveFile_SetSceneDiscovered(u8 sceneNum);
u8 SaveFile_GetIsEntranceDiscovered(u16 entranceIndex);
void SaveFile_SetEntranceDiscovered(u16 entranceIndex);
void SaveFile_SetStartingInventory(void);
void SaveFile_SetTradeItemAsOwned(u8 itemId);
void SaveFile_UnsetTradeItemAsOwned(u8 itemId);
u32 SaveFile_TradeItemIsOwned(u8 itemId);
u8 SaveFile_ChildTradeSlots(void);
u8 SaveFile_WeirdEggHatched(void);
u8 SaveFile_CurrentMask(void);
u32 SaveFile_MaskSlotValue(void);
void SaveFile_BorrowMask(s16 SI_ItemId);
void SaveFile_SetOwnedTradeItemEquipped(void);
void SaveFile_ResetItemSlotsIfMatchesID(u8 itemSlot);
u8 SaveFile_InventoryMenuHasSlot(u8 adult, u8 itemSlot);
void SaveFile_InitExtSaveData(u32 fileBaseIndex, u8 fromSaveCreation);
void SaveFile_LoadExtSaveData(u32 saveNumber);
void SaveFile_SaveExtSaveData(u32 saveNumber);
void SaveFile_EnforceHealthLimit(void);
u8 SaveFile_SwordlessPatchesEnabled(void);
void SaveFile_SetRupeeSanityFlag(s16 sceneNum, u16 collectibleFlag);
u8 SaveFile_GetRupeeSanityFlag(s16 sceneNum, u16 collectibleFlag);

// Increment the version number whenever the ExtSaveData structure is changed
#define EXTSAVEDATA_VERSION 17

typedef struct ExtInf {
    u8 biggoronTrades;
    u8 masterSwordFlags;
    u8 totAltarFlags;
    u8 enemySouls[8];
    u8 ocarinaButtons;
} ExtInf;

#define EXTINF_SIZE sizeof(ExtInf)

typedef struct {
    u32 version; // Needs to always be the first field of the structure
    union {
        ExtInf extInf; // Used for various bit flags that should also be synced in multiplayer with shared progress
        u8 extInfArray[EXTINF_SIZE]; // Used only by multiplayer code for easier management of bit flags
    };
    struct {
        Vec3i pos;
        s32 yaw;
        s32 playerParams;
        s32 entranceIndex;
        s32 roomIndex;
        s32 set;
        s32 tempSwchFlags;
        s32 tempCollectFlags;
    } fwStored;
    u32 playtimeSeconds;
    u32 scenesDiscovered[SAVEFILE_SCENES_DISCOVERED_IDX_COUNT];
    u32 entrancesDiscovered[SAVEFILE_ENTRANCES_DISCOVERED_IDX_COUNT];
    u32 rupeesanityFlags[SCENE_MAX];
    u32 rupeesanityRupeeCircleFlags[SCENE_MAX];
    u8 hasTimeTraveled;
    u8 permadeath;
    u8 gloomedHeart;
    u8 triforcePieces;
    // Ingame Options, all need to be s8
    s8 option_EnableBGM;
    s8 option_EnableSFX;
    s8 option_NaviNotifications;
    s8 option_IgnoreMaskReaction;
    s8 option_SkipSongReplays;
    s8 option_FreeCamControl;
} ExtSaveData;

#ifdef DECLARE_EXTSAVEDATA
    #define EXTERN
#else
    #define EXTERN extern
#endif

EXTERN ExtSaveData gExtSaveData;

#endif //_SAVEFILE_H_
