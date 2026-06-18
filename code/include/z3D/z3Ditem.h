#ifndef _Z3D_ITEM_H_
#define _Z3D_ITEM_H_

#include "s_item.h"

typedef enum InventorySlot {
    /* 0x00 */ SLOT_STICK,
    /* 0x01 */ SLOT_NUT,
    /* 0x02 */ SLOT_BOMB,
    /* 0x03 */ SLOT_BOW,
    /* 0x04 */ SLOT_ARROW_FIRE,
    /* 0x05 */ SLOT_DINS_FIRE,
    /* 0x06 */ SLOT_SLINGSHOT,
    /* 0x07 */ SLOT_OCARINA,
    /* 0x08 */ SLOT_BOMBCHU,
    /* 0x09 */ SLOT_HOOKSHOT,
    /* 0x0A */ SLOT_ARROW_ICE,
    /* 0x0B */ SLOT_FARORES_WIND,
    /* 0x0C */ SLOT_BOOMERANG,
    /* 0x0D */ SLOT_LENS,
    /* 0x0E */ SLOT_BEAN,
    /* 0x0F */ SLOT_HAMMER,
    /* 0x10 */ SLOT_ARROW_LIGHT,
    /* 0x11 */ SLOT_NAYRUS_LOVE,
    /* 0x12 */ SLOT_BOTTLE_1,
    /* 0x13 */ SLOT_BOTTLE_2,
    /* 0x14 */ SLOT_BOTTLE_3,
    /* 0x15 */ SLOT_BOTTLE_4,
    /* 0x16 */ SLOT_TRADE_ADULT,
    /* 0x17 */ SLOT_TRADE_CHILD,
    /* 0x18 */ SLOT_IRON_BOOTS,
    /* 0x19 */ SLOT_HOVER_BOOTS,
    /* 0xFF */ SLOT_NONE = 0xFF
} InventorySlot;

typedef enum ExchangeItemID {
    /* 0x00 */ EXCH_ITEM_NONE,
    /* 0x01 */ EXCH_ITEM_LETTER_ZELDA,
    /* 0x02 */ EXCH_ITEM_WEIRD_EGG,
    /* 0x03 */ EXCH_ITEM_CHICKEN,
    /* 0x04 */ EXCH_ITEM_BEAN,
    /* 0x05 */ EXCH_ITEM_POCKET_EGG,
    /* 0x06 */ EXCH_ITEM_POCKET_CUCCO,
    /* 0x07 */ EXCH_ITEM_COJIRO,
    /* 0x08 */ EXCH_ITEM_ODD_MUSHROOM,
    /* 0x09 */ EXCH_ITEM_ODD_POTION,
    /* 0x0A */ EXCH_ITEM_SAW,
    /* 0x0B */ EXCH_ITEM_SWORD_BROKEN,
    /* 0x0C */ EXCH_ITEM_PRESCRIPTION,
    /* 0x0D */ EXCH_ITEM_FROG,
    /* 0x0E */ EXCH_ITEM_EYEDROPS,
    /* 0x0F */ EXCH_ITEM_CLAIM_CHECK,
    /* 0x10 */ EXCH_ITEM_MASK_SKULL,
    /* 0x11 */ EXCH_ITEM_MASK_SPOOKY,
    /* 0x12 */ EXCH_ITEM_MASK_KEATON,
    /* 0x13 */ EXCH_ITEM_MASK_BUNNY,
    /* 0x14 */ EXCH_ITEM_MASK_TRUTH,
    /* 0x15 */ EXCH_ITEM_MASK_GORON,
    /* 0x16 */ EXCH_ITEM_MASK_ZORA,
    /* 0x17 */ EXCH_ITEM_MASK_GERUDO,
    /* 0x18 */ EXCH_ITEM_FISH,
    /* 0x19 */ EXCH_ITEM_BLUE_FIRE,
    /* 0x1A */ EXCH_ITEM_BUG,
    /* 0x1B */ EXCH_ITEM_POE,
    /* 0x1C */ EXCH_ITEM_BIG_POE,
    /* 0x1D */ EXCH_ITEM_LETTER_RUTO,
    /* 0x1E */ EXCH_ITEM_MAX
} ExchangeItemID;

#endif //_Z3D_ITEM_H_
