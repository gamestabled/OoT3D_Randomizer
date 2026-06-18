#include "menus.h"
#include "z3D/z3D.h"
#include "input.h"
#include "savefile.h"
#include "settings.h"
#include "dungeon.h"
#include "item_override.h"

extern MenuSpriteManager* gItemsMenuSpritesManager;
extern MenuSpriteManager* gBowMenuSpritesManager;
extern MenuSpriteManager* gItemsMenuGlowSpritesManager;
extern MenuSpriteManager* gMenuSpritesManager_506740;
extern MenuSpriteManager* gDungeonMapMenuSpritesManager;
extern MenuSpriteManager* gGearMenuSpritesManager;

extern s32 gItemsMenuSelectedSlot;
extern s32 gGearMenuSelectedSlot;

void MenuSpritesManager_RegisterItemSprite(MenuSpriteManager* menuMan, s32 spriteId, s32 itemId);
void MenuSpritesManager_SetSpriteAt(MenuSpriteManager* menuMan, s32 spriteId, s32 x, s32 y, s32 width, s32 height);
void MenuSpritesManager_OffsetSpriteAt(MenuSpriteManager* menuMan, s32 spriteId, s32 x, s32 y, s32 width, s32 height,
                                       s32 xOffset, s32 yOffset);

void ItemsMenu_Draw(void) {
    s32 selectedItemSlot;
    if (gItemsMenuSelectedSlot != -1) {
        if (gSaveContext.linkAge == 0) {
            selectedItemSlot = gSaveContext.itemMenuAdult[gItemsMenuSelectedSlot];
        } else {
            selectedItemSlot = gSaveContext.itemMenuChild[gItemsMenuSelectedSlot];
        }

        if (selectedItemSlot == SLOT_TRADE_ADULT) {
            u8 startingItem  = gSaveContext.items[selectedItemSlot];
            u8 potentialItem = startingItem;

            if (rInputCtx.pressed.l) {
                potentialItem = startingItem - 1;
                while ((potentialItem != startingItem) && !SaveFile_TradeItemIsOwned(potentialItem)) {
                    potentialItem--;
                    if (potentialItem < ITEM_POCKET_EGG) {
                        potentialItem = ITEM_CLAIM_CHECK;
                    }
                }
            } else if (rInputCtx.pressed.r) {
                potentialItem = startingItem + 1;
                while ((potentialItem != startingItem) && !SaveFile_TradeItemIsOwned(potentialItem)) {
                    potentialItem++;
                    if (potentialItem > ITEM_CLAIM_CHECK) {
                        potentialItem = ITEM_POCKET_EGG;
                    }
                }
            }

            if (potentialItem != startingItem) {
                gSaveContext.items[selectedItemSlot] = potentialItem;
                MenuSpritesManager_RegisterItemSprite(gItemsMenuSpritesManager, gItemsMenuSelectedSlot,
                                                      gSaveContext.items[selectedItemSlot]);
                MenuSpritesManager_RegisterItemSprite(gItemsMenuGlowSpritesManager, 0,
                                                      gSaveContext.items[selectedItemSlot]);
            }
        }

        // Obtained both weird egg and Zelda's letter and pressed l/r on child trade slot
        if (selectedItemSlot == SLOT_TRADE_CHILD && SaveFile_ChildTradeSlots() == 2 &&
            (rInputCtx.pressed.l || rInputCtx.pressed.r)) {
            u8 item = gSaveContext.items[selectedItemSlot];

            // Switch to ZL/mask slot
            if (item == ITEM_WEIRD_EGG || item == ITEM_CHICKEN) {
                // ZL has been replaced with a mask
                if (gSaveContext.itemGetInf[2] & (0x1 << 0x3)) {
                    // Sold mask but not paid for it
                    if (SaveFile_MaskSlotValue() == ITEM_SOLD_OUT) {
                        // Only change item to no mask if not equipped
                        if (gItemsMenuSelectedSlot % 6 != 5) {
                            item = ITEM_SOLD_OUT;
                        }
                    } else {
                        item = ITEM_MASK_KEATON + SaveFile_CurrentMask();
                    }
                } else {
                    item = ITEM_LETTER_ZELDA;
                }
            }
            // Switch to egg/cucco slot
            else {
                if (SaveFile_WeirdEggHatched()) {
                    item = ITEM_CHICKEN;
                } else {
                    item = ITEM_WEIRD_EGG;
                }
            }

            gSaveContext.items[selectedItemSlot] = item;
            MenuSpritesManager_RegisterItemSprite(gItemsMenuSpritesManager, gItemsMenuSelectedSlot,
                                                  gSaveContext.items[selectedItemSlot]);
            MenuSpritesManager_RegisterItemSprite(gItemsMenuGlowSpritesManager, 0,
                                                  gSaveContext.items[selectedItemSlot]);
        }
    }
}

// Returns a text ID to display a textbox in the Gear Menu when an empty slot is selected, or 0 if there is no text.
u16 GearMenu_GetRewardHint(void) {
    s32 rewardId;
    u8 checkedAltar, isHintUnlocked = FALSE;

    if (gGearMenuSelectedSlot >= GEARSLOT_KOKIRI_EMERALD && gGearMenuSelectedSlot <= GEARSLOT_ZORA_SAPPHIRE) {
        rewardId     = gGearMenuSelectedSlot - GEARSLOT_KOKIRI_EMERALD;
        checkedAltar = gExtSaveData.extInf.totAltarFlags & (1 << AGE_CHILD);
    } else if (gGearMenuSelectedSlot >= GEARSLOT_FOREST_MEDALLION &&
               gGearMenuSelectedSlot <= GEARSLOT_LIGHT_MEDALLION) {
        rewardId     = gGearMenuSelectedSlot - GEARSLOT_FOREST_MEDALLION + 3;
        checkedAltar = gExtSaveData.extInf.totAltarFlags & (1 << AGE_ADULT);
    } else {
        return 0;
    }

    if (gSettingsContext.compassesShowReward) {
        if (gSettingsContext.shuffleRewards == REWARDSHUFFLE_END_OF_DUNGEON) {
            // If rewards are at the End of Dungeons, find which dungeon has the reward for the selected slot.
            for (u32 dungeonId = 0; dungeonId <= DUNGEON_SHADOW_TEMPLE; dungeonId++) {
                if (rDungeonRewardOverrides[dungeonId] == rewardId) {
                    isHintUnlocked = gSaveContext.dungeonItems[dungeonId] & 2; // Check if compass is owned
                    break;
                }
            }
        } else {
            // If rewards are anywhere, Light Medallion can't be hinted because there is no Light Temple Compass.
            isHintUnlocked = ((rewardId != R_LIGHT_MEDALLION) && (gSaveContext.dungeonItems[rewardId] & 2));
        }
    } else {
        isHintUnlocked = gSettingsContext.totAltarHints && checkedAltar;
    }

    if (isHintUnlocked) {
        return 0x7300 + rewardId;
    }

    return 0;
}

u16 SaveMenu_IgnoreOpen(void) {
    return ItemOverride_IsAPendingOverride() || // safety check to avoid missing pending overrides by save-warping
           (gSettingsContext.menuOpeningButton == 0 && rInputCtx.cur.sel) ||
           (gSettingsContext.menuOpeningButton == 1 && rInputCtx.cur.strt);
}
