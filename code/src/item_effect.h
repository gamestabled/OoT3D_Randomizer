#ifndef _ITEM_EFFECT_H_
#define _ITEM_EFFECT_H_

#include "icetrap.h"

#include "z3D/z3D.h"

void ItemEffect_None(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_FullHeal(SaveContext* saveCtx, s16 arg1, s16 arg2);
// void give_triforce_piece(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_GiveTycoonWallet(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_GiveBiggoronSword(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_GiveBottle(SaveContext* saveCtx, s16 bottleItemId, s16 arg2);
void ItemEffect_GiveDungeonItem(SaveContext* saveCtx, s16 mask, s16 dungeonId);
void ItemEffect_GiveSmallKey(SaveContext* saveCtx, s16 dungeonId, s16 arg2);
void ItemEffect_GiveSmallKeyRing(SaveContext* saveCtx, s16 dungeonId, s16 arg2);
void ItemEffect_GiveDefense(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_GiveMagic(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_GiveDoubleMagic(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_GiveFairyOcarina(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_GiveSong(SaveContext* saveCtx, s16 questBit, s16 arg2);
void ItemEffect_GiveUpgrade(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_IceTrap(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_GiveMasterSword(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_BeanPack(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_RupeeAmmo(SaveContext* saveCtx);
void ItemEffect_FillWalletUpgrade(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_OpenMaskShop(SaveContext* saveCtx, s16 arg1, s16 arg2);
void PushSlotIntoInventoryMenu(u8 itemSlot);
void ItemEffect_PlaceMagicArrowsInInventory(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_GiveChildKokiriSword(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_GiveStone(SaveContext* saveCtx, s16 mask, s16 arg2);
void ItemEffect_GiveMedallion(SaveContext* saveCtx, s16 mask, s16 arg2);
void ItemEffect_MoveNabooru(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_GrannySellsPotions(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_OwnAdultTrade(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_GiveWeirdEgg(SaveContext* saveCtx, s16 arg1, s16 arg2);
void ItemEffect_ShardOfAgony(SaveContext* saveCtx, s16 arg1, s16 arg2);
#endif //_ITEM_EFFECT_H_
