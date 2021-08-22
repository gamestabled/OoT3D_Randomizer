#include "z3D/z3D.h"
#include "settings.h"
#include "item_effect.h"
#include "giants_knife.h"
#include "savefile.h"
#include "3ds/types.h"

void SaveFile_Init() {
#ifdef ENABLE_DEBUG
    gSaveContext.equipment  |= 0x0FFF;  //Swords, shields, tunics, boots
    gSaveContext.bgsFlag     = 1;
    gSaveContext.bgsHitsLeft = 1;
    gSaveContext.upgrades   |= 0x309;   //bomb bag, quiver, strength, scale
    gSaveContext.questItems |= 0x3FFC0; //songs
    gSaveContext.items[SLOT_OCARINA]  = ITEM_OCARINA_FAIRY;
    gSaveContext.items[SLOT_HOOKSHOT] = ITEM_LONGSHOT;
    gSaveContext.items[SLOT_HAMMER]   = ITEM_HAMMER;
    gSaveContext.items[SLOT_FARORES_WIND] = ITEM_FARORES_WIND;
    gSaveContext.items[SLOT_DINS_FIRE] = ITEM_DINS_FIRE;
    gSaveContext.items[SLOT_BOMB] = ITEM_BOMB;
    gSaveContext.items[SLOT_BOW] = ITEM_BOW;
    gSaveContext.items[SLOT_ARROW_FIRE] = ITEM_ARROW_FIRE;
    gSaveContext.items[SLOT_HOVER_BOOTS] = ITEM_BOOTS_HOVER;
    gSaveContext.items[SLOT_ARROW_LIGHT] = ITEM_ARROW_LIGHT;
    gSaveContext.items[SLOT_BOTTLE_1] = ITEM_FISH;
    gSaveContext.magicAcquired = 1;
    gSaveContext.magicLevel = 2;
    gSaveContext.magic = 48;
    gSaveContext.dungeonKeys[6] = 8;
    gSaveContext.dungeonKeys[7] = 5;
    gSaveContext.ammo[2] = 20; //bombs
    gSaveContext.ammo[3] = 20; //arrows
#endif

    /*-----------------------------------
    |       THINGS TO ALWAYS SET        |
    -----------------------------------*/
    gSaveContext.cutsceneIndex = 0;          //no intro cutscene
    gSaveContext.infTable   [0x0] |= 0x01;   //greeted by Saria
    gSaveContext.infTable  [0x11] |= 0x0400; //Met Darunia in Fire Temple
    gSaveContext.infTable  [0x14] |= 0x000E; //Ruto in Jabu can be escorted immediately
    gSaveContext.infTable  [0x19] |= 0x0100; //Got Magic Container
    gSaveContext.eventChkInf[0x3] |= 0x0800; //began Nabooru Battle
    gSaveContext.eventChkInf[0x7] |= 0x01FF; //began boss battles
    gSaveContext.eventChkInf[0x9] |= 0x0010; //Spoke to Nabooru as child
    gSaveContext.eventChkInf[0xA] |= 0x017B; //entrance cutscenes (minus temple of time)
    gSaveContext.eventChkInf[0xB] |= 0x07FF; //more entrance cutscenes
    gSaveContext.eventChkInf[0xC] |= 0x0001; //Nabooru ordered to fight by Twinrova
    gSaveContext.eventChkInf[0xC] |= 0x8000; //Forest Temple entrance cutscene (3ds only)

    gSaveContext.sceneFlags[5].swch |= 0x00010000; //remove Ruto cutscene in Water Temple

    gSaveContext.unk_13D0[4] |= 0x01; //Club Moblin cutscene

    //open lowest Vanilla Fire Temple locked door (to prevent key logic lockouts)
    //Not done on keysanity since this lockout is a non issue when FiT keys can be found outside the temple 
    bool keysanity = gSettingsContext.keysanity == KEYSANITY_ANYWHERE || gSettingsContext.keysanity == KEYSANITY_OVERWORLD || gSettingsContext.keysanity == KEYSANITY_ANY_DUNGEON;
    if (gSettingsContext.fireTempleDungeonMode == DUNGEONMODE_VANILLA && !keysanity) {
        gSaveContext.sceneFlags[DUNGEON_FIRE_TEMPLE].swch |= 0x00800000;
    }
    //open middle locked door in Vanilla Water Temple (to prevent key logic lockouts)
    if (gSettingsContext.waterTempleDungeonMode == DUNGEONMODE_VANILLA) {
        gSaveContext.sceneFlags[DUNGEON_WATER_TEMPLE].swch |= 0x00200000;
    }


    /*-----------------------------------
    |THINGS TO SET DEPENDING ON SETTINGS|
    -----------------------------------*/

    if (gSettingsContext.rainbowBridge == RAINBOWBRIDGE_OPEN) {
        gSaveContext.eventChkInf[0x4] |= 0x2000;
    }

    if (gSettingsContext.resolvedStartingAge == AGE_ADULT) {
        gSaveContext.linkAge       = AGE_ADULT;  //age is adult
        gSaveContext.entranceIndex = 0xF4050000; //spawn at temple of time
        gSaveContext.sceneIndex    = 0x6100;     //^
        gSaveContext.childEquips.equipment = 0x1100; //Child equips Kokiri Tunic and Kokiri Boots, no sword or shield
        gSaveContext.adultEquips.equipment = 0x1120; //Adult equips Kokiri Tunic, Kokiri Boots, and Master Sword
        gSaveContext.infTable[29]  = 0x00; //Unset swordless flag
    }

    //set master quest flag for mirror world
    if (gSettingsContext.mirrorWorld == ON) {
        gSaveContext.masterQuestFlag = 1;
    } else {
        gSaveContext.masterQuestFlag = 0;
    }

    if (gSettingsContext.startingTime == STARTINGTIME_NIGHT) {
        gSaveContext.dayTime = 0x1400; //Set night time
    }

    if (gSettingsContext.openDoorOfTime == OPENDOOROFTIME_OPEN) {
        gSaveContext.eventChkInf[0x4] |= 0x0800; //Open Door of Time
    }

    if (gSettingsContext.gerudoFortress == GERUDOFORTRESS_FAST) {
        gSaveContext.eventChkInf[0x9] |= 0x000E; //Free 3 carpenters
        gSaveContext.sceneFlags[DUNGEON_GERUDO_FORTRESS].swch    |= 0x000D01DC; //heard yells/unlocked doors
        gSaveContext.sceneFlags[DUNGEON_GERUDO_FORTRESS].collect |= 0x0000C400; //picked up keys
    } else if (gSettingsContext.gerudoFortress == GERUDOFORTRESS_OPEN) {
        gSaveContext.eventChkInf[0x9] |= 0x000F; //Free all carpenters
        gSaveContext.sceneFlags[DUNGEON_GERUDO_FORTRESS].swch    |= 0x000F01FE; //heard yells/unlocked doors
        gSaveContext.sceneFlags[DUNGEON_GERUDO_FORTRESS].collect |= 0x0000D400; //picked up keys
    }

    if (gSettingsContext.zorasFountain == ZORASFOUNTAIN_OPEN) {
        gSaveContext.eventChkInf[0x3] |= 0x0008; //King Zora Moved Aside
    }

    //Set Skipped Trials
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.forestTrialSkip) ? 0x0800 : 0;
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.fireTrialSkip)   ? 0x4000 : 0;
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.waterTrialSkip)  ? 0x1000 : 0;
    gSaveContext.eventChkInf[0xA] |= (gSettingsContext.spiritTrialSkip) ? 0x2000 : 0;
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.shadowTrialSkip) ? 0x2000 : 0;
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.lightTrialSkip)  ? 0x8000 : 0;

    //If all trials are skipped
    if (gSettingsContext.forestTrialSkip && gSettingsContext.fireTrialSkip && gSettingsContext.waterTrialSkip &&
        gSettingsContext.spiritTrialSkip && gSettingsContext.shadowTrialSkip && gSettingsContext.lightTrialSkip) {
            gSaveContext.eventChkInf[0xC] |= 0x0008; //dispel Ganon's Tower Barrier
    }

    //Give Link a starting stone/medallion if he has one (if he doesn't the value is just 0)
	//If starting inventory is set to start with any stone/medallion, just consider that Link's Pocket
    if(gSettingsContext.startingDungeonReward == 0){
        gSaveContext.questItems |= gSettingsContext.linksPocketRewardBitMask;
    }

    if (gSettingsContext.skipMinigamePhases == SKIP) {
        gSaveContext.sceneFlags[0x48].clear |= 0x00000010; //Remove first Dampe race
    }

    if (gSettingsContext.freeScarecrow == ON) {
        gSaveContext.eventChkInf[0x9] |= 0x1000; //Shown scarecrow's song to bonooru as adult
    }

    if (gSettingsContext.fourPoesCutscene == SKIP) {
        gSaveContext.sceneFlags[3].swch |= 0x08000000; //Remove Poe cutscene in Forest Temple
    }

    if (gSettingsContext.templeOfTimeIntro == SKIP) {
        gSaveContext.eventChkInf[0xA] |= 0x0080; //Remove Temple of Time intro cutscene
    }

    //Move mido away from the path to the Deku Tree in Open Forest
    if (gSettingsContext.openForest == OPENFOREST_OPEN) {
      gSaveContext.eventChkInf[0x0] |= 0x0010;
    }

    gSaveContext.eventChkInf[0x0] |= 0x0004; //spoke to mido
    gSaveContext.eventChkInf[0x0] |= 0x1020; //met deku tree and opened mouth

    gSaveContext.eventChkInf[0x4] |= 0x8020; //entered MS chamber, Pulled MS from pedestal

    gSaveContext.eventChkInf[0xC] |= 0x0020; //Sheik Spawned at MS pedestal as Adult

    SaveFile_SetStartingInventory();
}

void SaveFile_SaveChildBButton(void) {
    gSaveContext.infTable[29] &= 0x00; //Unset the swordless flag when going adult
}

u16 SaveFile_RestoreChildEquips(void) {
    //if Kokiri Sword is not on child B button
    if (gSaveContext.childEquips.buttonItems[0] != ITEM_SWORD_KOKIRI) {
        gSaveContext.infTable[29] |= 0x1; //set swordless flag
    }
    return (gSaveContext.childEquips.equipment & 0xFFF0) | (gSaveContext.equipment & 0x1);
}

u32 SaveFile_CheckGerudoToken(void) {
    return ((gSaveContext.questItems & 0x400000) != 0) ? 1 : 0;
}

void SaveFile_SwapFaroresWind(void) {
    const u32 numWordsToSwap = sizeof(gSaveContext.fw) / sizeof(u32);

    u32* curFWData = (u32*)&gSaveContext.fw;
    u32* storedFWData = &gSaveContext.sceneFlags[0x40].unk;
    u32 tempCur;
    u32 tempStored;

    for (s32 i = 0; i < numWordsToSwap; i++) {
        tempCur = *curFWData;
        tempStored = *storedFWData;
        *curFWData = tempStored;
        *storedFWData = tempCur;

        curFWData++;
        storedFWData += (sizeof(SaveSceneFlags) / sizeof(u32));
    }
}

u8 SaveFile_GetMedallionCount(void) {
    u8 count = 0;

    for (u8 i = 0; i <= 5; i++) {
        count += (gSaveContext.questItems >> i) & 0x1;
    }
    return count;
}

u8 SaveFile_GetStoneCount(void) {
    u8 count = 0;

    for (u8 i = 18; i <= 20; i++) {
        count += (gSaveContext.questItems >> i) & 0x1;
    }
    return count;
}

u8 SaveFile_GetDungeonCount(void) {
    u8 count = 0;

    //Adult dungeons
    for (u8 i = 0x6; i <= 0xA; i++) {
        count += (gSaveContext.eventChkInf[4] >> i) & 0x1;
    }

    //Child dungeons
    count += (gSaveContext.eventChkInf[0] >> 9) & 0x1; //Deku Tree
    count += (gSaveContext.eventChkInf[2] >> 5) & 0x1; //Dodongo's Cavern
    count += (gSaveContext.eventChkInf[3] >> 7) & 0x1; //Jabu Jabu's Belly

    return count;
}

//Resolve the item ID for the starting bottle
static void SaveFile_GiveStartingBottle(u8 startingBottle, InventorySlot bottleSlot) {
    if (startingBottle > STARTINGBOTTLE_NONE) {
        if (startingBottle < STARTINGBOTTLE_BLUE_FIRE) {
            gSaveContext.items[bottleSlot] = ITEM_BOTTLE + (startingBottle - 1);
        //stop subtracting 1 at Blue Fire to skip over Ruto's Letter Item ID
        } else if (startingBottle >= STARTINGBOTTLE_BLUE_FIRE) {
            gSaveContext.items[bottleSlot] = ITEM_BOTTLE + (startingBottle);
        }
    }
}

void SaveFile_SetStartingInventory(void) {
    //give maps and compasses
    if (gSettingsContext.mapsAndCompasses == MAPSANDCOMPASSES_START_WITH) {
        for (u8 i = 0; i < 0xA; i++) {
            gSaveContext.dungeonItems[i] |= 0x6;
        }
    }

    //give small keys
    if (gSettingsContext.keysanity == KEYSANITY_START_WITH) {                       //check if MQ dungeon               MQ : Vanilla key count
        gSaveContext.dungeonKeys[DUNGEON_FOREST_TEMPLE]            = gSettingsContext.forestTempleDungeonMode          ? 6 : 5;
        gSaveContext.dungeonKeys[DUNGEON_FIRE_TEMPLE]              = gSettingsContext.fireTempleDungeonMode            ? 5 : 8;
        gSaveContext.dungeonKeys[DUNGEON_WATER_TEMPLE]             = gSettingsContext.waterTempleDungeonMode           ? 2 : 6;
        gSaveContext.dungeonKeys[DUNGEON_SPIRIT_TEMPLE]            = gSettingsContext.spiritTempleDungeonMode          ? 7 : 5;
        gSaveContext.dungeonKeys[DUNGEON_SHADOW_TEMPLE]            = gSettingsContext.shadowTempleDungeonMode          ? 6 : 5;
        gSaveContext.dungeonKeys[DUNGEON_BOTTOM_OF_THE_WELL]       = gSettingsContext.bottomOfTheWellDungeonMode       ? 2 : 3;
        gSaveContext.dungeonKeys[DUNGEON_GERUDO_TRAINING_GROUNDS]  = gSettingsContext.gerudoTrainingGroundsDungeonMode ? 3 : 9;
        gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_FIRST_PART] = gSettingsContext.ganonsCastleDungeonMode          ? 3 : 2;
        //give starting spirit keys for vanilla key locations
    } else if (gSettingsContext.keysanity == KEYSANITY_VANILLA) {
        if (gSettingsContext.spiritTempleDungeonMode == DUNGEONMODE_MQ) {
            gSaveContext.dungeonKeys[DUNGEON_SPIRIT_TEMPLE] = 3;
        }
    }

    //give boss keys
    if (gSettingsContext.bossKeysanity == BOSSKEYSANITY_START_WITH) {
        for (u8 i = 3; i < 8; i++) {
            gSaveContext.dungeonItems[i] |= 0x1;
        }
    }

    //give Ganon's Castle Boss Key
    if (gSettingsContext.ganonsBossKey == GANONSBOSSKEY_START_WITH) {
        gSaveContext.dungeonItems[DUNGEON_GANONS_CASTLE_SECOND_PART] |= 0x1;
    }

    //starting Nuts and Sticks
    if (gSettingsContext.startingConsumables) {
        gSaveContext.items[SLOT_NUT] = ITEM_NUT;
        gSaveContext.items[SLOT_STICK] = ITEM_STICK;
        gSaveContext.upgrades |= 1 << 17;
        gSaveContext.upgrades |= 1 << 20;
        gSaveContext.ammo[SLOT_NUT] = 20;
        gSaveContext.ammo[SLOT_STICK] = 10;
    }

    //main inventory
    if (gSettingsContext.startingStickCapacity > 0) {
        gSaveContext.upgrades |= ((gSettingsContext.startingStickCapacity + 1) << 17);
        gSaveContext.items[SLOT_STICK] = ITEM_STICK;
        gSaveContext.ammo[SLOT_STICK] = (gSettingsContext.startingStickCapacity + 1) * 10;
    }

    if (gSettingsContext.startingNutCapacity > 0) {
        gSaveContext.upgrades |= ((gSettingsContext.startingNutCapacity + 1) << 20);
        gSaveContext.items[SLOT_NUT] = ITEM_NUT;
        gSaveContext.ammo[SLOT_NUT] = (gSettingsContext.startingNutCapacity + 2) * 10;
    }

    if (gSettingsContext.startingBombBag > 0) {
        gSaveContext.upgrades |= (gSettingsContext.startingBombBag << 3);
        gSaveContext.items[SLOT_BOMB] = ITEM_BOMB;
        gSaveContext.ammo[SLOT_BOMB] = (gSettingsContext.startingBombBag + 1) * 10;
    }

    if (gSettingsContext.startingBombchus > 0) {
        gSaveContext.items[SLOT_BOMBCHU] = ITEM_BOMBCHU;
        gSaveContext.ammo[SLOT_BOMBCHU] = 20;
    }

    if (gSettingsContext.startingBow > 0) {
        gSaveContext.upgrades |= (gSettingsContext.startingBow);
        gSaveContext.items[SLOT_BOW] = ITEM_BOW;
        gSaveContext.ammo[SLOT_BOW] = (gSettingsContext.startingBow + 2) * 10;
    }

    if (gSettingsContext.startingFireArrows) {
        gSaveContext.items[SLOT_ARROW_FIRE] = ITEM_ARROW_FIRE;
    }

    if (gSettingsContext.startingIceArrows) {
        gSaveContext.items[SLOT_ARROW_ICE] = ITEM_ARROW_ICE;
    }

    if (gSettingsContext.startingLightArrows) {
        gSaveContext.items[SLOT_ARROW_LIGHT] = ITEM_ARROW_LIGHT;
    }

    if (gSettingsContext.startingDinsFire) {
        gSaveContext.items[SLOT_DINS_FIRE] = ITEM_DINS_FIRE;
    }

    if (gSettingsContext.startingFaroresWind) {
        gSaveContext.items[SLOT_FARORES_WIND] = ITEM_FARORES_WIND;
    }

    if (gSettingsContext.startingNayrusLove) {
        gSaveContext.items[SLOT_NAYRUS_LOVE] = ITEM_NAYRUS_LOVE;
    }

    if (gSettingsContext.startingSlingshot > 0) {
        gSaveContext.upgrades |= (gSettingsContext.startingSlingshot << 14);
        gSaveContext.items[SLOT_SLINGSHOT] = ITEM_SLINGSHOT;
        gSaveContext.ammo[SLOT_SLINGSHOT] = (gSettingsContext.startingSlingshot + 2) * 10;
    }

    if (gSettingsContext.startingBoomerang) {
        gSaveContext.items[SLOT_BOOMERANG] = ITEM_BOOMERANG;
    }

    if (gSettingsContext.startingLensOfTruth) {
        gSaveContext.items[SLOT_LENS] = ITEM_LENS;
    }

    if (gSettingsContext.startingMagicBean) {
        ItemEffect_BeanPack(&gSaveContext, 0, 0);
        gSaveContext.magic_beans_available = 10;
    }

    if (gSettingsContext.startingMegatonHammer) {
        gSaveContext.items[SLOT_HAMMER] = ITEM_HAMMER;
    }

    if (gSettingsContext.startingHookshot > 0) {
        gSaveContext.items[SLOT_HOOKSHOT] = ITEM_HOOKSHOT + (gSettingsContext.startingHookshot - 1);
    }

    if (gSettingsContext.startingIronBoots) {
        gSaveContext.items[SLOT_IRON_BOOTS] = ITEM_BOOTS_IRON;
    }

    if (gSettingsContext.startingHoverBoots) {
        gSaveContext.items[SLOT_HOVER_BOOTS] = ITEM_BOOTS_HOVER;
    }

    SaveFile_GiveStartingBottle(gSettingsContext.startingBottle1, SLOT_BOTTLE_1);
    SaveFile_GiveStartingBottle(gSettingsContext.startingBottle2, SLOT_BOTTLE_2);
    SaveFile_GiveStartingBottle(gSettingsContext.startingBottle3, SLOT_BOTTLE_3);

    if (gSettingsContext.startingRutoBottle) {
        gSaveContext.items[SLOT_BOTTLE_4] = gSettingsContext.zorasFountain == ZORASFOUNTAIN_OPEN ? ITEM_BOTTLE : ITEM_LETTER_RUTO;
    }

    if (gSettingsContext.startingOcarina > 0) {
        gSaveContext.items[SLOT_OCARINA] = ITEM_OCARINA_FAIRY + (gSettingsContext.startingOcarina - 1);
    }

    if (gSettingsContext.startingKokiriSword) {
        gSaveContext.childEquips.buttonItems[0] = ITEM_SWORD_KOKIRI;
    }

    if (gSettingsContext.startingBiggoronSword == STARTINGBGS_BIGGORON_SWORD) {
        gSaveContext.bgsFlag = 1;
        gSaveContext.bgsHitsLeft = 1;
    }
    if (gSettingsContext.startingBiggoronSword == STARTINGBGS_GIANTS_KNIFE){
        gSaveContext.bgsFlag = 0;
        gSaveContext.bgsHitsLeft = GK_SetDurability();
    }

    if (gSettingsContext.startingMagicMeter == 1) {
        ItemEffect_GiveMagic(&gSaveContext, 0, 0);
    } else if (gSettingsContext.startingMagicMeter == 2) {
        ItemEffect_GiveDoubleMagic(&gSaveContext, 0, 0);
    }

    if (gSettingsContext.startingDoubleDefense) {
        ItemEffect_GiveDefense(&gSaveContext, 0, 0);
    }

    gSaveContext.healthCapacity = gSettingsContext.startingHealth << 4;
    gSaveContext.health         = gSettingsContext.startingHealth << 4;

    gSaveContext.questItems |= gSettingsContext.startingQuestItems;
    gSaveContext.questItems |= gSettingsContext.startingDungeonReward;
    gSaveContext.equipment |= gSettingsContext.startingEquipment;
    gSaveContext.upgrades |= gSettingsContext.startingUpgrades;

    //max rupees
    if (gSettingsContext.startingMaxRupees) {
        u8 wallet = (gSaveContext.upgrades >> 12) & 0x3;
        if (wallet == 0) {
            gSaveContext.rupees = 99;
        } else if (wallet == 1) {
            gSaveContext.rupees = 200;
        } else if (wallet == 2) {
            gSaveContext.rupees = 500;
        } else {
            gSaveContext.rupees = 999;
        }

    }

	//set token count
	gSaveContext.gsTokens = gSettingsContext.startingTokens;

    //Set Epona as freed if Skip Epona Race is enabled and Epona's Song is in the starting inventory
    if (gSettingsContext.skipEponaRace == SKIP && (gSaveContext.questItems >> 13) & 0x1) {
      EventSet(0x18);
    }
}

//We will use the "unk" flags in DMT to represent adult trade ownership
void SaveFile_SetTradeItemAsOwned(u8 itemId) {
    u8 tradeItemNum = itemId - ITEM_POCKET_EGG;

    gSaveContext.sceneFlags[0x60].unk |= (0x1 << tradeItemNum);
}

void SaveFile_UnsetTradeItemAsOwned(u8 itemId) {
    u8 tradeItemNum = itemId - ITEM_POCKET_EGG;

    gSaveContext.sceneFlags[0x60].unk &= ~(0x1 << tradeItemNum);
}

u32 SaveFile_TradeItemIsOwned(u8 itemId) {
    u8 tradeItemNum = itemId - ITEM_POCKET_EGG;

    return (gSaveContext.sceneFlags[0x60].unk & (0x1 << tradeItemNum)) != 0;
}

typedef s32 (*Inventory_ReplaceItem_proc)(GlobalContext* globalCtx, u16 oldItem, u16 newItem);
#define Inventory_ReplaceItem_addr 0x316CEC
#define Inventory_ReplaceItem ((Inventory_ReplaceItem_proc)Inventory_ReplaceItem_addr)

u32 SaveFile_CheckForPocketCuccoHatch(void) {
    // Force the egg into the adult trade slot so that it can hatch
    if (SaveFile_TradeItemIsOwned(ITEM_POCKET_EGG)) {
        gSaveContext.items[SLOT_TRADE_ADULT] = ITEM_POCKET_EGG;
    }

    if (Inventory_ReplaceItem(gGlobalContext, ITEM_POCKET_EGG, ITEM_POCKET_CUCCO)) {
        SaveFile_SetTradeItemAsOwned(ITEM_POCKET_CUCCO);
        SaveFile_UnsetTradeItemAsOwned(ITEM_POCKET_EGG);
        return 1;
    } else {
        return 0;
    }
}

void SaveFile_ResetItemSlotsIfMatchesID(u8 itemSlot) {
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

void SaveFile_SetOwnedTradeItemEquipped(void) {
    if (gSaveContext.sceneFlags[0x60].unk == 0) {
        gSaveContext.items[SLOT_TRADE_ADULT] = 0xFF;
        SaveFile_ResetItemSlotsIfMatchesID(SLOT_TRADE_ADULT);
    } else {
        for (u8 itemId = ITEM_POCKET_EGG; itemId <= ITEM_CLAIM_CHECK; itemId++) {
            if (SaveFile_TradeItemIsOwned(itemId)) {
                gSaveContext.items[SLOT_TRADE_ADULT] = itemId;
                return;
            }
        }
    }
}