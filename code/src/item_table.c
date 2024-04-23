#include "item_table.h"
#include "item_upgrade.h"
#include "item_effect.h"
#include "enemy_souls.h"
#include "rHeap.h"
#include "chest.h"
#include "ocarina_notes.h"
#include <stddef.h>

#define ITEM_ROW(baseItemId_, chestType_, actionId_, textId_, objectId_, objectModelIdx_, cmabIndex_,             \
                 objectModelIdx2_, cmabIndex2_, special_, upgrade_, effect_, effectArg1_, effectArg2_)            \
    {                                                                                                             \
        .baseItemId = baseItemId_, .chestType = chestType_, .actionId = actionId_, .textId = textId_,             \
        .objectId = objectId_, .objectModelIdx = objectModelIdx_, .cmabIndex = cmabIndex_,                        \
        .objectModelIdx2 = objectModelIdx2_, .cmabIndex2 = cmabIndex2_, .special = special_, .upgrade = upgrade_, \
        .effect = effect_, .effectArg1 = effectArg1_, .effectArg2 = effectArg2_                                   \
    }

/*
From OoTR:
    `The "base item" mostly controls the sound effect made when you receive the item. It should be
    set to something that doesn't break NPCs. Good options include:
    0x53 = Gerudo Mask (major item sound effect)
    0x4D = Blue Rupee (minor item sound effect)

    Action ID 0x41 (give kokiri tunic) is used to indicate no action.`

The following values are used to render both overworld models and GI models above Link's head
    objectId:        index for the ZAR file containing the model data (CMBs and CMABs);
    objectModelIdx:  index for the CMB to use as the base model;
    cmabIndex:       index for the CMAB texture to apply to the base model (optional, 0xFF if none);
    objectModelIdx2: index for the CMB to use as the second model (optional, 0xFF if none);
    cmabIndex2:      index for the CMAB texture to apply to the second model (optional, 0xFF if none);
    special:         value used for different purposes for some custom models.

The second model, if present, will face the camera by default (because it's a 2D billboard like the
fairy orb in the bottle). Exceptions to this can be added in Model_UpdateMatrix.
*/

// clang-format off
static ItemRow rItemTable[] = {
    [GI_BOMBS_5]            = ITEM_ROW(0x4D, CHEST_JUNK,      0x8E, 0x0032,   0x00CE, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_BombsToRupee, ItemEffect_None, -1, -1), // Bombs (5)
    [GI_NUTS_5]             = ITEM_ROW(0x4D, CHEST_JUNK,      0x8C, 0x0034,   0x00BB, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Deku Nuts (5)
    [GI_BOMBCHUS_10]        = ITEM_ROW(0x4D, CHEST_BOMBCHUS,  0x09, 0x0033,   0x00D9, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Bombchu (10)
    [GI_BOW]                = ITEM_ROW(0x53, CHEST_MAJOR,     0x03, 0x0031,   0x00E9, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_PlaceMagicArrowsInInventory, 0, -1), // Fairy Bow
    [GI_SLINGSHOT]          = ITEM_ROW(0x53, CHEST_MAJOR,     0x06, 0x0030,   0x00E7, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Fairy Slingshot
    [GI_BOOMERANG]          = ITEM_ROW(0x53, CHEST_MAJOR,     0x0E, 0x0035,   0x00E8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Boomerang
    [GI_STICKS_1]           = ITEM_ROW(0x4D, CHEST_JUNK,      0x00, 0x0037,   0x00C7, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Deku Stick
    [GI_HOOKSHOT]           = ITEM_ROW(0x53, CHEST_MAJOR,     0x0A, 0x0036,   0x00DD, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Hookshot
    [GI_LONGSHOT]           = ITEM_ROW(0x53, CHEST_MAJOR,     0x0B, 0x004F,   0x00DD, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Longshot
    [GI_LENS]               = ITEM_ROW(0x53, CHEST_MAJOR,     0x0F, 0x0039,   0x00EA, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Lens of Truth
    [GI_LETTER_ZELDA]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x23, 0x0069,   0x00EF, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_OpenMaskShop, -1, -1), // Zelda's Letter
    [GI_OCARINA_OOT]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x08, 0x003A,   0x00DE, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Ocarina of Time
    [GI_HAMMER]             = ITEM_ROW(0x53, CHEST_MAJOR,     0x11, 0x0038,   0x00F6, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Megaton Hammer
    [GI_COJIRO]             = ITEM_ROW(0x53, CHEST_MAJOR,     0x2F, 0x0002,   0x0109, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_OwnAdultTrade, 47, -1), // Cojiro
    [GI_BOTTLE]             = ITEM_ROW(0x53, CHEST_MAJOR,     0x14, 0x0042,   0x00C6, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Empty Bottle
    [GI_POTION_RED]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x15, 0x0043,   0x00EB, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Red Potion
    [GI_POTION_GREEN]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x16, 0x0044,   0x00EB, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Green Potion
    [GI_POTION_BLUE]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x17, 0x0045,   0x00EB, 0x02, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Blue Potion
    [GI_FAIRY]              = ITEM_ROW(0x53, CHEST_MAJOR,     0x18, 0x0046,   0x00C6, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Bottled Fairy
    [GI_MILK_BOTTLE]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x1A, 0x0098,   0x00DF, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Bottled Lon Lon Milk
    [GI_LETTER_RUTO]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x1B, 0x0099,   0x010B, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_LetterToBottle, ItemEffect_None, -1, -1), // Bottled Ruto's Letter
    [GI_BEAN]               = ITEM_ROW(0x53, CHEST_JUNK,      0x10, 0x0048,   0x00F3, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Magic Bean
    [GI_MASK_SKULL]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x25, 0x0010,   0x0136, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Skull Mask
    [GI_MASK_SPOOKY]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x26, 0x0011,   0x0135, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Spooky Mask
    [GI_CHICKEN]            = ITEM_ROW(0x53, CHEST_MAJOR,     0x22, 0x000B,   0x0109, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Chicken
    [GI_MASK_KEATON]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x24, 0x0012,   0x0134, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Keaton Mask
    [GI_MASK_BUNNY]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x27, 0x0013,   0x0137, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Bunny Hood
    [GI_MASK_TRUTH]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x2B, 0x0017,   0x0138, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Mask of Truth
    [GI_POCKET_EGG]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x2D, 0x0001,   0x00DA, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_OwnAdultTrade, 45, -1), // Pocket Egg
    [GI_POCKET_CUCCO]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x2E, 0x0002,   0x0109, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_OwnAdultTrade, 46, -1), // Pocket Cucco
    [GI_ODD_MUSHROOM]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x30, 0x0003,   0x0141, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_OwnAdultTrade, 48, -1), // Odd Mushroom
    [GI_ODD_POTION]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x31, 0x0004,   0x0140, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_OwnAdultTrade, 49, -1), // Odd Potion
    [GI_SAW]                = ITEM_ROW(0x53, CHEST_MAJOR,     0x32, 0x0005,   0x00F5, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_OwnAdultTrade, 50, -1), // Poacher's Saw
    [GI_SWORD_BROKEN]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x33, 0x0008,   0x0143, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_OwnAdultTrade, 51, -1), // Goron's Sword (Broken)
    [GI_PERSCRIPTION]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x34, 0x0009,   0x0146, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_OwnAdultTrade, 52, -1), // Prescription
    [GI_FROG]               = ITEM_ROW(0x53, CHEST_MAJOR,     0x35, 0x000D,   0x0149, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_OwnAdultTrade, 53, -1), // Eyeball Frog
    [GI_EYEDROPS]           = ITEM_ROW(0x53, CHEST_MAJOR,     0x36, 0x000E,   0x013F, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_OwnAdultTrade, 54, -1), // Eye Drops
    [GI_CLAIM_CHECK]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x37, 0x000A,   0x0142, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_OwnAdultTrade, 55, -1), // Claim Check
    [GI_SWORD_KOKIRI]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x3B, 0x00A4,   0x018D, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveChildKokiriSword, -1, -1), // Kokiri Sword
    [GI_SWORD_KNIFE]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x3D, 0x004B,   0x00F8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Giant's Knife
    [GI_SHIELD_DEKU]        = ITEM_ROW(0x53, CHEST_JUNK,      0x3E, 0x004C,   0x00CB, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Deku Shield
    [GI_SHIELD_HYLIAN]      = ITEM_ROW(0x53, CHEST_JUNK,      0x3F, 0x004D,   0x00DC, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Hylian Shield
    [GI_SHIELD_MIRROR]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x40, 0x004E,   0x00EE, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Mirror Shield
    [GI_TUNIC_GORON]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x42, 0x0050,   0x00F2, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Goron Tunic
    [GI_TUNIC_ZORA]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x43, 0x0051,   0x00F2, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Zora Tunic
    [GI_BOOTS_IRON]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x45, 0x0053,   0x0118, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Iron Boots
    [GI_BOOTS_HOVER]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x46, 0x0054,   0x0157, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Hover Boots
    [GI_QUIVER_40]          = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0056,   0x00BE, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveUpgrade, 2, 0), // Big Quiver
    [GI_QUIVER_50]          = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0057,   0x00BE, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveUpgrade, 3, 0), // Biggest Quiver
    [GI_BOMB_BAG_20]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x4D, 0x0058,   0x00BF, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Bomb Bag
    [GI_BOMB_BAG_30]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0059,   0x00BF, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveUpgrade, 2, 1), // Big Bomb Bag
    [GI_BOMB_BAG_40]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x005A,   0x00BF, 0x02, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveUpgrade, 3, 1), // Biggest Bomb Bag
    [GI_GAUNTLETS_SILVER]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x51, 0x005B,   0x012D, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_MoveNabooru, -1, -1), // Silver Gauntlets
    [GI_GAUNTLETS_GOLD]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x52, 0x005C,   0x012D, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Golden Gauntlets
    [GI_SCALE_SILVER]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x53, 0x00CD,   0x00DB, 0x00, 0x00, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Silver Scale
    [GI_SCALE_GOLD]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x54, 0x00CE,   0x00DB, 0x01, 0x01, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Golden Scale
    [GI_STONE_OF_AGONY]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x6F, 0x0068,   0x00C8, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_ShardOfAgony, -1, -1), // Shard of Agony
    [GI_GERUDO_CARD]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x70, 0x007B,   0x00D7, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Gerudo Token
    [GI_OCARINA_FAIRY]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x004A,   0x010E, 0x02, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveFairyOcarina, -1, -1), // Fairy Ocarina
    [GI_SEEDS_5]            = ITEM_ROW(0x4D, CHEST_JUNK,      0x58, 0x00DC,   0x0119, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_SeedsToRupee, ItemEffect_None, -1, -1), // Deku Seeds (5)
    [GI_HEART_CONTAINER]    = ITEM_ROW(0x3D, CHEST_HEART,     0x72, 0x00C6,   0x00BD, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_HealthToRupee, ItemEffect_FullHeal, -1, -1), // Heart Container
    [GI_HEART_PIECE]        = ITEM_ROW(0x3E, CHEST_HEART,     0x7A, 0x00C2,   0x00BD, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_HealthToRupee, ItemEffect_FullHeal, -1, -1), // Piece of Heart
    [GI_KEY_BOSS]           = ITEM_ROW(0x53, CHEST_BOSS_KEY,  0x74, 0x00C7,   0x00B9, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Boss Key
    [GI_COMPASS]            = ITEM_ROW(0x53, CHEST_JUNK,      0x75, 0x0067,   0x00B8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Compass
    [GI_MAP]                = ITEM_ROW(0x53, CHEST_JUNK,      0x76, 0x0066,   0x00C8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Map
    [GI_KEY_SMALL]          = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x77, 0x0060,   0x00AA, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Small Key
    [GI_MAGIC_SMALL]        = ITEM_ROW(0x53, CHEST_JUNK,      0x78, 0x0052,   0x00CD, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Small Magic Jar
    [GI_MAGIC_LARGE]        = ITEM_ROW(0x53, CHEST_JUNK,      0x79, 0x0052,   0x00CD, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Large Magic Jar
    [GI_WALLET_ADULT]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x56, 0x005E,   0x00D1, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_FillWalletUpgrade, 1, -1), // Adult's Wallet
    [GI_WALLET_GIANT]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x57, 0x005F,   0x00D1, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_FillWalletUpgrade, 2, -1), // Giant's Wallet
    [GI_WEIRD_EGG]          = ITEM_ROW(0x53, CHEST_MAJOR,     0x21, 0x009A,   0x00DA, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveWeirdEgg, -1, -1), // Weird Egg
    [GI_HEART]              = ITEM_ROW(0x4D, CHEST_HEART,     0x83, 0x0055,   0x00B7, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Recovery Heart
    [GI_ARROWS_SMALL]       = ITEM_ROW(0x4D, CHEST_JUNK,      0x92, 0x00E6,   0x00D8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_ArrowsToRupee, ItemEffect_None, -1, -1), // Arrows (5)
    [GI_ARROWS_MEDIUM]      = ITEM_ROW(0x4D, CHEST_JUNK,      0x93, 0x00E6,   0x00D8, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_ArrowsToRupee, ItemEffect_None, -1, -1), // Arrows (10)
    [GI_ARROWS_LARGE]       = ITEM_ROW(0x4D, CHEST_JUNK,      0x94, 0x00E6,   0x00D8, 0x02, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_ArrowsToRupee, ItemEffect_None, -1, -1), // Arrows (30)
    [GI_RUPEE_GREEN]        = ITEM_ROW(0x4D, CHEST_JUNK,      0x84, 0x006F,   0x017F, 0x00, 0xFF, 0xFF, 0xFF,   0x6C, ItemUpgrade_None, ItemEffect_None, -1, -1), // Green Rupee
    [GI_RUPEE_BLUE]         = ITEM_ROW(0x4D, CHEST_JUNK,      0x85, 0x00CC,   0x017F, 0x00, 0xFF, 0xFF, 0xFF,   0x6D, ItemUpgrade_None, ItemEffect_None, -1, -1), // Blue Rupee
    [GI_RUPEE_RED]          = ITEM_ROW(0x4D, CHEST_JUNK,      0x86, 0x00F0,   0x017F, 0x00, 0xFF, 0xFF, 0xFF,   0x6E, ItemUpgrade_None, ItemEffect_None, -1, -1), // Red Rupee
    [GI_HEART_CONTAINER_2]  = ITEM_ROW(0x3D, CHEST_HEART,     0x72, 0x00C6,   0x00BD, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_HealthToRupee, ItemEffect_FullHeal, -1, -1), // Heart Container
    [GI_MILK]               = ITEM_ROW(0x53, CHEST_MAJOR,     0x82, 0x0098,   0x00DF, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Lon Lon Milk (Refill)
    [GI_MASK_GORON]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x28, 0x0014,   0x0150, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Goron Mask
    [GI_MASK_ZORA]          = ITEM_ROW(0x53, CHEST_MAJOR,     0x29, 0x0015,   0x0151, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Zora Mask
    [GI_MASK_GERUDO]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x2A, 0x0016,   0x0152, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Gerudo Mask
    [GI_BRACELET]           = ITEM_ROW(0x53, CHEST_MAJOR,     0x50, 0x0079,   0x0147, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Goron's Bracelet
    [GI_RUPEE_PURPLE]       = ITEM_ROW(0x4D, CHEST_JUNK,      0x87, 0x00F1,   0x017F, 0x00, 0xFF, 0xFF, 0xFF,   0x70, ItemUpgrade_None, ItemEffect_None, -1, -1), // Purple Rupee
    [GI_RUPEE_GOLD]         = ITEM_ROW(0x4D, CHEST_JUNK,      0x88, 0x00F2,   0x017F, 0x00, 0xFF, 0xFF, 0xFF,   0x71, ItemUpgrade_None, ItemEffect_None, -1, -1), // Huge Rupee
    [GI_SWORD_BGS]          = ITEM_ROW(0x53, CHEST_MAJOR,     0x3D, 0x000C,   0x00F8, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveBiggoronSword, -1, -1), // Biggoron's Sword
    [GI_ARROW_FIRE]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x04, 0x0070,   0x0158, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_PlaceMagicArrowsInInventory, 1, -1), // Fire Arrow
    [GI_ARROW_ICE]          = ITEM_ROW(0x53, CHEST_MAJOR,     0x0C, 0x0071,   0x0158, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_PlaceMagicArrowsInInventory, 2, -1), // Ice Arrow
    [GI_ARROW_LIGHT]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x12, 0x0072,   0x0158, 0x02, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_PlaceMagicArrowsInInventory, 3, -1), // Light Arrow
    [GI_SKULL_TOKEN]        = ITEM_ROW(0x5B, CHEST_SKULL,     0x71, 0x00B4,   0x015C, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_TokenToRupee, ItemEffect_None, -1, -1), // Gold Skulltula Token
    [GI_DINS_FIRE]          = ITEM_ROW(0x53, CHEST_MAJOR,     0x05, 0x00AD,   0x015D, 0x00, 0x00, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Din's Fire
    [GI_FARORES_WIND]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x0D, 0x00AE,   0x015D, 0x01, 0x01, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Farore's Wind
    [GI_NAYRUS_LOVE]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x13, 0x00AF,   0x015D, 0x02, 0x02, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Nayru's Love
    [GI_BULLET_BAG_30]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x47, 0x0007,   0x017B, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Bullet Bag (30)
    [GI_BULLET_BAG_40]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0007,   0x017B, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveUpgrade, 2, 5), // Bullet Bag (40)
    [GI_STICKS_5]           = ITEM_ROW(0x4D, CHEST_JUNK,      0x8A, 0x0037,   0x00C7, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Deku Sticks (5)
    [GI_STICKS_10]          = ITEM_ROW(0x4D, CHEST_JUNK,      0x8B, 0x0037,   0x00C7, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Deku Sticks (10)
    [GI_NUTS_5_2]           = ITEM_ROW(0x4D, CHEST_JUNK,      0x8C, 0x0034,   0x00BB, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Deku Nuts (5)
    [GI_NUTS_10]            = ITEM_ROW(0x4D, CHEST_JUNK,      0x8D, 0x0034,   0x00BB, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Deku Nuts (10)
    [GI_BOMBS_1]            = ITEM_ROW(0x4D, CHEST_JUNK,      0x02, 0x0032,   0x00CE, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_BombsToRupee, ItemEffect_None, -1, -1), // Bomb
    [GI_BOMBS_10]           = ITEM_ROW(0x4D, CHEST_JUNK,      0x8F, 0x0032,   0x00CE, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_BombsToRupee, ItemEffect_None, -1, -1), // Bombs (10)
    [GI_BOMBS_20]           = ITEM_ROW(0x4D, CHEST_JUNK,      0x90, 0x0032,   0x00CE, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_BombsToRupee, ItemEffect_None, -1, -1), // Bombs (20)
    [GI_BOMBS_30]           = ITEM_ROW(0x4D, CHEST_JUNK,      0x91, 0x0032,   0x00CE, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_BombsToRupee, ItemEffect_None, -1, -1), // Bombs (30)
    [GI_SEEDS_30]           = ITEM_ROW(0x4D, CHEST_JUNK,      0x95, 0x00DC,   0x0119, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_SeedsToRupee, ItemEffect_None, -1, -1), // Deku Seeds (30)
    [GI_BOMBCHUS_5]         = ITEM_ROW(0x4D, CHEST_BOMBCHUS,  0x96, 0x0033,   0x00D9, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Bombchu (5)
    [GI_BOMBCHUS_20]        = ITEM_ROW(0x4D, CHEST_BOMBCHUS,  0x97, 0x0033,   0x00D9, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Bombchu (20)
    [GI_FISH]               = ITEM_ROW(0x53, CHEST_MAJOR,     0x19, 0x0047,   0x00F4, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Fish (Refill)
    [GI_BUGS]               = ITEM_ROW(0x53, CHEST_MAJOR,     0x1D, 0x007A,   0x0174, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Bugs (Refill)
    [GI_BLUE_FIRE]          = ITEM_ROW(0x53, CHEST_MAJOR,     0x1C, 0x005D,   0x0173, 0x00, 0x00, 0x01, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Blue Fire (Refill)
    [GI_POE]                = ITEM_ROW(0x53, CHEST_MAJOR,     0x20, 0x0097,   0x0176, 0x01, 0xFF, 0x00, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Poe (Refill)
    [GI_BIG_POE]            = ITEM_ROW(0x53, CHEST_MAJOR,     0x1E, 0x00F9,   0x019A, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Big Poe (Refill)
    [GI_DOOR_KEY]           = ITEM_ROW(0x53, CHEST_JUNK,      0x77, 0x00F3,   0x00AA, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None, -1, -1), // Small Key (Chest Game)
    [GI_RUPEE_GREEN_LOSE]   = ITEM_ROW(0x4D, CHEST_JUNK,      0x84, 0x00F4,   0x017F, 0x00, 0xFF, 0xFF, 0xFF,   0x6C, ItemUpgrade_None, ItemEffect_None, -1, -1), // Green Rupee (Chest Game)
    [GI_RUPEE_BLUE_LOSE]    = ITEM_ROW(0x4D, CHEST_JUNK,      0x85, 0x00F5,   0x017F, 0x00, 0xFF, 0xFF, 0xFF,   0x6D, ItemUpgrade_None, ItemEffect_None, -1, -1), // Blue Rupee (Chest Game)
    [GI_RUPEE_RED_LOSE]     = ITEM_ROW(0x4D, CHEST_JUNK,      0x86, 0x00F6,   0x017F, 0x00, 0xFF, 0xFF, 0xFF,   0x6E, ItemUpgrade_None, ItemEffect_None, -1, -1), // Red Rupee (Chest Game)
    [GI_RUPEE_PURPLE_LOSE]  = ITEM_ROW(0x4D, CHEST_JUNK,      0x87, 0x00F7,   0x017F, 0x00, 0xFF, 0xFF, 0xFF,   0x70, ItemUpgrade_None, ItemEffect_None, -1, -1), // Purple Rupee (Chest Game)
    [GI_HEART_PIECE_WIN]    = ITEM_ROW(0x53, CHEST_HEART,     0x7A, 0x00FA,   0x00BD, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_HealthToRupee, ItemEffect_FullHeal, -1, -1), // Piece of Heart (Chest Game)
    [GI_STICK_UPGRADE_20]   = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x0090,   0x00C7, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveUpgrade, 2, 6), // Deku Stick Upgrade (20)
    [GI_STICK_UPGRADE_30]   = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x0091,   0x00C7, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveUpgrade, 3, 6), // Deku Stick Upgrade (30)
    [GI_NUT_UPGRADE_30]     = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x00A7,   0x00BB, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveUpgrade, 2, 7), // Deku Nut Upgrade (30)
    [GI_NUT_UPGRADE_40]     = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x00A8,   0x00BB, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveUpgrade, 3, 7), // Deku Nut Upgrade (40)
    [GI_BULLET_BAG_50]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x006C,   0x017B, 0x02, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveUpgrade, 3, 5), // Bullet Bag (50)
    [GI_ICE_TRAP]           = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9002,   0x0000, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_IceTrap, -1, -1), // Ice Trap

    [GI_SWORD_MASTER]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x3C, 0x9309,   0x0195, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveMasterSword, -1, -1), // Master Sword

    [GI_PROG_HOOKSHOT]      = ITEM_ROW(  -1, CHEST_MAJOR,       -1,     -1,   0x00DD, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_Hookshot,  ItemEffect_None, -1, -1), // Progressive Hookshot
    [GI_PROG_STRENGTH]      = ITEM_ROW(  -1, CHEST_MAJOR,       -1,     -1,   0x0147, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_Strength,  ItemEffect_None, -1, -1), // Progressive Strength
    [GI_PROG_BOMB_BAG]      = ITEM_ROW(  -1, CHEST_MAJOR,       -1,     -1,   0x00BF, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_BombBag,   ItemEffect_None, -1, -1), // Progressive Bomb Bag
    [GI_PROG_BOW]           = ITEM_ROW(  -1, CHEST_MAJOR,       -1,     -1,   0x00E9, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_Quiver,    ItemEffect_None, -1, -1), // Progressive Bow
    [GI_PROG_SLINGSHOT]     = ITEM_ROW(  -1, CHEST_MAJOR,       -1,     -1,   0x00E7, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_BulletBag, ItemEffect_None, -1, -1), // Progressive Slingshot
    [GI_PROG_WALLET]        = ITEM_ROW(  -1, CHEST_MAJOR,       -1,     -1,   0x00D1, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_Wallet,    ItemEffect_None, -1, -1), // Progressive Wallet
    [GI_PROG_SCALE]         = ITEM_ROW(  -1, CHEST_MAJOR,       -1,     -1,   0x00DB, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_Scale,     ItemEffect_None, -1, -1), // Progressive Scale
    [GI_PROG_NUT_UPGRADE]   = ITEM_ROW(  -1, CHEST_JUNK,        -1,     -1,   0x00BB, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_Nuts,      ItemEffect_None, -1, -1), // Progressive Nut Capacity
    [GI_PROG_STICK_UPGRADE] = ITEM_ROW(  -1, CHEST_JUNK,        -1,     -1,   0x00C7, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_Sticks,    ItemEffect_None, -1, -1), // Progressive Stick Capacity
    [GI_PROG_BOMBCHUS]      = ITEM_ROW(  -1, CHEST_BOMBCHUS,    -1,     -1,   0x00D9, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_Bombchu,   ItemEffect_None, -1, -1), // Progressive Bombchus
    [GI_PROG_MAGIC_METER]   = ITEM_ROW(  -1, CHEST_MAJOR,       -1,     -1,   0x00CD, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_Magic,     ItemEffect_None, -1, -1), // Progressive Magic Meter
    [GI_PROG_OCARINA]       = ITEM_ROW(  -1, CHEST_MAJOR,       -1,     -1,   0x010E, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_Ocarina,   ItemEffect_None, -1, -1), // Progressive Ocarina

    [GI_BOTTLE_RED_POTION]  = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0043,   0x0199, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveBottle, 0x15, -1), // Bottle with Red Potion
    [GI_BOTTLE_GREEN_POTION]= ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0044,   0x0199, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveBottle, 0x16, -1), // Bottle with Green Potion
    [GI_BOTTLE_BLUE_POTION] = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0045,   0x0199, 0x02, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveBottle, 0x17, -1), // Bottle with Blue Potion
    [GI_BOTTLE_FAIRY]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0046,   0x0177, 0x02, 0xFF, 0x03, 0x01,   0xFF, ItemUpgrade_None, ItemEffect_GiveBottle, 0x18, -1), // Bottle with Fairy
    [GI_BOTTLE_FISH]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0047,   0x00F4, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveBottle, 0x19, -1), // Bottle with Fish
    [GI_BOTTLE_BLUE_FIRE]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x005D,   0x0173, 0x02, 0xFF, 0x03, 0x01,   0xFF, ItemUpgrade_None, ItemEffect_GiveBottle, 0x1C, -1), // Bottle with Blue Fire
    [GI_BOTTLE_BUGS]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x007A,   0x0174, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveBottle, 0x1D, -1), // Bottle with Bugs
    [GI_BOTTLE_BIG_POE]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x00F9,   0x019A, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_GiveBottle, 0x1E, -1), // Bottle with Big Poe
    [GI_BOTTLE_POE]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0097,   0x0176, 0x02, 0xFF, 0x03, 0x01,   0xFF, ItemUpgrade_None, ItemEffect_GiveBottle, 0x20, -1), // Bottle with Poe

    [GI_FOREST_BOSS_KEY]    = ITEM_ROW(0x53, CHEST_BOSS_KEY,  0x41, 0x09D4,   0x0080, 0x00, 0xFF, 0xFF, 0xFF,   0x00, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x01, DUNGEON_FOREST_TEMPLE ), // Forest Temple Boss Key
    [GI_FIRE_BOSS_KEY]      = ITEM_ROW(0x53, CHEST_BOSS_KEY,  0x41, 0x09D5,   0x0080, 0x00, 0xFF, 0xFF, 0xFF,   0x01, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x01, DUNGEON_FIRE_TEMPLE   ), // Fire Temple Boss Key
    [GI_WATER_BOSS_KEY]     = ITEM_ROW(0x53, CHEST_BOSS_KEY,  0x41, 0x09D6,   0x0080, 0x00, 0xFF, 0xFF, 0xFF,   0x02, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x01, DUNGEON_WATER_TEMPLE  ), // Water Temple Boss Key
    [GI_SPIRIT_BOSS_KEY]    = ITEM_ROW(0x53, CHEST_BOSS_KEY,  0x41, 0x09D7,   0x0080, 0x00, 0xFF, 0xFF, 0xFF,   0x04, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x01, DUNGEON_SPIRIT_TEMPLE ), // Spirit Temple Boss Key
    [GI_SHADOW_BOSS_KEY]    = ITEM_ROW(0x53, CHEST_BOSS_KEY,  0x41, 0x09D8,   0x0080, 0x00, 0xFF, 0xFF, 0xFF,   0x03, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x01, DUNGEON_SHADOW_TEMPLE ), // Shadow Temple Boss Key
    [GI_GANON_BOSS_KEY]     = ITEM_ROW(0x53, CHEST_BOSS_KEY,  0x41, 0x09D9,   0x0080, 0x00, 0xFF, 0xFF, 0xFF,   0x05, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x01, DUNGEON_GANONS_TOWER  ), // Ganon's Castle Boss Key

    [GI_DEKU_COMPASS]       = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09DA,   0x00B8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x02, DUNGEON_DEKU_TREE         ), // Deku Tree Compass
    [GI_DODONGO_COMPASS]    = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09DB,   0x00B8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x02, DUNGEON_DODONGOS_CAVERN   ), // Dodongo's Cavern Compass
    [GI_JABU_COMPASS]       = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09DC,   0x00B8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x02, DUNGEON_JABUJABUS_BELLY   ), // Jabu Jabu Compass
    [GI_FOREST_COMPASS]     = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09DD,   0x00B8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x02, DUNGEON_FOREST_TEMPLE     ), // Forest Temple Compass
    [GI_FIRE_COMPASS]       = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09DE,   0x00B8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x02, DUNGEON_FIRE_TEMPLE       ), // Fire Temple Compass
    [GI_WATER_COMPASS]      = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09DF,   0x00B8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x02, DUNGEON_WATER_TEMPLE      ), // Water Temple Compass
    [GI_SPIRIT_COMPASS]     = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09E0,   0x00B8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x02, DUNGEON_SPIRIT_TEMPLE     ), // Spirit Temple Compass
    [GI_SHADOW_COMPASS]     = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09E1,   0x00B8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x02, DUNGEON_SHADOW_TEMPLE     ), // Shadow Temple Compass
    [GI_BOTW_COMPASS]       = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09E2,   0x00B8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x02, DUNGEON_BOTTOM_OF_THE_WELL), // Bottom of the Well Compass
    [GI_ICE_CAVERN_COMPASS] = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09E3,   0x00B8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x02, DUNGEON_ICE_CAVERN        ), // Ice Cavern Compass

    [GI_DEKU_MAP]           = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09E4,   0x00C8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x04, DUNGEON_DEKU_TREE      ), // Deku Tree Map
    [GI_DODONGO_MAP]        = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09E5,   0x00C8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x04, DUNGEON_DODONGOS_CAVERN), // Dodongo's Cavern Map
    [GI_JABU_MAP]           = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09E6,   0x00C8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x04, DUNGEON_JABUJABUS_BELLY), // Jabu Jabu Map
    [GI_FOREST_MAP]         = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09E7,   0x00C8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x04, DUNGEON_FOREST_TEMPLE  ), // Forest Temple Map
    [GI_FIRE_MAP]           = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09E8,   0x00C8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x04, DUNGEON_FIRE_TEMPLE    ), // Fire Temple Map
    [GI_WATER_MAP]          = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09E9,   0x00C8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x04, DUNGEON_WATER_TEMPLE   ), // Water Temple Map
    [GI_SPIRIT_MAP]         = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09EA,   0x00C8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x04, DUNGEON_SPIRIT_TEMPLE  ), // Spirit Temple Map
    [GI_SHADOW_MAP]         = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09EB,   0x00C8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x04, DUNGEON_SHADOW_TEMPLE  ), // Shadow Temple Map
    [GI_BOTW_MAP]           = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09EC,   0x00C8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x04, DUNGEON_BOTTOM_OF_THE_WELL   ), // Bottom of the Well Map
    [GI_ICE_CAVERN_MAP]     = ITEM_ROW(0x53, CHEST_JUNK,      0x41, 0x09ED,   0x00C8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDungeonItem, 0x04, DUNGEON_ICE_CAVERN     ), // Ice Cavern Map

    [GI_FOREST_SMALL_KEY]   = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x09EE,   0x0011, 0x00, 0xFF, 0xFF, 0xFF,   0x00, ItemUpgrade_None, ItemEffect_GiveSmallKey, DUNGEON_FOREST_TEMPLE, -1), // Forest Temple Small Key
    [GI_FIRE_SMALL_KEY]     = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x09EF,   0x003A, 0x00, 0xFF, 0xFF, 0xFF,   0x01, ItemUpgrade_None, ItemEffect_GiveSmallKey, DUNGEON_FIRE_TEMPLE,   -1), // Fire Temple Small Key
    [GI_WATER_SMALL_KEY]    = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x09F0,   0x0078, 0x00, 0xFF, 0xFF, 0xFF,   0x02, ItemUpgrade_None, ItemEffect_GiveSmallKey, DUNGEON_WATER_TEMPLE,  -1), // Water Temple Small Key
    [GI_SPIRIT_SMALL_KEY]   = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x09F1,   0x007B, 0x00, 0xFF, 0xFF, 0xFF,   0x05, ItemUpgrade_None, ItemEffect_GiveSmallKey, DUNGEON_SPIRIT_TEMPLE, -1), // Spirit Temple Small Key
    [GI_SHADOW_SMALL_KEY]   = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x09F2,   0x0079, 0x00, 0xFF, 0xFF, 0xFF,   0x03, ItemUpgrade_None, ItemEffect_GiveSmallKey, DUNGEON_SHADOW_TEMPLE, -1), // Shadow Temple Small Key
    [GI_BOTW_SMALL_KEY]     = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x09F3,   0x007A, 0x00, 0xFF, 0xFF, 0xFF,   0x04, ItemUpgrade_None, ItemEffect_GiveSmallKey, DUNGEON_BOTTOM_OF_THE_WELL,       -1), // Bottom of the Well Small Key
    [GI_GTG_SMALL_KEY]      = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x09F4,   0x007E, 0x00, 0xFF, 0xFF, 0xFF,   0x07, ItemUpgrade_None, ItemEffect_GiveSmallKey, DUNGEON_GERUDO_TRAINING_GROUNDS,  -1), // Gerudo Training Small Key
    [GI_FORTRESS_SMALL_KEY] = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x09F5,   0x007D, 0x00, 0xFF, 0xFF, 0xFF,   0x06, ItemUpgrade_None, ItemEffect_GiveSmallKey, DUNGEON_THIEVES_HIDEOUT,          -1), // Gerudo Fortress Small Key
    [GI_GANON_SMALL_KEY]    = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x09F6,   0x007F, 0x00, 0xFF, 0xFF, 0xFF,   0x08, ItemUpgrade_None, ItemEffect_GiveSmallKey, DUNGEON_INSIDE_GANONS_CASTLE, -1), // Ganon's Castle Small Key

    [GI_DOUBLE_DEFENSE]     = ITEM_ROW(0x53, CHEST_HEART,     0x41, 0x00E9,   0x0004, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDefense,     -1, -1), // Double Defense
    [GI_MAGIC_METER]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x00E4,   0x00CD, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveMagic,       -1, -1), // Magic Meter
    [GI_DOUBLE_MAGIC]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x00E8,   0x00CD, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveDoubleMagic, -1, -1), // Double Magic

    [GI_MINUET]             = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0073,   0x0010, 0x00, 0xFF, 0xFF, 0xFF,   0x01, ItemUpgrade_None, ItemEffect_GiveSong, 6, -1 ), // Minuet of Forest
    [GI_BOLERO]             = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0074,   0x0010, 0x00, 0xFF, 0xFF, 0xFF,   0x00, ItemUpgrade_None, ItemEffect_GiveSong, 7, -1 ), // Bolero of Fire
    [GI_SERENADE]           = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0075,   0x0010, 0x00, 0xFF, 0xFF, 0xFF,   0x05, ItemUpgrade_None, ItemEffect_GiveSong, 8, -1 ), // Serenade of Water
    [GI_REQUIEM]            = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0076,   0x0010, 0x00, 0xFF, 0xFF, 0xFF,   0x04, ItemUpgrade_None, ItemEffect_GiveSong, 9, -1 ), // Requiem of Spirit
    [GI_NOCTURNE]           = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0077,   0x0010, 0x00, 0xFF, 0xFF, 0xFF,   0x02, ItemUpgrade_None, ItemEffect_GiveSong, 10, -1), // Nocturne of Shadow
    [GI_PRELUDE]            = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0078,   0x0010, 0x00, 0xFF, 0xFF, 0xFF,   0x03, ItemUpgrade_None, ItemEffect_GiveSong, 11, -1), // Prelude of Light

    [GI_ZELDA_LULLABY]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x00D4,   0x0005, 0x02, 0xFF, 0xFF, 0xFF,   0x01, ItemUpgrade_None, ItemEffect_GiveSong, 12, -1), // Zelda's Lullaby
    [GI_EPONA_SONG]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x00D2,   0x0005, 0x02, 0xFF, 0xFF, 0xFF,   0x00, ItemUpgrade_None, ItemEffect_GiveSong, 13, -1), // Epona's Song
    [GI_SARIA_SONG]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x00D1,   0x0005, 0x02, 0xFF, 0xFF, 0xFF,   0x02, ItemUpgrade_None, ItemEffect_GiveSong, 14, -1), // Saria's Song
    [GI_SUN_SONG]           = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x00D3,   0x0005, 0x02, 0xFF, 0xFF, 0xFF,   0x04, ItemUpgrade_None, ItemEffect_GiveSong, 15, -1), // Sun's Song
    [GI_SONG_OF_TIME]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x00D5,   0x0005, 0x02, 0xFF, 0xFF, 0xFF,   0x05, ItemUpgrade_None, ItemEffect_GiveSong, 16, -1), // Song of Time
    [GI_SONG_OF_STORMS]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x00D6,   0x0005, 0x02, 0xFF, 0xFF, 0xFF,   0x03, ItemUpgrade_None, ItemEffect_GiveSong, 17, -1), // Song of Storms

    [GI_TYCOON_WALLET]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x09F7,   0x00D1, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveTycoonWallet, 3, -1), // Tycoon's Wallet
    [GI_LETTER_RUTO_2]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x14, 0x9099,   0x010B, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_None,            -1, -1), // Redundant Letter Bottle
    [GI_MAGIC_BEAN_PACK]    = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0048,   0x00F3, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_BeanPack,        -1, -1), // Magic Bean Pack
    [GI_TRIFORCE_PIECE]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9003,   0x016E, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_TriforcePiece,   -1, -1), // Triforce piece

    [GI_KOKIRI_EMERALD]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0080,   0x019C, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveStone, 0x0004, -1), // Kokiri Emerald
    [GI_GORON_RUBY]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0081,   0x019D, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveStone, 0x0008, -1), // Goron Ruby
    [GI_ZORA_SAPPHIRE]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0082,   0x019E, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveStone, 0x0010, -1), // Zora Sapphire

    [GI_FOREST_MEDALLION]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x003E,   0x00BA, 0x01, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveMedallion, 0x0001, -1), // Forest Medallion
    [GI_FIRE_MEDALLION]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x003C,   0x00BA, 0x02, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveMedallion, 0x0002, -1), // Fire   Medallion
    [GI_WATER_MEDALLION]    = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x003D,   0x00BA, 0x03, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveMedallion, 0x0004, -1), // Water  Medallion
    [GI_SPIRIT_MEDALLION]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x003F,   0x00BA, 0x04, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveMedallion, 0x0008, -1), // Spirit Medallion
    [GI_SHADOW_MEDALLION]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0041,   0x00BA, 0x05, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveMedallion, 0x0010, -1), // Shadow Medallion
    [GI_LIGHT_MEDALLION]    = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x0040,   0x00BA, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveMedallion, 0x0020, -1), // Light  Medallion

    [GI_PROG_GORON_SWORD]   = ITEM_ROW(  -1, CHEST_MAJOR,       -1,     -1,   0x00F8, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_GoronSword, ItemEffect_None, -1, -1), // Progressive Goron Sword

    [GI_FOREST_KEY_RING]    = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x9300,   0x0011, 0x00, 0xFF, 0xFF, 0xFF,   0x00, ItemUpgrade_None, ItemEffect_GiveSmallKeyRing, DUNGEON_FOREST_TEMPLE, -1), // Forest Temple Small Key ring
    [GI_FIRE_KEY_RING]      = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x9301,   0x003A, 0x00, 0xFF, 0xFF, 0xFF,   0x01, ItemUpgrade_None, ItemEffect_GiveSmallKeyRing, DUNGEON_FIRE_TEMPLE,   -1), // Fire Temple Small Key ring
    [GI_WATER_KEY_RING]     = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x9302,   0x0078, 0x00, 0xFF, 0xFF, 0xFF,   0x02, ItemUpgrade_None, ItemEffect_GiveSmallKeyRing, DUNGEON_WATER_TEMPLE,  -1), // Water Temple Small Key ring
    [GI_SPIRIT_KEY_RING]    = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x9303,   0x007B, 0x00, 0xFF, 0xFF, 0xFF,   0x05, ItemUpgrade_None, ItemEffect_GiveSmallKeyRing, DUNGEON_SPIRIT_TEMPLE, -1), // Spirit Temple Small Key ring
    [GI_SHADOW_KEY_RING]    = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x9304,   0x0079, 0x00, 0xFF, 0xFF, 0xFF,   0x03, ItemUpgrade_None, ItemEffect_GiveSmallKeyRing, DUNGEON_SHADOW_TEMPLE, -1), // Shadow Temple Small Key ring
    [GI_BOTW_KEY_RING]      = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x9305,   0x007A, 0x00, 0xFF, 0xFF, 0xFF,   0x04, ItemUpgrade_None, ItemEffect_GiveSmallKeyRing, DUNGEON_BOTTOM_OF_THE_WELL,       -1), // Bottom of the Well Small Key ring
    [GI_GTG_KEY_RING]       = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x9306,   0x007E, 0x00, 0xFF, 0xFF, 0xFF,   0x07, ItemUpgrade_None, ItemEffect_GiveSmallKeyRing, DUNGEON_GERUDO_TRAINING_GROUNDS,  -1), // Gerudo Training Small Key ring
    [GI_FORTRESS_KEY_RING]  = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x9307,   0x007D, 0x00, 0xFF, 0xFF, 0xFF,   0x06, ItemUpgrade_None, ItemEffect_GiveSmallKeyRing, DUNGEON_THIEVES_HIDEOUT,          -1), // Gerudo Fortress Small Key ring
    [GI_GANON_KEY_RING]     = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x9308,   0x007F, 0x00, 0xFF, 0xFF, 0xFF,   0x08, ItemUpgrade_None, ItemEffect_GiveSmallKeyRing, DUNGEON_INSIDE_GANONS_CASTLE, -1), // Ganon's Castle Small Key ring

    [GI_CHEST_GAME_KEY]     = ITEM_ROW(0x53, CHEST_SMALL_KEY, 0x41, 0x00F3,   0x00AA, 0x00, 0xFF, 0xFF, 0xFF,   0xFF, ItemUpgrade_None, ItemEffect_GiveSmallKey, DUNGEON_TREASURE_CHEST_SHOP, -1), // Small Key (Chest Game)

    [GI_SOUL_POE]           = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9450,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_POE,                   -1), // Poe Soul
    [GI_SOUL_OCTOROK]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9451,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_OCTOROK,               -1), // Octorok Soul
    [GI_SOUL_KEESE]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9452,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_KEESE,                 -1), // Keese Soul
    [GI_SOUL_TEKTITE]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9453,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_TEKTITE,               -1), // Tektite Soul
    [GI_SOUL_LEEVER]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9454,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_LEEVER,                -1), // Leever Soul
    [GI_SOUL_PEAHAT]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9455,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_PEAHAT,                -1), // Peahat Soul
    [GI_SOUL_LIZALFOS]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9456,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_LIZALFOS,              -1), // Lizalfos and Dinolfos Soul
    [GI_SOUL_SHABOM]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9457,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_SHABOM,                -1), // Shabom Soul
    [GI_SOUL_BIRI_BARI]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9458,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_BIRI_BARI,             -1), // Biri and Bari Soul
    [GI_SOUL_TAILPASARAN]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9459,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_TAILPASARAN,           -1), // Tailpasaran Soul
    [GI_SOUL_SKULLTULA]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x945A,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_SKULLTULA,             -1), // Skulltula Soul
    [GI_SOUL_TORCH_SLUG]    = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x945B,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_TORCH_SLUG,            -1), // Torch Slug Soul
    [GI_SOUL_STINGER]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x945C,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_STINGER,               -1), // Stinger Soul
    [GI_SOUL_MOBLIN]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x945D,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_MOBLIN,                -1), // Moblin Soul
    [GI_SOUL_ARMOS]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x945E,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_ARMOS,                 -1), // Armos Soul
    [GI_SOUL_DEKU_BABA]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x945F,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_DEKU_BABA,             -1), // Deku Baba Soul
    [GI_SOUL_BUBBLE]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9460,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_BUBBLE,                -1), // Bubble Soul
    [GI_SOUL_FLYING_TRAP]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9461,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_FLYING_TRAP,           -1), // Flying Pot & Tile Soul
    [GI_SOUL_BEAMOS]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9462,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_BEAMOS,                -1), // Beamos Soul
    [GI_SOUL_WALLMASTER]    = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9463,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_WALLMASTER,            -1), // Wallmaster & Floormaster Soul
    [GI_SOUL_REDEAD_GIBDO]  = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9464,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_REDEAD_GIBDO,          -1), // Redead and Gibdo Soul
    [GI_SOUL_SHELL_BLADE]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9465,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_SHELL_BLADE,           -1), // Shell Blade Soul
    [GI_SOUL_LIKE_LIKE]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9466,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_LIKE_LIKE,             -1), // Like Like Soul
    [GI_SOUL_TENTACLE]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9467,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_TENTACLE,              -1), // Parasitic Tentacle Soul
    [GI_SOUL_ANUBIS]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9468,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_ANUBIS,                -1), // Anubis Soul
    [GI_SOUL_SPIKE]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9469,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_SPIKE,                 -1), // Spike Soul
    [GI_SOUL_SKULL_KID]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x946A,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_SKULL_KID,             -1), // Skull Kid Soul
    [GI_SOUL_FREEZARD]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x946B,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_FREEZARD,              -1), // Freezard Soul
    [GI_SOUL_DEKU_SCRUB]    = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x946C,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_DEKU_SCRUB,            -1), // Deku Scrub Soul
    [GI_SOUL_WOLFOS]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x946D,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_WOLFOS,                -1), // Wolfos Soul
    [GI_SOUL_STALCHILD]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x946E,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_STALCHILD,             -1), // Stalchild Soul
    [GI_SOUL_GUAY]          = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x946F,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_GUAY,                  -1), // Guay Soul
    [GI_SOUL_DOOR_MIMIC]    = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9470,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_DOOR_MIMIC,            -1), // Door Mimic Soul
    [GI_SOUL_STALFOS]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9471,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_STALFOS,               -1), // Stalfos Soul
    [GI_SOUL_DARK_LINK]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9472,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_DARK_LINK,             -1), // Dark Link Soul
    [GI_SOUL_FLARE_DANCER]  = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9473,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_FLARE_DANCER,          -1), // Flare Dancer Soul
    [GI_SOUL_DEAD_HAND]     = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9474,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_DEAD_HAND,             -1), // Dead Hand Soul
    [GI_SOUL_GERUDO]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9475,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_GERUDO,                -1), // Gerudo Soul
    [GI_SOUL_GOHMA]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9476,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_GOHMA,                 -1), // Gohma Soul
    [GI_SOUL_DODONGO]       = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9477,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_DODONGO,               -1), // Dodongo Soul
    [GI_SOUL_BARINADE]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9478,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_BARINADE,              -1), // Barinade Soul
    [GI_SOUL_PHANTOM_GANON] = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x9479,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_PHANTOM_GANON,         -1), // Phantom Ganon Soul
    [GI_SOUL_VOLVAGIA]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x947A,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_VOLVAGIA,              -1), // Volvagia Soul
    [GI_SOUL_MORPHA]        = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x947B,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_MORPHA,                -1), // Morpha Soul
    [GI_SOUL_BONGO_BONGO]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x947C,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_BONGO_BONGO,           -1), // Bongo Bongo Soul
    [GI_SOUL_TWINROVA]      = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x947D,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_TWINROVA,              -1), // Twinrova Soul
    [GI_SOUL_GANON]         = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x947E,   0x00E4, 0x00, 0xFF, 0x01, 0x00,   0xFF, ItemUpgrade_None, ItemEffect_EnemySoul, SOUL_GANON,                 -1), // Ganon Soul

    [GI_OCARINA_BUTTON_L]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x93F0,   0x0123, 0x00, 0xFF, 0xFF, 0xFF,   0x00, ItemUpgrade_None, ItemEffect_OcarinaNote, OCARINA_BUTTON_L, -1), // Ocarina Note Button L
    [GI_OCARINA_BUTTON_R]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x93F1,   0x0123, 0x00, 0xFF, 0xFF, 0xFF,   0x01, ItemUpgrade_None, ItemEffect_OcarinaNote, OCARINA_BUTTON_R, -1), // Ocarina Note Button R
    [GI_OCARINA_BUTTON_X]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x93F2,   0x0123, 0x00, 0xFF, 0xFF, 0xFF,   0x02, ItemUpgrade_None, ItemEffect_OcarinaNote, OCARINA_BUTTON_X, -1), // Ocarina Note Button X
    [GI_OCARINA_BUTTON_Y]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x93F3,   0x0123, 0x00, 0xFF, 0xFF, 0xFF,   0x03, ItemUpgrade_None, ItemEffect_OcarinaNote, OCARINA_BUTTON_Y, -1), // Ocarina Note Button Y
    [GI_OCARINA_BUTTON_A]   = ITEM_ROW(0x53, CHEST_MAJOR,     0x41, 0x93F4,   0x0123, 0x00, 0xFF, 0xFF, 0xFF,   0x04, ItemUpgrade_None, ItemEffect_OcarinaNote, OCARINA_BUTTON_A, -1), // Ocarina Note Button A
};
// clang-format on

ItemRow* ItemTable_GetItemRow(u16 itemId) {
    if (itemId >= ARR_SIZE(rItemTable)) {
        return NULL;
    }
    ItemRow* itemRow = &rItemTable[itemId];
    if (itemRow->baseItemId == 0) {
        return NULL;
    }
    return itemRow;
}

u16 ItemTable_ResolveUpgrades(u16 itemId) {
    for (;;) {
        ItemRow* itemRow = ItemTable_GetItemRow(itemId);
        u16 newItemId    = itemRow->upgrade(&gSaveContext, itemId);
        if (newItemId == itemId) {
            return itemId;
        }
        itemId = newItemId;
    }
}

void ItemTable_CallEffect(ItemRow* itemRow) {
    itemRow->effect(&gSaveContext, itemRow->effectArg1, itemRow->effectArg2);
}
