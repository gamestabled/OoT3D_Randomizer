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
#endif //_SAVEFILE_H_
