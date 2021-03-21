#include "item_effect.h"
#include "settings.h"
#include "z3D/z3D.h"

// #define rupee_cap ((us16*)0x800F8CEC)
volatile uint8_t MAX_RUPEES = 0;

// typedef void (*commit_scene_flags_fn)(z64_game_t* game_ctxt);
// #define commit_scene_flags ((commit_scene_flags_fn)0x8009D894)
// typedef void (*save_game_fn)(void* unk);
// #define save_game ((save_game_fn)0x800905D4)

void ItemEffect_None(SaveContext* saveCtx, s16 arg1, s16 arg2) {
}

void ItemEffect_FullHeal(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->healthAccumulator = 20 * 0x10;
}

// void give_triforce_piece(SaveContext* saveCtx, s16 arg1, s16 arg2) {
//     save->scene_flags[0x48].unk_00_ += 1; //Unused word in scene x48.
//     set_triforce_render();

//     // Trigger win when the target is hit
//     if (save->scene_flags[0x48].unk_00_ == triforce_pieces_requied) {
//         // Give GC boss key to allow beating the game again afterwards
//         give_dungeon_item(save, 0x01, 10);

//         // Save Game
//         save->entrance_index = z64_game.entrance_index;
//         save->scene_index = z64_game.scene_index;
//         commit_scene_flags(&z64_game);
//         save_game(&z64_game + 0x1F74);

//         // warp to start of credits sequence
//         z64_file.cutscene_next = 0xFFF8;
//         z64_game.entrance_index = 0x00A0;
//         z64_game.scene_load_flag = 0x14;
//         z64_game.fadeout_transition = 0x01;
//     }
// }

// void give_tycoon_wallet(SaveContext* saveCtx, s16 arg1, s16 arg2) {
//     save->wallet = 3;
//     if(MAX_RUPEES)
//         save->rupees = rupee_cap[arg1];
// }

void ItemEffect_GiveBiggoronSword(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->bgsFlag = 1; // Set flag to make the sword durable
}

void ItemEffect_GiveBottle(SaveContext* saveCtx, s16 bottleItemId, s16 arg2) {
    for (u32 i = SLOT_BOTTLE_1; i <= SLOT_BOTTLE_4; i++) {
        if (saveCtx->items[i] == 0xFF) {
            saveCtx->items[i] = bottleItemId;
            return;
        }
    }
}

void ItemEffect_GiveDungeonItem(SaveContext* saveCtx, s16 mask, s16 dungeonId) {
    saveCtx->dungeonItems[dungeonId] |= mask;
}

void ItemEffect_GiveSmallKey(SaveContext* saveCtx, s16 dungeonId, s16 arg2) {
    s8 keys = saveCtx->dungeonKeys[dungeonId];
    if (keys < 0) {
        keys = 0;
    }
    saveCtx->dungeonKeys[dungeonId] = keys + 1;
}

void ItemEffect_GiveDefense(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->doubleDefense = 1;
    // saveCtx->defense_hearts = 20; //TODO? is this needed?
    saveCtx->healthAccumulator = 20 * 0x10;
}

void ItemEffect_GiveMagic(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->magicLevel = 1; // Set meter level
    saveCtx->magicAcquired = 1; // Required for meter to persist on save load
    // save->magic_meter_size = 0x30; // Set meter size //TODO? is this needed?
    saveCtx->magic = 0x30; // Fill meter
}

void ItemEffect_GiveDoubleMagic(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->magicLevel = 2; // Set meter level
    saveCtx->magicAcquired = 1; // Required for meter to persist on save load
    saveCtx->doubleMagic = 1; // Required for meter to persist on save load
    // saveCtx->magic_meter_size = 0x60; // Set meter size //TODO? is this needed?
    saveCtx->magic = 0x60; // Fill meter
}

void ItemEffect_GiveFairyOcarina(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->items[SLOT_OCARINA] = ITEM_OCARINA_FAIRY;
}

void ItemEffect_GiveSong(SaveContext* saveCtx, s16 questBit, s16 arg2) {
    saveCtx->questItems |= 1 << questBit;

    //give epona for Skip Epona Race setting
    if (questBit == 13 && gSettingsContext.skipEponaRace == SKIP) {
      saveCtx->eventChkInf[0x1] |= 0x0100;
    }
}

void ItemEffect_IceTrap(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    IceTrap_Push();
}

void ItemEffect_BeanPack(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->items[SLOT_BEAN] = ITEM_BEAN;
    saveCtx->ammo[SLOT_BEAN] += 10; // 10 Magic Beans
}

void ItemEffect_FillWalletUpgrade(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    if(MAX_RUPEES) {
        if (arg1 == 1) {
            saveCtx->rupeeAccumulator = 200;
        } else if (arg1 == 2) {
            saveCtx->rupeeAccumulator = 500;
        }
    }
}

// uint8_t OPEN_KAKARIKO = 0;
// uint8_t COMPLETE_MASK_QUEST = 0;
void ItemEffect_OpenMaskShop(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    // TODO
    // if (OPEN_KAKARIKO) {
    //     save->inf_table[7] = save->inf_table[7] | 0x40; // "Spoke to Gate Guard About Mask Shop"
    //     if (!COMPLETE_MASK_QUEST) {
    //         save->item_get_inf[2] = save->item_get_inf[2] & 0xFB87; // Unset "Obtained Mask" flags just in case of savewarp before Impa.
    //     }
    // }
    // if (COMPLETE_MASK_QUEST) {
    //     save->inf_table[7] = save->inf_table[7] | 0x80; // "Soldier Wears Keaton Mask"
    //     save->item_get_inf[3] = save->item_get_inf[3] | 0x8F00; // "Sold Masks & Unlocked Masks" / "Obtained Mask of Truth"
    //     save->event_chk_inf[8] = save->event_chk_inf[8] | 0xF000; // "Paid Back Mask Fees"
    // }
}

static void ResetItemSlotsIfMatchesID(u8 itemSlot) {
    // Remove the slot from child/adult grids
    for (u32 i = 0; i < 0x18; ++i) {
        if (gSaveContext.itemMenuChild[i] == itemSlot) {
            gSaveContext.itemMenuChild[i] = 0xFF;
        }
        if (gSaveContext.itemMenuAdult[i] == itemSlot) {
            gSaveContext.itemMenuAdult[i] = 0xFF;
        }
    }
}

static void PushSlotIntoInventoryMenu(u8 itemSlot) {
    u8 currentSlot = 0;
    while(gSaveContext.itemMenuChild[currentSlot] != 0xFF) {
        currentSlot++;
    }
    gSaveContext.itemMenuChild[currentSlot] = itemSlot;

    currentSlot = 0;
    while(gSaveContext.itemMenuAdult[currentSlot] != 0xFF) {
        currentSlot++;
    }
    gSaveContext.itemMenuAdult[currentSlot] = itemSlot;
}

void ItemEffect_PlaceMagicArrowsInInventory(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    if (arg1 == 0) { // Fairy Bow
        ResetItemSlotsIfMatchesID(ItemSlots[ITEM_ARROW_FIRE]);
        ResetItemSlotsIfMatchesID(ItemSlots[ITEM_ARROW_ICE]);
        ResetItemSlotsIfMatchesID(ItemSlots[ITEM_ARROW_LIGHT]);
    } else if (saveCtx->items[ItemSlots[ITEM_BOW]] != ITEM_BOW) {
        if (arg1 == 1) { // Fire Arrow
            PushSlotIntoInventoryMenu(ItemSlots[ITEM_ARROW_FIRE]);
        } else if (arg1 == 2) { // Ice Arrow
            PushSlotIntoInventoryMenu(ItemSlots[ITEM_ARROW_ICE]);
        } else if (arg1 == 3) { // Light Arrow
            PushSlotIntoInventoryMenu(ItemSlots[ITEM_ARROW_LIGHT]);
        }
    }
}
