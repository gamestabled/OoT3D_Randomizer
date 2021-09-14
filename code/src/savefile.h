#ifndef _SAVEFILE_H_
#define _SAVEFILE_H_

#include "z3D/z3D.h"

u8 SaveFile_GetMedallionCount(void);
u8 SaveFile_GetStoneCount(void);
u8 SaveFile_GetDungeonCount(void);
void SaveFile_SetStartingInventory(void);
void SaveFile_SetTradeItemAsOwned(u8 itemId);
void SaveFile_UnsetTradeItemAsOwned(u8 itemId);
u32 SaveFile_TradeItemIsOwned(u8 itemId);
void SaveFile_SetOwnedTradeItemEquipped(void);
void SaveFile_ResetItemSlotsIfMatchesID(u8 itemSlot);
void SaveFile_InitExtSaveData(u32 fileBaseIndex);
void SaveFile_LoadExtSaveData(u32 saveNumber);
void SaveFile_SaveExtSaveData(u32 saveNumber);

typedef struct {
    u32 playtimeSeconds;
} ExtSaveData;

#ifdef DECLARE_EXTSAVEDATA
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN ExtSaveData gExtSaveData;

#endif //_SAVEFILE_H_
