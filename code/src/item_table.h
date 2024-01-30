#ifndef _ITEM_TABLE_H_
#define _ITEM_TABLE_H_

#include "z3D/z3D.h"

typedef u16 (*upgradeFunc)(SaveContext* saveCtx, u16 itemId);
typedef void (*effectFunc)(SaveContext* saveCtx, s16 arg1, s16 arg2);

typedef struct {
    s8 baseItemId;
    u8 actionId;
    u16 textId;

    u16 objectId;
    s8 objectModelIdx;
    s8 cmabIndex;       // 0xFF if none
    s8 objectModelIdx2; // 0xFF if none
    s8 cmabIndex2;      // 0xFF if none
    s8 special;         /* 0xFF if none. objectMeshIdx for rupees
                                         TexAnim frame for songs
                                         key ID for small keys */
    u8 chestType;

    upgradeFunc upgrade;

    effectFunc effect;
    s16 effectArg1;
    s16 effectArg2;
} ItemRow;

u16 ItemTable_ResolveUpgrades(u16 itemId);
ItemRow* ItemTable_GetItemRow(u16 itemId);
void ItemTable_CallEffect(ItemRow* itemRow);

#endif //_ITEM_TABLE_H_
