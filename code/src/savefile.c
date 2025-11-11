#include "z3D/z3D.h"
#include "settings.h"
#include "item_effect.h"
#include "giants_knife.h"
#include "3ds/types.h"
#include "3ds/extdata.h"
#include <string.h>
#include "entrance.h"
#include "multiplayer.h"
#include "item_override.h"
#include "permadeath.h"
#include "gloom.h"

#define DECLARE_EXTSAVEDATA
#include "savefile.h"

void SaveFile_Init(u32 fileBaseIndex) {
#ifdef ENABLE_DEBUG
    gSaveContext.equipment |= 0x0FFF; // Swords, shields, tunics, boots
    gSaveContext.bgsFlag     = 1;
    gSaveContext.bgsHitsLeft = 1;
    gSaveContext.upgrades |= 0x309;     // bomb bag, quiver, strength, scale
    gSaveContext.questItems |= 0x3FFC0; // songs
    gSaveContext.items[SLOT_OCARINA]      = ITEM_OCARINA_FAIRY;
    gSaveContext.items[SLOT_HOOKSHOT]     = ITEM_LONGSHOT;
    gSaveContext.items[SLOT_HAMMER]       = ITEM_HAMMER;
    gSaveContext.items[SLOT_FARORES_WIND] = ITEM_FARORES_WIND;
    gSaveContext.items[SLOT_DINS_FIRE]    = ITEM_DINS_FIRE;
    gSaveContext.items[SLOT_BOMB]         = ITEM_BOMB;
    gSaveContext.items[SLOT_BOW]          = ITEM_BOW;
    gSaveContext.items[SLOT_ARROW_FIRE]   = ITEM_ARROW_FIRE;
    gSaveContext.items[SLOT_HOVER_BOOTS]  = ITEM_BOOTS_HOVER;
    gSaveContext.items[SLOT_ARROW_LIGHT]  = ITEM_ARROW_LIGHT;
    gSaveContext.items[SLOT_BOTTLE_1]     = ITEM_FISH;
    gSaveContext.magicAcquired            = 1;
    gSaveContext.magicLevel               = 2;
    gSaveContext.magic                    = 48;
    gSaveContext.dungeonKeys[6]           = 8;
    gSaveContext.dungeonKeys[7]           = 5;
    gSaveContext.ammo[2]                  = 20; // bombs
    gSaveContext.ammo[3]                  = 20; // arrows
#endif

    /*-----------------------------------
    |       THINGS TO ALWAYS SET        |
    -----------------------------------*/
    gSaveContext.cutsceneIndex = 0;          // no intro cutscene
    gSaveContext.infTable[0x0] |= 0x01;      // greeted by Saria
    gSaveContext.infTable[0x11] |= 0x0400;   // Met Darunia in Fire Temple
    gSaveContext.infTable[0x14] |= 0x0016;   // Ruto in Jabu can be escorted immediately,
                                             // skip cutscene entering Big Octo room
    gSaveContext.infTable[0x19] |= 0x0100;   // Picked up Magic Container
    gSaveContext.infTable[0x19] |= 0x0020;   // Talked to owl in Lake Hylia
    gSaveContext.infTable[0x8] |= 0x0810;    // Met Malon in Market/Castle Grounds and talked to her once
    gSaveContext.itemGetInf[0x1] |= 0x0008;  // Picked up Deku Seeds
    gSaveContext.eventChkInf[0x3] |= 0x0800; // began Nabooru Battle
    gSaveContext.eventChkInf[0x7] |= 0x01FF; // began boss battles
    gSaveContext.eventChkInf[0x9] |= 0x0010; // Spoke to Nabooru as child
    gSaveContext.eventChkInf[0xB] |= 0x0001; // Dodongo's Cavern intro
    gSaveContext.eventChkInf[0x0] |= 0x0004; // Spoke to mido
    gSaveContext.eventChkInf[0x0] |= 0x1020; // Met deku tree and opened mouth
    gSaveContext.eventChkInf[0x4] |= 0x8020; // Entered MS chamber, Pulled MS from pedestal
    gSaveContext.eventChkInf[0xC] |= 0x0020; // Sheik Spawned at MS pedestal as Adult

    gSaveContext.sceneFlags[0x05].swch |= 0x00010000; // Met Ruto in Water Temple
    gSaveContext.sceneFlags[0x5C].swch |= 0x80000000; // Spoke to owl in Desert Colossus (required for music to play)

    gSaveContext.otherNewEventFlags |= 0x01; // Club Moblin cutscene

    // open lowest Vanilla Fire Temple locked door (to prevent key logic lockouts)
    // Not done on keysanity since this lockout is a non issue when FiT keys can be found outside the temple
    bool keysanity = gSettingsContext.keysanity == KEYSANITY_ANYWHERE ||
                     gSettingsContext.keysanity == KEYSANITY_OVERWORLD ||
                     gSettingsContext.keysanity == KEYSANITY_ANY_DUNGEON;
    if (gSettingsContext.fireTempleDungeonMode == DUNGEONMODE_VANILLA && !keysanity) {
        gSaveContext.sceneFlags[DUNGEON_FIRE_TEMPLE].swch |= 0x00800000;
    }
    // open middle locked door in Vanilla Water Temple (to prevent key logic lockouts)
    if (gSettingsContext.waterTempleDungeonMode == DUNGEONMODE_VANILLA) {
        gSaveContext.sceneFlags[DUNGEON_WATER_TEMPLE].swch |= 0x00200000;
    }

    /*-----------------------------------
    |THINGS TO SET DEPENDING ON SETTINGS|
    -----------------------------------*/

    if (gSettingsContext.rainbowBridge == RAINBOWBRIDGE_OPEN) {
        gSaveContext.eventChkInf[0x4] |= 0x2000;
    }

    gSaveContext.adultEquips.buttonItems[0] = (gSettingsContext.shuffleMasterSword) ? 0xFE : 0xFF;

    if (gSettingsContext.resolvedStartingAge == AGE_ADULT) {
        gSaveContext.sceneIndex = 0x43; // Temple of Time (any scene other than a dungeon or Link's House would work
                                        // too)
        gSaveContext.linkAge               = AGE_ADULT; // age is adult
        gSaveContext.childEquips.equipment = 0x1100; // Child equips Kokiri Tunic and Kokiri Boots, no sword or shield
        gSaveContext.adultEquips.equipment = 0x1120; // Adult equips Kokiri Tunic, Kokiri Boots, and Master Sword
        gSaveContext.equips.buttonItems[0] = gSaveContext.adultEquips.buttonItems[0];
        gSaveContext.infTable[29]          = 0x00; // Unset swordless flag
    }

    if (gSettingsContext.startingTime == STARTINGTIME_NIGHT) {
        gSaveContext.dayTime = 0x1400; // Set night time
    }

    if (gSettingsContext.openDoorOfTime == OPENDOOROFTIME_OPEN) {
        gSaveContext.eventChkInf[0x4] |= 0x0800; // Open Door of Time
    }

    if (gSettingsContext.gerudoFortress == GERUDOFORTRESS_FAST) {
        gSaveContext.eventChkInf[0x9] |= 0x000E;                                // Free 3 carpenters
        gSaveContext.sceneFlags[DUNGEON_THIEVES_HIDEOUT].swch |= 0x000D01DC;    // heard yells/unlocked doors
        gSaveContext.sceneFlags[DUNGEON_THIEVES_HIDEOUT].collect |= 0x0000C400; // picked up keys
        gSaveContext.sceneFlags[DUNGEON_THIEVES_HIDEOUT].clear |= 0x00000032;   // cleared rooms (for Enemy Randomizer)
    } else if (gSettingsContext.gerudoFortress == GERUDOFORTRESS_OPEN) {
        gSaveContext.eventChkInf[0x9] |= 0x000F;                                // Free all carpenters
        gSaveContext.sceneFlags[DUNGEON_THIEVES_HIDEOUT].swch |= 0x000F01FE;    // heard yells/unlocked doors
        gSaveContext.sceneFlags[DUNGEON_THIEVES_HIDEOUT].collect |= 0x0000D400; // picked up keys
        gSaveContext.sceneFlags[DUNGEON_THIEVES_HIDEOUT].clear |= 0x00000036;   // cleared rooms (for Enemy Randomizer)
    }

    if (gSettingsContext.zorasFountain == ZORASFOUNTAIN_OPEN) {
        gSaveContext.eventChkInf[0x3] |= 0x0008; // King Zora Moved Aside
    }

    if (gSettingsContext.openJabu == JABUJABU_OPEN) {
        gSaveContext.eventChkInf[0x3] |= 0x0400; // Offered Fish to Jabu-Jabu
    }

    // Set Skipped Trials
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.forestTrialSkip) ? 0x0800 : 0;
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.fireTrialSkip) ? 0x4000 : 0;
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.waterTrialSkip) ? 0x1000 : 0;
    gSaveContext.eventChkInf[0xA] |= (gSettingsContext.spiritTrialSkip) ? 0x2000 : 0;
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.shadowTrialSkip) ? 0x2000 : 0;
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.lightTrialSkip) ? 0x8000 : 0;

    // If all trials are skipped
    if (gSettingsContext.forestTrialSkip && gSettingsContext.fireTrialSkip && gSettingsContext.waterTrialSkip &&
        gSettingsContext.spiritTrialSkip && gSettingsContext.shadowTrialSkip && gSettingsContext.lightTrialSkip) {
        gSaveContext.eventChkInf[0xC] |= 0x0008; // dispel Ganon's Tower Barrier
    }

    // Give Link a starting stone/medallion if he has one (if he doesn't the value is just 0)
    // If starting inventory is set to start with any stone/medallion, just consider that Link's Pocket
    if (gSettingsContext.startingDungeonReward == 0) {
        gSaveContext.questItems |= gSettingsContext.linksPocketRewardBitMask;
    }

    if (gSettingsContext.skipMinigamePhases == SKIP) {
        gSaveContext.sceneFlags[0x48].clear |= 0x00000010; // Remove first Dampe race
    }

    if (gSettingsContext.freeScarecrow == ON) {
        gSaveContext.eventChkInf[0x9] |= 0x1000; // Shown scarecrow's song to bonooru as adult
    }

    if (gSettingsContext.fourPoesCutscene == SKIP) {
        gSaveContext.sceneFlags[3].swch |= 0x08000000; // Remove Poe cutscene in Forest Temple
    }

    // Move mido away from the path to the Deku Tree in Open Forest
    if (gSettingsContext.openForest == OPENFOREST_OPEN) {
        gSaveContext.eventChkInf[0x0] |= 0x0010;
    }

    SaveFile_InitExtSaveData(fileBaseIndex + gSaveContext.fileNum, 1);
    SaveFile_SetStartingInventory();

    // Ingame Defaults
    gSaveContext.zTargetingSetting    = gSettingsContext.zTargeting;
    gSaveContext.cameraControlSetting = gSettingsContext.cameraControl;
    gSaveContext.motionControlSetting = gSettingsContext.motionControl;
}

void SaveFile_SaveChildBButton(void) {
    gSaveContext.infTable[29] &= 0x00; // Unset the swordless flag when going adult
}

u16 SaveFile_RestoreChildEquips(void) {
    // if Kokiri Sword is not on child B button
    if (gSaveContext.childEquips.buttonItems[0] != ITEM_SWORD_KOKIRI) {
        gSaveContext.infTable[29] |= 0x1;    // set swordless flag
        gSaveContext.buttonStatus[0] = 0xFF; // clear Temp B
    }
    return (gSaveContext.childEquips.equipment & 0xFFF0) | (gSaveContext.equipment & 0x1);
}

u32 SaveFile_CheckGerudoToken(void) {
    return ((gSaveContext.questItems & 0x400000) != 0) ? 1 : 0;
}

void SaveFile_SwapFaroresWind(void) {
    const u32 numWordsToSwap = sizeof(gSaveContext.fw) / sizeof(u32);

    u32* curFWData    = (u32*)&gSaveContext.fw;
    u32* storedFWData = (u32*)&gExtSaveData.fwStored;
    u32 tempCur;
    u32 tempStored;

    for (s32 i = 0; i < numWordsToSwap; i++) {
        tempCur       = *curFWData;
        tempStored    = *storedFWData;
        *curFWData    = tempStored;
        *storedFWData = tempCur;

        curFWData++;
        storedFWData++;
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

    // Adult dungeons
    for (u8 i = 0x6; i <= 0xA; i++) {
        count += (gSaveContext.eventChkInf[4] >> i) & 0x1;
    }

    // Child dungeons
    count += (gSaveContext.eventChkInf[0] >> 9) & 0x1; // Deku Tree
    count += (gSaveContext.eventChkInf[2] >> 5) & 0x1; // Dodongo's Cavern
    count += (gSaveContext.eventChkInf[3] >> 7) & 0x1; // Jabu Jabu's Belly

    return count;
}

u8 SaveFile_GetIsSceneDiscovered(u8 sceneNum) {
    u32 numBits = sizeof(u32) * 8;
    u32 idx     = sceneNum / numBits;
    if (idx < SAVEFILE_SCENES_DISCOVERED_IDX_COUNT) {
        u32 bit = 1 << (sceneNum - (idx * numBits));
        return (gExtSaveData.scenesDiscovered[idx] & bit) != 0;
    }
    return 0;
}

void SaveFile_SetSceneDiscovered(u8 sceneNum) {
    // This is used to reveal Kak Shop items when entered the scene as adult only
    if (sceneNum == 0x30 && gSaveContext.linkAge == AGE_ADULT) {
        EventSet(0x8B);
    }

    if (SaveFile_GetIsSceneDiscovered(sceneNum)) {
        return;
    }

    u16 numBits = sizeof(u32) * 8;
    u32 idx     = sceneNum / numBits;
    if (idx < SAVEFILE_SCENES_DISCOVERED_IDX_COUNT) {
        u32 sceneBit = 1 << (sceneNum - (idx * numBits));
        gExtSaveData.scenesDiscovered[idx] |= sceneBit;
        Multiplayer_Send_DiscoveredScene(idx, sceneBit);
    }
}

u8 SaveFile_GetIsEntranceDiscovered(u16 entranceIndex) {
    u32 numBits = sizeof(u32) * 8;
    u32 idx     = entranceIndex / numBits;
    if (idx < SAVEFILE_ENTRANCES_DISCOVERED_IDX_COUNT) {
        u32 bit = 1 << (entranceIndex - (idx * numBits));
        return (gExtSaveData.entrancesDiscovered[idx] & bit) != 0;
    }
    return 0;
}

void SaveFile_SetEntranceDiscovered(u16 entranceIndex) {

    // Skip if already set to save time from setting the connected or
    // if this is a dynamic entrance
    if (entranceIndex > 0x0820 || SaveFile_GetIsEntranceDiscovered(entranceIndex)) {
        return;
    }

    u16 numBits = sizeof(u32) * 8;
    u32 idx     = entranceIndex / numBits;
    if (idx < SAVEFILE_ENTRANCES_DISCOVERED_IDX_COUNT) {
        u32 entranceBit = 1 << (entranceIndex - (idx * numBits));
        gExtSaveData.entrancesDiscovered[idx] |= entranceBit;
        Multiplayer_Send_DiscoveredEntrance(idx, entranceBit);
        // Set connected
        for (size_t i = 0; i < ENTRANCE_OVERRIDES_MAX_COUNT; i++) {
            if (entranceIndex == rEntranceOverrides[i].index) {
                if (!SaveFile_GetIsEntranceDiscovered(rEntranceOverrides[i].overrideDestination)) {
                    SaveFile_SetEntranceDiscovered(rEntranceOverrides[i].overrideDestination);
                }
                break;
            }
        }
    }
}

// Resolve the item ID for the starting bottle
static void SaveFile_GiveStartingBottle(u8 startingBottle, InventorySlot bottleSlot) {
    if (startingBottle > STARTINGBOTTLE_NONE) {
        if (startingBottle < STARTINGBOTTLE_BLUE_FIRE) {
            gSaveContext.items[bottleSlot] = ITEM_BOTTLE + (startingBottle - 1);
            // stop subtracting 1 at Blue Fire to skip over Ruto's Letter Item ID
        } else if (startingBottle >= STARTINGBOTTLE_BLUE_FIRE) {
            gSaveContext.items[bottleSlot] = ITEM_BOTTLE + (startingBottle);
        }
    }
}

void SaveFile_SetStartingInventory(void) {
    // give maps and compasses
    if (gSettingsContext.mapsAndCompasses == MAPSANDCOMPASSES_START_WITH) {
        for (u8 i = 0; i < 0xA; i++) {
            gSaveContext.dungeonItems[i] |= 0x6;
        }
    }

    // give small keys
    if (gSettingsContext.keysanity == KEYSANITY_START_WITH) { // check if MQ dungeon -> MQ : Vanilla key count
        gSaveContext.dungeonKeys[DUNGEON_FOREST_TEMPLE]      = gSettingsContext.forestTempleDungeonMode ? 6 : 5;
        gSaveContext.dungeonKeys[DUNGEON_FIRE_TEMPLE]        = gSettingsContext.fireTempleDungeonMode ? 5 : 8;
        gSaveContext.dungeonKeys[DUNGEON_WATER_TEMPLE]       = gSettingsContext.waterTempleDungeonMode ? 2 : 6;
        gSaveContext.dungeonKeys[DUNGEON_SPIRIT_TEMPLE]      = gSettingsContext.spiritTempleDungeonMode ? 7 : 5;
        gSaveContext.dungeonKeys[DUNGEON_SHADOW_TEMPLE]      = gSettingsContext.shadowTempleDungeonMode ? 6 : 5;
        gSaveContext.dungeonKeys[DUNGEON_BOTTOM_OF_THE_WELL] = gSettingsContext.bottomOfTheWellDungeonMode ? 2 : 3;
        gSaveContext.dungeonKeys[DUNGEON_GERUDO_TRAINING_GROUNDS] =
            gSettingsContext.gerudoTrainingGroundsDungeonMode ? 3 : 9;
        gSaveContext.dungeonKeys[DUNGEON_INSIDE_GANONS_CASTLE] = gSettingsContext.ganonsCastleDungeonMode ? 3 : 2;
        // give starting spirit keys for vanilla key locations
    } else if (gSettingsContext.keysanity == KEYSANITY_VANILLA) {
        if (gSettingsContext.spiritTempleDungeonMode == DUNGEONMODE_MQ) {
            gSaveContext.dungeonKeys[DUNGEON_SPIRIT_TEMPLE] = 3;
        }
    }

    // give boss keys
    if (gSettingsContext.bossKeysanity == BOSSKEYSANITY_START_WITH) {
        for (u8 i = 3; i < 8; i++) {
            gSaveContext.dungeonItems[i] |= 0x1;
        }
    }

    // give Ganon's Castle Boss Key
    if (gSettingsContext.ganonsBossKey == GANONSBOSSKEY_START_WITH) {
        gSaveContext.dungeonItems[DUNGEON_GANONS_TOWER] |= 0x1;
    }

    // starting Nuts and Sticks
    if (gSettingsContext.startingConsumables) {
        gSaveContext.items[SLOT_NUT]   = ITEM_NUT;
        gSaveContext.items[SLOT_STICK] = ITEM_STICK;
        gSaveContext.ammo[SLOT_NUT]    = 20;
        gSaveContext.ammo[SLOT_STICK]  = 10;
    }

    // main inventory
    u8 insertedInChildItemMenu = 0;

    if (gSettingsContext.startingStickCapacity > 0) {
        gSaveContext.upgrades |= ((gSettingsContext.startingStickCapacity + 1) << 17);
        gSaveContext.items[SLOT_STICK] = ITEM_STICK;
        gSaveContext.ammo[SLOT_STICK]  = (gSettingsContext.startingStickCapacity + 1) * 10;
    } else if (gSettingsContext.startingConsumables) {
        gSaveContext.upgrades |= 1 << 17;
    }

    if (gSettingsContext.startingNutCapacity > 0) {
        gSaveContext.upgrades |= ((gSettingsContext.startingNutCapacity + 1) << 20);
        gSaveContext.items[SLOT_NUT] = ITEM_NUT;
        gSaveContext.ammo[SLOT_NUT]  = (gSettingsContext.startingNutCapacity + 2) * 10;
    } else if (gSettingsContext.startingConsumables) {
        gSaveContext.upgrades |= 1 << 20;
    }

    if (gSettingsContext.startingBombBag > 0) {
        gSaveContext.upgrades |= (gSettingsContext.startingBombBag << 3);
        gSaveContext.items[SLOT_BOMB] = ITEM_BOMB;
        gSaveContext.ammo[SLOT_BOMB]  = (gSettingsContext.startingBombBag + 1) * 10;
    }

    if (gSettingsContext.startingBombchus > 0) {
        gSaveContext.items[SLOT_BOMBCHU] = ITEM_BOMBCHU;
        gSaveContext.ammo[SLOT_BOMBCHU]  = 30 * gSettingsContext.startingBombchus - 10;
    }

    if (gSettingsContext.startingBow > 0) {
        gSaveContext.upgrades |= (gSettingsContext.startingBow);
        gSaveContext.items[SLOT_BOW] = ITEM_BOW;
        gSaveContext.ammo[SLOT_BOW]  = (gSettingsContext.startingBow + 2) * 10;
    }

    if (gSettingsContext.startingFireArrows) {
        gSaveContext.items[SLOT_ARROW_FIRE] = ITEM_ARROW_FIRE;
        if (gSettingsContext.startingBow == 0) {
            gSaveContext.itemMenuAdult[insertedInChildItemMenu]   = ItemSlots[ITEM_ARROW_FIRE];
            gSaveContext.itemMenuChild[insertedInChildItemMenu++] = ItemSlots[ITEM_ARROW_FIRE];
        }
    }

    if (gSettingsContext.startingIceArrows) {
        gSaveContext.items[SLOT_ARROW_ICE] = ITEM_ARROW_ICE;
        if (gSettingsContext.startingBow == 0) {
            gSaveContext.itemMenuAdult[insertedInChildItemMenu]   = ItemSlots[ITEM_ARROW_ICE];
            gSaveContext.itemMenuChild[insertedInChildItemMenu++] = ItemSlots[ITEM_ARROW_ICE];
        }
    }

    if (gSettingsContext.startingLightArrows) {
        gSaveContext.items[SLOT_ARROW_LIGHT] = ITEM_ARROW_LIGHT;
        if (gSettingsContext.startingBow == 0) {
            gSaveContext.itemMenuAdult[insertedInChildItemMenu]   = ItemSlots[ITEM_ARROW_LIGHT];
            gSaveContext.itemMenuChild[insertedInChildItemMenu++] = ItemSlots[ITEM_ARROW_LIGHT];
        }
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
        gSaveContext.ammo[SLOT_SLINGSHOT]  = (gSettingsContext.startingSlingshot + 2) * 10;
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

    SaveFile_GiveStartingBottle(gSettingsContext.startingBottle1, SLOT_BOTTLE_1);
    SaveFile_GiveStartingBottle(gSettingsContext.startingBottle2, SLOT_BOTTLE_2);
    SaveFile_GiveStartingBottle(gSettingsContext.startingBottle3, SLOT_BOTTLE_3);
    SaveFile_GiveStartingBottle(gSettingsContext.startingBottle4, SLOT_BOTTLE_4);

    if (gSettingsContext.startingRutoBottle) {
        gSaveContext.items[SLOT_BOTTLE_4] =
            gSettingsContext.zorasFountain == ZORASFOUNTAIN_OPEN ? ITEM_BOTTLE : ITEM_LETTER_RUTO;
    }

    if (gSettingsContext.startingChildTrade) {
        gSaveContext.items[SLOT_TRADE_CHILD] = ITEM_MASK_BUNNY;
        SaveFile_BorrowMask(0x21);
        gSaveContext.sceneFlags[0x60].unk |= 0x1 << 0x11;
    }

    if (gSettingsContext.startingOcarina > 0) {
        gSaveContext.items[SLOT_OCARINA] = ITEM_OCARINA_FAIRY + (gSettingsContext.startingOcarina - 1);
    }

    if (gSettingsContext.startingKokiriSword) {
        gSaveContext.childEquips.buttonItems[0] = ITEM_SWORD_KOKIRI;
    }

    if (gSettingsContext.startingBiggoronSword == STARTINGBGS_BIGGORON_SWORD) {
        gSaveContext.bgsFlag     = 1;
        gSaveContext.bgsHitsLeft = 1;
    }
    if (gSettingsContext.startingBiggoronSword == STARTINGBGS_GIANTS_KNIFE) {
        gSaveContext.bgsFlag     = 0;
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

    gSaveContext.healthCapacity = gSettingsContext.startingHearts << 4;
    gSaveContext.health         = gSettingsContext.startingHearts << 4;

    gSaveContext.questItems |= gSettingsContext.startingQuestItems;
    gSaveContext.questItems |= gSettingsContext.startingDungeonReward;
    gSaveContext.equipment |= gSettingsContext.startingEquipment;
    gSaveContext.upgrades |= gSettingsContext.startingUpgrades;

    // max rupees
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

    // set token count
    gSaveContext.gsTokens = gSettingsContext.startingTokens;

    // Set Epona as freed if Skip Epona Race is enabled and Epona's Song is in the starting inventory
    if (gSettingsContext.skipEponaRace == SKIP && (gSaveContext.questItems >> 13) & 0x1) {
        EventSet(0x18);
        gSaveContext.horseData.pos.y = 0xF000; // place Epona OoB, so you can't reach her without playing the song
    }

    // Set owned ocarina buttons. If the shuffle option is disabled, this value will be ignored.
    gExtSaveData.extInf[EXTINF_OCARINA_BUTTONS] = gSettingsContext.startingOcarinaButtons;

    // Set owned enemy souls. If the shuffle option is disabled, these values will be ignored.
    for (u32 i = 0; i < sizeof(gSettingsContext.startingEnemySouls); i++) {
        gExtSaveData.extInf[EXTINF_ENEMYSOULSFLAGS_START + i] = gSettingsContext.startingEnemySouls[i];
    }
}

// We will use the "unk" flags in DMT to represent adult trade ownership
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

u8 SaveFile_WeirdEggOwned(void) {
    return (gSaveContext.sceneFlags[0x60].unk >> 0x10) & 0x1;
}

u8 SaveFile_ZeldasLetterOwned(void) {
    return (gSaveContext.sceneFlags[0x60].unk >> 0x11) & 0x1;
}

u8 SaveFile_ChildTradeSlots(void) {
    return SaveFile_WeirdEggOwned() + SaveFile_ZeldasLetterOwned();
}

u8 SaveFile_WeirdEggHatched(void) {
    return (gSaveContext.sceneFlags[0x60].unk >> 0x12) & 0x1;
}

u8 SaveFile_CurrentMask(void) {
    return (gSaveContext.sceneFlags[0x60].unk >> 0x13) & 0x7;
}

u32 SaveFile_MaskSlotValue(void) {
    u8 mask = SaveFile_CurrentMask();

    // Sold but not paid for mask
    if (mask < 4 && gSaveContext.itemGetInf[3] & (0x1 << (0x8 + mask)) &&
        !(gSaveContext.eventChkInf[8] & (0x1 << (0xC + mask)))) {
        return ITEM_SOLD_OUT;
    }

    return ITEM_MASK_KEATON + mask;
}

void SaveFile_BorrowMask(s16 SI_ItemId) {
    // SI ids are in a different order to normal item ids so need to convert
    u8 itemId;
    switch (SI_ItemId) {
        case 0x1E:
            itemId = ITEM_MASK_KEATON;
            break;
        case 0x1F:
            itemId = ITEM_MASK_SPOOKY;
            break;
        case 0x20:
            itemId = ITEM_MASK_SKULL;
            break;
        case 0x21:
            itemId = ITEM_MASK_BUNNY;
            break;
        case 0x22:
            itemId = ITEM_MASK_TRUTH;
            break;
        case 0x23:
            itemId = ITEM_MASK_ZORA;
            break;
        case 0x24:
            itemId = ITEM_MASK_GORON;
            break;
        case 0x25:
            itemId = ITEM_MASK_GERUDO;
            break;
    }

    // Ensure flag for obtaining Keaton mask is set in case complete mask quest is enabled
    gSaveContext.itemGetInf[2] |= 0x1 << 0x3;

    gSaveContext.sceneFlags[0x60].unk &= ~(0x7 << 0x13);
    gSaveContext.sceneFlags[0x60].unk |= (itemId - ITEM_MASK_KEATON) << 0x13;
}

typedef s32 (*Inventory_ReplaceItem_proc)(GlobalContext* globalCtx, u16 oldItem, u16 newItem);
#define Inventory_ReplaceItem ((Inventory_ReplaceItem_proc)GAME_ADDR(0x316CEC))

u32 SaveFile_CheckForWeirdEggHatch(void) {
    // Force the egg into the child trade slot so that it can hatch
    if (SaveFile_WeirdEggOwned() & !SaveFile_WeirdEggHatched()) {
        gSaveContext.items[SLOT_TRADE_CHILD] = ITEM_WEIRD_EGG;
    }

    if (Inventory_ReplaceItem(gGlobalContext, ITEM_WEIRD_EGG, ITEM_CHICKEN)) {
        gSaveContext.sceneFlags[0x60].unk |= 0x1 << 0x12;
        return 1;
    } else {
        return 0;
    }
}

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

u8 SaveFile_InventoryMenuHasSlot(u8 adult, u8 itemSlot) {
    u8* itemMenu = adult ? gSaveContext.itemMenuAdult : gSaveContext.itemMenuChild;
    for (size_t i = 0; i < 0x18; i++) {
        if (itemMenu[i] == itemSlot) {
            return 1;
        }
    }
    return 0;
}

void SaveFile_SetOwnedTradeItemEquipped(void) {
    if ((gSaveContext.sceneFlags[0x60].unk & 0x7FF) == 0) {
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

s8 SaveFile_GetIgnoreMaskReactionOption(u32 reactionSet) {
    // This option somehow breaks talking to the Kakariko Mountain Gate guard, so use a workaround
    if (reactionSet == 0x3C && PLAYER->currentMask == 1 && (gSaveContext.infTable[7] & 0x80) == 0) {
        return 0;
    }
    return gExtSaveData.option_IgnoreMaskReaction;
}

void SaveFile_InitExtSaveData(u32 saveNumber, u8 fromSaveCreation) {
    // Reset entire struct to 0 before setting specific fields.
    memset(&gExtSaveData, 0, sizeof(gExtSaveData));

    gExtSaveData.version = EXTSAVEDATA_VERSION; // Do not change this line
    gExtSaveData.extInf[EXTINF_MASTERSWORDFLAGS] =
        (gSettingsContext.shuffleMasterSword && !(gSettingsContext.startingEquipment & 0x2)) ? 0 : 1;
    gExtSaveData.permadeath = fromSaveCreation ? gSettingsContext.permadeath : 0;
    // Ingame Options
    gExtSaveData.option_EnableBGM          = gSettingsContext.playMusic;
    gExtSaveData.option_EnableSFX          = gSettingsContext.playSFX;
    gExtSaveData.option_NaviNotifications  = gSettingsContext.naviNotifications;
    gExtSaveData.option_IgnoreMaskReaction = gSettingsContext.ignoreMaskReaction;
    gExtSaveData.option_SkipSongReplays    = gSettingsContext.skipSongReplays;
    gExtSaveData.option_FreeCamControl     = gSettingsContext.freeCamControl;
}

void SaveFile_LoadExtSaveData(u32 saveNumber) {
    char path[] = "/0.bin";
    u32 version;
    u64 fileSize;

    Result res;
    FS_Archive fsa;
    Handle fileHandle;

    if (R_FAILED(res = extDataMount(&fsa))) {
        SaveFile_InitExtSaveData(saveNumber, 0);
        return;
    }

    path[1] = saveNumber + '0';

    // Load default values if the file does not exist
    if (R_FAILED(res = extDataOpen(&fileHandle, fsa, path))) {
        extDataUnmount(fsa);
        SaveFile_InitExtSaveData(saveNumber, 0);
        return;
    }

    // Delete the file and load default values if the size does not match or the version is different
    FSFILE_GetSize(fileHandle, &fileSize);
    extDataReadFile(fileHandle, &version, 0, sizeof(version));
    if (fileSize != sizeof(gExtSaveData) || version != EXTSAVEDATA_VERSION) {
        extDataClose(fileHandle);
        extDataDeleteFile(fsa, path);
        extDataUnmount(fsa);
        SaveFile_InitExtSaveData(saveNumber, 0);
        return;
    }

    extDataReadFile(fileHandle, &gExtSaveData, 0, sizeof(gExtSaveData));

    extDataClose(fileHandle);
    extDataUnmount(fsa);
}

void SaveFile_SaveExtSaveData(u32 saveNumber) {
    char path[] = "/0.bin";

    Result res;
    FS_Archive fsa;

    if (R_FAILED(res = extDataMount(&fsa))) {
        return;
    }

    path[1] = saveNumber + '0';

    extDataWriteFileDirectly(fsa, path, &gExtSaveData, 0, sizeof(gExtSaveData));

    extDataUnmount(fsa);
}

void SaveFile_BeforeCopy(s32 srcFileNum) {
    // When the game writes the copied savefile, it calls SaveFile_SaveExtSaveData,
    // so in order to properly copy the ExtData they first need to be loaded from the source savefile.
    SaveFile_LoadExtSaveData(srcFileNum);
}

void SaveFile_EnforceHealthLimit(void) {
    u16 healthLimit = (gSaveContext.healthCapacity == 0) ? 2 : gSaveContext.healthCapacity;
    if (gSaveContext.health > healthLimit) {
        gSaveContext.health = healthLimit;
    } else if (gSaveContext.health < 0) {
        gSaveContext.health = 0;
    }
}

u8 SaveFile_SwordlessPatchesEnabled(void) {
    return gSettingsContext.shuffleMasterSword && !(gExtSaveData.extInf[EXTINF_MASTERSWORDFLAGS] & 1);
}

u8 SaveFile_BecomeAdult(void) {
    // Normal behaviour checks for 0xFF
    if (gSaveContext.adultEquips.buttonItems[0] == 0xFF) {
        if (SaveFile_SwordlessPatchesEnabled()) {
            // Simulate adult reset but without equipping/giving master sword
            gSaveContext.adultEquips.buttonItems[0] = 0xFE;
            gSaveContext.adultEquips.equipment      = 0x1120;
            return 1;
        } else {
            // Normal behaviour if supposed to get master sword equipped
            return 0;
        }
    }

    // If first time going adult update adult equips (equip master sword if in inventory)
    if (gSaveContext.adultEquips.equipment == 0) {
        gSaveContext.adultEquips.equipment = 0x1120 | (gSaveContext.equipment & 0x2);
        if (gSaveContext.equipment & 0x2) {
            gSaveContext.adultEquips.buttonItems[0] = 0x3C;
        }
    }

    // Return to code for 2nd time becoming adult
    return 1;
}

void SaveFile_LoadFileSwordless(void) {
    if (gSaveContext.linkAge == 0) {
        // Push pedestal item if adult and haven't received yet
        if (gSettingsContext.shuffleMasterSword && !(gExtSaveData.extInf[EXTINF_MASTERSWORDFLAGS] & 2)) {
            ItemOverride_PushDelayedOverride(0x00);
        }

        // Mark pedestal item collected
        gExtSaveData.extInf[EXTINF_MASTERSWORDFLAGS] |= 2;
    }
}

void SaveFile_BeforeLoadGame(u32 saveNumber) {
    SaveFile_LoadExtSaveData(saveNumber);
}

void SaveFile_AfterLoadGame(void) {
    // Give Ganon BK if Triforce Hunt has been completed
    if (gSettingsContext.triforceHunt == ON && gExtSaveData.triforcePieces >= gSettingsContext.triforcePiecesRequired &&
        (gSaveContext.dungeonItems[DUNGEON_GANONS_TOWER] & 1) == 0) {

        ItemOverride_PushHardcodedItem(GI_GANON_BOSS_KEY);
    }
}

void SaveFile_OnGameOver(void) {
    Gloom_OnDeath();
    Permadeath_DeleteSave();
}

void SaveFile_SetCollectedRandomizedRespawningCollectibleFlag(s16 sceneNum, u16 collectibleFlag) {
    if (collectibleFlag >= 0x20 && collectibleFlag < 0x40) {
        gExtSaveData.collectedRandomizedRespawningRupeeFlags[gGlobalContext->sceneNum] |=
            (1 << (collectibleFlag - 0x20));
    }
    if (collectibleFlag >= 0x40) {
        gExtSaveData.collectedRandomizedRupeeCircleRupeeFlags[gGlobalContext->sceneNum] |=
            (1 << (collectibleFlag - 0x40));
    }
}

u8 SaveFile_GetCollectedRandomizedRespawningCollectibleFlag(s16 sceneNum, u16 collectibleFlag) {
    u32 saveFlags;
    u16 shiftBy;
    if (collectibleFlag >= 0x20 && collectibleFlag < 0x40) {
        saveFlags = gExtSaveData.collectedRandomizedRespawningRupeeFlags[sceneNum];
        shiftBy   = 0x20;
    }
    if (collectibleFlag >= 0x40) {
        saveFlags = gExtSaveData.collectedRandomizedRupeeCircleRupeeFlags[sceneNum];
        shiftBy   = 0x40;
    }

    return ((saveFlags & (1 << (collectibleFlag - shiftBy))) > 0);
}
