#include "item_upgrade.h"

#include "z3D/z3D.h"

u16 ItemUpgrade_None(SaveContext* saveCtx, u16 itemId) {
    return itemId;
}

u16 ItemUpgrade_Hookshot(SaveContext* saveCtx, u16 itemId) {
    switch (saveCtx->items[SLOT_HOOKSHOT]) {
        case ITEM_NONE: return GI_HOOKSHOT; // Hookshot
        default:        return GI_LONGSHOT; // Longshot
    }
}

u16 ItemUpgrade_Strength(SaveContext* saveCtx, u16 itemId) {
    switch ((saveCtx->upgrades >> 6) & 0x7) {
        case 0:  return GI_BRACELET; // Goron Bracelet
        case 1:  return GI_GAUNTLETS_SILVER; // Silver Gauntlets
        default: return GI_GAUNTLETS_GOLD; // Gold Gauntlets
    }
}

u16 ItemUpgrade_BombBag(SaveContext* saveCtx, u16 itemId) {
    switch ((saveCtx->upgrades >> 3) & 0x7) {
        case 0:  return GI_BOMB_BAG_20; // Bomb Bag
        case 1:  return GI_BOMB_BAG_30; // Bigger Bomb Bag
        default: return GI_BOMB_BAG_40; // Biggest Bomb Bag
    }
}

u16 ItemUpgrade_Quiver(SaveContext* saveCtx, u16 itemId) {
    switch (saveCtx->upgrades & 0x7) {
        case 0:  return GI_BOW; // Bow
        case 1:  return GI_QUIVER_40; // Big Quiver
        default: return GI_QUIVER_50; // Biggest Quiver
    }
}

u16 ItemUpgrade_BulletBag(SaveContext* saveCtx, u16 itemId) {
    switch ((saveCtx->upgrades >> 14) & 0x7) {
        case 0:  return GI_SLINGSHOT; // Slingshot
        case 1:  return GI_BULLET_BAG_40; // Bullet Bag (40)
        default: return GI_BULLET_BAG_50; // Bullet Bag (50)
    }
}

u16 ItemUpgrade_Wallet(SaveContext* saveCtx, u16 itemId) {
    switch ((saveCtx->upgrades >> 12) & 0x3) {
        case 0:  return GI_WALLET_ADULT; // Adult's Wallet
        case 1:  return GI_WALLET_GIANT; // Giant's Wallet
        default: return 0xC7; // Tycoon's Wallet
    }
}

u16 ItemUpgrade_Scale(SaveContext* saveCtx, u16 itemId) {
    switch ((saveCtx->upgrades >> 9) & 0x7) {
        case 0:  return GI_SCALE_SILVER; // Silver Scale
        default: return GI_SCALE_GOLD; // Gold Scale
    }
}

u16 ItemUpgrade_Nuts(SaveContext* saveCtx, u16 itemId) {
    switch ((saveCtx->upgrades >> 20) & 0x7) {
        case 0:  return GI_NUT_UPGRADE_30; // 30 Nuts. 0 and 1 are both starting capacity
        case 1:  return GI_NUT_UPGRADE_30; // 30 Nuts
        default: return GI_NUT_UPGRADE_40; // 40 Nuts
    }
}

u16 ItemUpgrade_Sticks(SaveContext* saveCtx, u16 itemId) {
    switch ((saveCtx->upgrades >> 17) & 0x7) {
        case 0:  return GI_STICK_UPGRADE_20; // 20 Sticks. 0 and 1 are both starting capacity
        case 1:  return GI_STICK_UPGRADE_20; // 20 Sticks
        default: return GI_STICK_UPGRADE_30; // 30 Sticks
    }
}

u16 ItemUpgrade_Magic(SaveContext* saveCtx, u16 itemId) {
    switch (saveCtx->magicAcquired) {
        case 0:  return 0xB9; // Single Magic 
        default: return 0xBA; // Double Magic
    }
}

u16 ItemUpgrade_Bombchu(SaveContext* saveCtx, u16 itemId) {
    if (saveCtx->items[SLOT_BOMBCHU] == 0xFF) {
        return GI_BOMBCHUS_20; // Bombchu 20 pack
    }
    if (saveCtx->ammo[SLOT_BOMBCHU] <= 5) {
        return GI_BOMBCHUS_10; // Bombchu 10 pack
    }
    return GI_BOMBCHUS_5; // Bombchu 5 pack
}

u16 ItemUpgrade_Ocarina(SaveContext* saveCtx, u16 itemId) {
    switch (saveCtx->items[SLOT_OCARINA]) {
        case ITEM_NONE: return GI_OCARINA_FAIRY; // Fairy Ocarina
        default: return GI_OCARINA_OOT; // Ocarina of Time
    }
}

u16 ItemUpgrade_ArrowsToRupee(SaveContext* saveCtx, u16 itemId) {
    return (saveCtx->upgrades & 0x7) ? itemId : GI_RUPEE_BLUE; // Blue Rupee
}

u16 ItemUpgrade_BombsToRupee(SaveContext* saveCtx, u16 itemId) {
    return ((saveCtx->upgrades >> 3) & 0x7) ? itemId : GI_RUPEE_BLUE; // Blue Rupee
}

u16 ItemUpgrade_SeedsToRupee(SaveContext* saveCtx, u16 itemId) {
    return ((saveCtx->upgrades >> 14) & 0x7) ? itemId : GI_RUPEE_BLUE; // Blue Rupee
}

u16 ItemUpgrade_LetterToBottle(SaveContext* saveCtx, u16 itemId) {
    if (saveCtx->eventChkInf[3] & 0x0008) // "King Zora Moved Aside" //TODO: check this
        return 0xC8; // Redundant Letter Bottle
    if (saveCtx->items[SLOT_BOTTLE_1] == ITEM_LETTER_RUTO || saveCtx->items[SLOT_BOTTLE_2] == ITEM_LETTER_RUTO
     || saveCtx->items[SLOT_BOTTLE_3] == ITEM_LETTER_RUTO || saveCtx->items[SLOT_BOTTLE_4] == ITEM_LETTER_RUTO)
        return 0xC8; // Redundant Letter Bottle
    return itemId;
}
