#include "item_effect.h"
#include "settings.h"
#include "z3D/z3D.h"
#include "savefile.h"
#include "multiplayer.h"

void ItemEffect_None(SaveContext* saveCtx, s16 arg1, s16 arg2) {
}

void ItemEffect_FullHeal(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    //With the No Health Refills option on, or if max health is currently 0, store-bought health upgrades do not heal the player
    if (gSettingsContext.heartDropRefill != HEARTDROPREFILL_NOREFILL &&
        gSettingsContext.heartDropRefill != HEARTDROPREFILL_NODROPREFILL &&
        gSaveContext.healthCapacity > 0) {

        saveCtx->healthAccumulator = 20 * 0x10;
    }
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

void ItemEffect_GiveTycoonWallet(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->upgrades |= 3 << 12;
    if (gSettingsContext.startingMaxRupees)
        saveCtx->rupees = 999;
}

void ItemEffect_GiveBiggoronSword(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->bgsFlag = 1; // Set flag to make the sword durable

    if (gSettingsContext.mp_SharedProgress == ON) {
        Multiplayer_Send_BGSFlag();
    }
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
    // Special case for Treasure Chest Shop: if the keys are in a pack, give all 6 at once
    if (dungeonId == DUNGEON_TREASURE_CHEST_SHOP && gSettingsContext.shuffleChestMinigame == SHUFFLECHESTMINIGAME_PACK) {
        keys += 5;
    }
    saveCtx->dungeonKeys[dungeonId] = keys + 1;
}

void ItemEffect_GiveSmallKeyRing(SaveContext* saveCtx, s16 dungeonId, s16 arg2) {
    s8 keys = saveCtx->dungeonKeys[dungeonId];
    if (keys < 0) {
        keys = 0;
    }
    s8 amt = 0;
    switch(dungeonId) {
        case DUNGEON_FOREST_TEMPLE:
            if (gSettingsContext.forestTempleDungeonMode == DUNGEONMODE_MQ) {
                amt = 6;
            }
            else {
                amt = 5;
            }
            break;
        case DUNGEON_FIRE_TEMPLE:
            if (gSettingsContext.fireTempleDungeonMode == DUNGEONMODE_MQ) {
                amt = 5;
            }
            else {
                amt = 8;
            }
            break;
        case DUNGEON_WATER_TEMPLE:
            if (gSettingsContext.waterTempleDungeonMode == DUNGEONMODE_MQ) {
                amt = 2;
            }
            else {
                amt = 6;
            }
            break;
        case DUNGEON_SPIRIT_TEMPLE:
            if (gSettingsContext.spiritTempleDungeonMode == DUNGEONMODE_MQ) {
                amt = 7;
            }
            else {
                amt = 5;
            }
            break;
        case DUNGEON_SHADOW_TEMPLE:
            if (gSettingsContext.shadowTempleDungeonMode == DUNGEONMODE_MQ) {
                amt = 6;
            }
            else {
                amt = 5;
            }
            break;
        case DUNGEON_BOTTOM_OF_THE_WELL:
            if (gSettingsContext.bottomOfTheWellDungeonMode == DUNGEONMODE_MQ) {
                amt = 2;
            }
            else {
                amt = 3;
            }
            break;
        case DUNGEON_GERUDO_TRAINING_GROUNDS:
            if (gSettingsContext.gerudoTrainingGroundsDungeonMode == DUNGEONMODE_MQ) {
                amt = 3;
            }
            else {
                amt = 9;
            }
            break;
        case DUNGEON_THIEVES_HIDEOUT:
            amt = 4;
            break;
        case DUNGEON_INSIDE_GANONS_CASTLE:
            if (gSettingsContext.ganonsCastleDungeonMode == DUNGEONMODE_MQ) {
                amt = 3;
            }
            else {
                amt = 2;
            }
            break;
    }
    saveCtx->dungeonKeys[dungeonId] = keys + amt;
}

void ItemEffect_GiveDefense(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->doubleDefense = 1;
    // saveCtx->defense_hearts = 20; //TODO? is this needed?
    //With the No Health Refills option on, or if max health is currently 0, store-bought health upgrades do not heal the player
    if (gSettingsContext.heartDropRefill != HEARTDROPREFILL_NOREFILL &&
        gSettingsContext.heartDropRefill != HEARTDROPREFILL_NODROPREFILL &&
        gSaveContext.healthCapacity > 0) {

        saveCtx->healthAccumulator = 20 * 0x10;
    }

    if (gSettingsContext.mp_SharedProgress == ON) {
        Multiplayer_Send_GreatFairyBuff(0);
    }
}

void ItemEffect_GiveMagic(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->magicLevel = 1;        // Set meter level
    saveCtx->magicAcquired = 1;     // Required for meter to persist on save load
    saveCtx->magicMeterSize = 0x30; // Set meter size
    saveCtx->magic = 0x30;          // Fill meter

    if (gSettingsContext.mp_SharedProgress == ON) {
        Multiplayer_Send_GreatFairyBuff(1);
    }
}

void ItemEffect_GiveDoubleMagic(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->magicLevel = 2;        // Set meter level
    saveCtx->magicAcquired = 1;     // Required for meter to persist on save load
    saveCtx->doubleMagic = 1;       // Required for meter to persist on save load
    saveCtx->magicMeterSize = 0x60; // Set meter size
    saveCtx->magic = 0x60;          // Fill meter

    if (gSettingsContext.mp_SharedProgress == ON) {
        Multiplayer_Send_GreatFairyBuff(2);
    }
}

void ItemEffect_GiveFairyOcarina(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->items[SLOT_OCARINA] = ITEM_OCARINA_FAIRY;
}

void ItemEffect_GiveSong(SaveContext* saveCtx, s16 questBit, s16 arg2) {
    saveCtx->questItems |= 1 << questBit;

    // give epona for Skip Epona Race setting
    if (questBit == 13 && gSettingsContext.skipEponaRace == SKIP) {
        saveCtx->eventChkInf[0x1] |= 0x0100;
        gSaveContext.horseData.pos.y = 0xF000; // place Epona OoB, so you can't reach her without playing the song
    }
}

void ItemEffect_IceTrap(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    IceTrap_Push((u16)arg1 << 16 | (u16)arg2);
}

void ItemEffect_GiveMasterSword(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    gExtSaveData.masterSwordFlags |= 1;
}

void ItemEffect_EquipMasterSword(void) {
    // Prevent auto-equipping master sword on child unless can equip normally
    if (gSettingsContext.shuffleMasterSword && gSaveContext.linkAge == 1 && !gSettingsContext.masterSwordAsChild) return;
    // Otherwise run original code
    gSaveContext.equips.equipment = (gSaveContext.equips.equipment & 0xFFF0) | 0x2;
    gSaveContext.equips.buttonItems[0] = 0x3C;
}

void ItemEffect_BeanPack(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    saveCtx->items[SLOT_BEAN] = ITEM_BEAN;
    saveCtx->ammo[SLOT_BEAN] += 10; // 10 Magic Beans
}

//With the No Ammo Drops option on, when the player gets an ammo upgrade,
//the ammo count increases by 10 instead of being set to the maximum
typedef void (*Inventory_ChangeUpgrade_proc)(u32 upgrade, u32 value);
#define Inventory_ChangeUpgrade_addr 0x33C730
#define Inventory_ChangeUpgrade ((Inventory_ChangeUpgrade_proc)Inventory_ChangeUpgrade_addr)

void ItemEffect_GiveUpgrade(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    Inventory_ChangeUpgrade(arg2, arg1);
    if(gSettingsContext.ammoDrops == AMMODROPS_NONE){
        switch (arg2){
            case 0: saveCtx->ammo[SLOT_BOW] += 10; break;
            case 1: saveCtx->ammo[SLOT_BOMB] += 10; break;
            case 5: saveCtx->ammo[SLOT_SLINGSHOT] += 10; break;
            case 6: saveCtx->items[SLOT_STICK] = ITEM_STICK; saveCtx->ammo[SLOT_STICK] += 10; break;
            case 7: saveCtx->items[SLOT_NUT] = ITEM_NUT; saveCtx->ammo[SLOT_NUT] += 10; break;
		}
    } else {
        switch (arg2){
            case 0: saveCtx->ammo[SLOT_BOW] = (20 + 10 * arg1); break;
            case 1: saveCtx->ammo[SLOT_BOMB] = (10 + 10 * arg1); break;
            case 5: saveCtx->ammo[SLOT_SLINGSHOT] = (20 + 10 * arg1); break;
            case 6: saveCtx->items[SLOT_STICK] = ITEM_STICK; saveCtx->ammo[SLOT_STICK] = (10 * arg1); break;
            case 7: saveCtx->items[SLOT_NUT] = ITEM_NUT; saveCtx->ammo[SLOT_NUT] = (10 + 10 * arg1); break;
		}
    }
}
void ItemEffect_FillWalletUpgrade(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    if (gSettingsContext.startingMaxRupees) {
        if (arg1 == 1) {
            saveCtx->rupeeAccumulator = 200;
        } else if (arg1 == 2) {
            saveCtx->rupeeAccumulator = 500;
        }
    }
}

void ItemEffect_OpenMaskShop(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    if (gSettingsContext.openKakariko == OPENKAKARIKO_OPEN) {
        gSaveContext.infTable[7] |= 0x40; // "Spoke to Gate Guard About Mask Shop"
        if (!gSettingsContext.completeMaskQuest) {
            gSaveContext.itemGetInf[2] &= 0xFB87; // Unset "Obtained Mask" flags just in case of savewarp before Impa.
        }
    }
    if (gSettingsContext.completeMaskQuest) {
        gSaveContext.infTable[7] |= 0x80; // "Soldier Wears Keaton Mask"
        gSaveContext.itemGetInf[3] |= 0x8F00; // "Sold Masks & Unlocked Masks" / "Obtained Mask of Truth"
        gSaveContext.eventChkInf[8] |= 0xF000; // "Paid Back Mask Fees"
    }
}

static u8 MakeSpaceInItemMenu(u8* itemMenu) {
    u8 currentSlot = 5;
    u8 emptyButton = 0xFF;
    u8 slotToFree = 0xFF;

    // find an empty button
    for (currentSlot = 5; currentSlot < 24; currentSlot += 6) {
        if (itemMenu[currentSlot] == 0xFF) {
            emptyButton = currentSlot;
            break;
        }
    }

    if (emptyButton == 0xFF) {
        return 0xFF;
    }

    // search the inventory for an equippable item
    for (currentSlot = 0; currentSlot < 24; currentSlot++) {

        // ignore the button slots
        if ((currentSlot + 1) % 6 == 0) {
            currentSlot++;
        }

        if (itemMenu[currentSlot] == 2) { // Bomb slot
            slotToFree = currentSlot;
        } else if (itemMenu[currentSlot] == 8) { // Bombchu slot
            slotToFree = currentSlot;
        } else if (itemMenu[currentSlot] == 1) { // Deku Nuts slot
            slotToFree = currentSlot;
        } else if (itemMenu[currentSlot] == 5) { // Din's Fire slot
            slotToFree = currentSlot;
        }

        // equip the item and free up the slot it occupied
        if (slotToFree != 0xFF) {
            itemMenu[emptyButton] = itemMenu[slotToFree];
            itemMenu[slotToFree] = 0xFF;
            return slotToFree;
        }
    }
    return 0xFF;
}

void PushSlotIntoInventoryMenu(u8 itemSlot) {
    u8 currentSlot = 0;
    while ((currentSlot + 1) % 6 == 0 || gSaveContext.itemMenuChild[currentSlot] != 0xFF) {
        currentSlot++;
        if (currentSlot == 24) {
            currentSlot = MakeSpaceInItemMenu(gSaveContext.itemMenuChild);
            break;
        }
    }
    gSaveContext.itemMenuChild[currentSlot] = itemSlot;

    currentSlot = 0;
    while ((currentSlot + 1) % 6 == 0 || gSaveContext.itemMenuAdult[currentSlot] != 0xFF) {
        currentSlot++;
        if (currentSlot == 24) {
            for (currentSlot = 5; currentSlot < 24; currentSlot += 6) {
                if (gSaveContext.itemMenuAdult[currentSlot] == 0xFF) {
                    break;
                }
            }
            break;
        }
    }
    gSaveContext.itemMenuAdult[currentSlot] = itemSlot;
}

void ItemEffect_PlaceMagicArrowsInInventory(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    if (arg1 == 0) { // Fairy Bow
        SaveFile_ResetItemSlotsIfMatchesID(ItemSlots[ITEM_ARROW_FIRE]);
        SaveFile_ResetItemSlotsIfMatchesID(ItemSlots[ITEM_ARROW_ICE]);
        SaveFile_ResetItemSlotsIfMatchesID(ItemSlots[ITEM_ARROW_LIGHT]);
        if (gSettingsContext.mp_SharedProgress == ON && !mp_duplicateSendProtection) {
            Multiplayer_Send_MagicArrow(arg1);
        }
    } else if (saveCtx->items[ItemSlots[ITEM_BOW]] == ITEM_NONE) {
        if (arg1 == 1 && saveCtx->items[ItemSlots[ITEM_ARROW_FIRE]] == ITEM_NONE) { // Fire Arrow
            PushSlotIntoInventoryMenu(ItemSlots[ITEM_ARROW_FIRE]);
            if (gSettingsContext.mp_SharedProgress == ON && !mp_duplicateSendProtection) {
                Multiplayer_Send_MagicArrow(arg1);
            }
        } else if (arg1 == 2 && saveCtx->items[ItemSlots[ITEM_ARROW_ICE]] == ITEM_NONE) { // Ice Arrow
            PushSlotIntoInventoryMenu(ItemSlots[ITEM_ARROW_ICE]);
            if (gSettingsContext.mp_SharedProgress == ON && !mp_duplicateSendProtection) {
                Multiplayer_Send_MagicArrow(arg1);
            }
        } else if (arg1 == 3 && saveCtx->items[ItemSlots[ITEM_ARROW_LIGHT]] == ITEM_NONE) { // Light Arrow
            PushSlotIntoInventoryMenu(ItemSlots[ITEM_ARROW_LIGHT]);
            if (gSettingsContext.mp_SharedProgress == ON && !mp_duplicateSendProtection) {
                Multiplayer_Send_MagicArrow(arg1);
            }
        }
    }
    mp_duplicateSendProtection = false;
}

void ItemEffect_GiveChildKokiriSword(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    // Put the Kokiri Sword on Child B button when Link goes back child
    saveCtx->childEquips.buttonItems[0] = ITEM_SWORD_KOKIRI;

    if (gSettingsContext.mp_SharedProgress == ON) {
        Multiplayer_Send_KokiriSwordEquip();
    }
}

void ItemEffect_GiveStone(SaveContext* saveCtx, s16 mask, s16 arg2) {
    s32 trueMask = mask << 16;
    saveCtx->questItems |= trueMask;
}

void ItemEffect_GiveMedallion(SaveContext* saveCtx, s16 mask, s16 arg2) {
    saveCtx->questItems |= mask;
}

void ItemEffect_MoveNabooru(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    gSaveContext.eventChkInf[9] |= 0x0020;
}

void ItemEffect_GrannySellsPotions(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    gSaveContext.itemGetInf[3] |= 0x1;
}

void ItemEffect_OwnAdultTrade(SaveContext* saveCtx, s16 arg1, s16 arg2) {
    SaveFile_SetTradeItemAsOwned(arg1);

    if ((gSettingsContext.shuffleAdultTradeQuest == SHUFFLEADULTTRADEQUEST_OFF) && arg1 >= ITEM_ODD_POTION) {
        ItemEffect_GrannySellsPotions(saveCtx, arg1, arg2);
    }
}
