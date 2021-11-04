#include "../include/z3D/z3D.h"
#include "grotto.h"
#include "savefile.h"

// Information necessary for entering each grotto
static const GrottoLoadInfo grottoLoadTable[NUM_GROTTOS] = {
    {.entranceIndex = 0x05BC, .content = 0xFD, .scene = 0x5C}, // Desert Colossus -> Colossus Grotto
    {.entranceIndex = 0x05A4, .content = 0xEF, .scene = 0x57}, // Lake Hylia -> LH Grotto
    {.entranceIndex = 0x05BC, .content = 0xEB, .scene = 0x54}, // Zora River -> ZR Storms Grotto
    {.entranceIndex = 0x036D, .content = 0xE6, .scene = 0x54}, // Zora River -> ZR Fairy Grotto
    {.entranceIndex = 0x003F, .content = 0x29, .scene = 0x54}, // Zora River -> ZR Open Grotto
    {.entranceIndex = 0x05A4, .content = 0xF9, .scene = 0x61}, // DMC Lower Nearby -> DMC Hammer Grotto
    {.entranceIndex = 0x003F, .content = 0x7A, .scene = 0x61}, // DMC Upper Nearby -> DMC Upper Grotto
    {.entranceIndex = 0x05A4, .content = 0xFB, .scene = 0x62}, // GC Grotto Platform -> GC Grotto
    {.entranceIndex = 0x003F, .content = 0x57, .scene = 0x60}, // Death Mountain -> DMT Storms Grotto
    {.entranceIndex = 0x05FC, .content = 0xF8, .scene = 0x60}, // Death Mountain Summit -> DMT Cow Grotto
    {.entranceIndex = 0x003F, .content = 0x28, .scene = 0x52}, // Kak Backyard -> Kak Open Grotto
    {.entranceIndex = 0x05A0, .content = 0xE7, .scene = 0x52}, // Kakariko Village -> Kak Redead Grotto
    {.entranceIndex = 0x05B8, .content = 0xF6, .scene = 0x5F}, // Hyrule Castle Grounds -> HC Storms Grotto
    {.entranceIndex = 0x05C0, .content = 0xE1, .scene = 0x51}, // Hyrule Field -> HF Tektite Grotto
    {.entranceIndex = 0x0598, .content = 0xE5, .scene = 0x51}, // Hyrule Field -> HF Near Kak Grotto
    {.entranceIndex = 0x036D, .content = 0xFF, .scene = 0x51}, // Hyrule Field -> HF Fairy Grotto
    {.entranceIndex = 0x003F, .content = 0x00, .scene = 0x51}, // Hyrule Field -> HF Near Market Grotto
    {.entranceIndex = 0x05A8, .content = 0xE4, .scene = 0x51}, // Hyrule Field -> HF Cow Grotto
    {.entranceIndex = 0x059C, .content = 0xE6, .scene = 0x51}, // Hyrule Field -> HF Inside Fence Grotto
    {.entranceIndex = 0x003F, .content = 0x03, .scene = 0x51}, // Hyrule Field -> HF Open Grotto
    {.entranceIndex = 0x003F, .content = 0x22, .scene = 0x51}, // Hyrule Field -> HF Southeast Grotto
    {.entranceIndex = 0x05A4, .content = 0xFC, .scene = 0x63}, // Lon Lon Ranch -> LLR Grotto
    {.entranceIndex = 0x05B4, .content = 0xED, .scene = 0x56}, // SFM Entryway -> SFM Wolfos Grotto
    {.entranceIndex = 0x05BC, .content = 0xEE, .scene = 0x56}, // Sacred Forest Meadow -> SFM Storms Grotto
    {.entranceIndex = 0x036D, .content = 0xFF, .scene = 0x56}, // Sacred Forest Meadow -> SFM Fairy Grotto
    {.entranceIndex = 0x05B0, .content = 0xF5, .scene = 0x5B}, // LW Beyond Mido -> LW Scrubs Grotto
    {.entranceIndex = 0x003F, .content = 0x14, .scene = 0x5B}, // Lost Woods -> LW Near Shortcuts Grotto
    {.entranceIndex = 0x003F, .content = 0x2C, .scene = 0x55}, // Kokiri Forest -> KF Storms Grotto
    {.entranceIndex = 0x036D, .content = 0xFF, .scene = 0x58}, // Zoras Domain -> ZD Storms Grotto
    {.entranceIndex = 0x036D, .content = 0xFF, .scene = 0x5D}, // Gerudo Fortress -> GF Storms Grotto
    {.entranceIndex = 0x05BC, .content = 0xF0, .scene = 0x5A}, // GV Fortress Side -> GV Storms Grotto
    {.entranceIndex = 0x05AC, .content = 0xF2, .scene = 0x5A}, // GV Grotto Ledge -> GV Octorok Grotto
    {.entranceIndex = 0x05C4, .content = 0xF3, .scene = 0x5B}, // LW Beyond Mido -> Deku Theater
};

// Information necessary for setting up returning from a grotto
static const GrottoReturnInfo grottoReturnTable[NUM_GROTTOS] = {
    {.entranceIndex = 0x0123, .room = 0x00, .angle = 0xA71C, .pos = {.x =    62.5078f, .y =   -32.0f, .z = -1296.2f}},   // Colossus Grotto -> Desert Colossus
    {.entranceIndex = 0x0102, .room = 0x00, .angle = 0x0000, .pos = {.x = -3039.34f,   .y = -1033.0f, .z =  6080.74f}},  // LH Grotto -> Lake Hylia
    {.entranceIndex = 0x00EA, .room = 0x00, .angle = 0x0000, .pos = {.x = -1630.05f,   .y =   100.0f, .z =  -132.104f}}, // ZR Storms Grotto -> Zora River
    {.entranceIndex = 0x00EA, .room = 0x00, .angle = 0xE000, .pos = {.x =   670.507f,  .y =   570.0f, .z =  -361.853f}}, // ZR Fairy Grotto -> Zora River
    {.entranceIndex = 0x00EA, .room = 0x00, .angle = 0x8000, .pos = {.x =   362.29f,   .y =   570.0f, .z =   137.63f}},  // ZR Open Grotto -> Zora River
    {.entranceIndex = 0x0246, .room = 0x01, .angle = 0x31C7, .pos = {.x = -1684.52f,   .y =   722.0f, .z =  -474.667f}}, // DMC Hammer Grotto -> DMC Lower Local
    {.entranceIndex = 0x0147, .room = 0x01, .angle = 0x238E, .pos = {.x =    35.8008f, .y =  1265.0f, .z =  1766.67f}},  // DMC Upper Grotto -> DMC Upper Local
    {.entranceIndex = 0x014D, .room = 0x03, .angle = 0x0000, .pos = {.x =  1104.73f,   .y =   580.0f, .z = -1182.41f}},  // GC Grotto -> GC Grotto Platform
    {.entranceIndex = 0x01B9, .room = 0x00, .angle = 0x8000, .pos = {.x =  -387.584f,  .y =  1386.0f, .z = -1213.05f}},  // DMT Storms Grotto -> Death Mountain
    {.entranceIndex = 0x01B9, .room = 0x00, .angle = 0x8000, .pos = {.x =  -691.022f,  .y =  1946.0f, .z =  -281.969f}}, // DMT Cow Grotto -> Death Mountain Summit
    {.entranceIndex = 0x00DB, .room = 0x00, .angle = 0x0000, .pos = {.x =   855.238f,  .y =    80.0f, .z =  -253.095f}}, // Kak Open Grotto -> Kak Backyard
    {.entranceIndex = 0x00DB, .room = 0x00, .angle = 0x0000, .pos = {.x =  -401.873f,  .y =     0.0f, .z =   402.792f}}, // Kak Redead Grotto -> Kakariko Village
    {.entranceIndex = 0x0138, .room = 0x00, .angle = 0x9555, .pos = {.x =  1009.02f,   .y =  1571.0f, .z =   855.532f}}, // HC Storms Grotto -> Castle Grounds
    {.entranceIndex = 0x01F9, .room = 0x00, .angle = 0x1555, .pos = {.x = -4949.58f,   .y =  -300.0f, .z =  2837.59f}},  // HF Tektite Grotto -> Hyrule Field
    {.entranceIndex = 0x01F9, .room = 0x00, .angle = 0xC000, .pos = {.x =  2050.6f,    .y =    20.0f, .z =  -160.397f}}, // HF Near Kak Grotto -> Hyrule Field
    {.entranceIndex = 0x01F9, .room = 0x00, .angle = 0x0000, .pos = {.x = -4452.66f,   .y =  -300.0f, .z =  -426.191f}}, // HF Fairy Grotto -> Hyrule Field
    {.entranceIndex = 0x01F9, .room = 0x00, .angle = 0xE000, .pos = {.x = -1429.56f,   .y =     0.0f, .z =   817.775f}}, // HF Near Market Grotto -> Hyrule Field
    {.entranceIndex = 0x01F9, .room = 0x00, .angle = 0x0000, .pos = {.x = -7874.07f,   .y =  -300.0f, .z =  6921.31f}},  // HF Cow Grotto -> Hyrule Field
    {.entranceIndex = 0x01F9, .room = 0x00, .angle = 0xEAAB, .pos = {.x = -4989.13f,   .y =  -700.0f, .z = 13821.1f}},   // HF Inside Fence Grotto -> Hyrule Field
    {.entranceIndex = 0x01F9, .room = 0x00, .angle = 0x8000, .pos = {.x = -4022.61f,   .y =  -700.0f, .z = 13859.5f}},   // HF Open Grotto -> Hyrule Field
    {.entranceIndex = 0x01F9, .room = 0x00, .angle = 0x9555, .pos = {.x =  -265.313f,  .y =  -500.0f, .z = 12343.2f}},   // HF Southeast Grotto -> Hyrule Field
    {.entranceIndex = 0x0157, .room = 0x00, .angle = 0xAAAB, .pos = {.x =  1799.92f,   .y =     0.0f, .z =  1500.82f}},  // LLR Grotto -> Lon Lon Ranch
    {.entranceIndex = 0x00FC, .room = 0x00, .angle = 0x8000, .pos = {.x =  -189.861f,  .y =     0.0f, .z =  1898.09f}},  // SFM Wolfos Grotto -> SFM Entryway
    {.entranceIndex = 0x00FC, .room = 0x00, .angle = 0xAAAB, .pos = {.x =   314.853f,  .y =   480.0f, .z = -2300.39f}},  // SFM Storms Grotto -> Sacred Forest Meadow
    {.entranceIndex = 0x00FC, .room = 0x00, .angle = 0x0000, .pos = {.x =    55.034f,  .y =     0.0f, .z =   206.595f}}, // SFM Fairy Grotto -> Sacred Forest Meadow
    {.entranceIndex = 0x01A9, .room = 0x08, .angle = 0x2000, .pos = {.x =   676.994f,  .y =     0.0f, .z = -2526.2f}},   // LW Scrubs Grotto -> LW Beyond Mido
    {.entranceIndex = 0x011E, .room = 0x02, .angle = 0xE000, .pos = {.x =   914.755f,  .y =     0.0f, .z =  -915.43f}},  // LW Near Shortcuts Grotto -> Lost Woods
    {.entranceIndex = 0x0286, .room = 0x00, .angle = 0x4000, .pos = {.x =  -507.065f,  .y =   380.0f, .z = -1220.43f}},  // KF Storms Grotto -> Kokiri Forest
    {.entranceIndex = 0x0108, .room = 0x01, .angle = 0xD555, .pos = {.x =  -855.68f,   .y =    14.0f, .z =  -474.422f}}, // ZD Storms Grotto -> Zoras Domain
    {.entranceIndex = 0x0129, .room = 0x00, .angle = 0x4000, .pos = {.x =   380.521f,  .y =   333.0f, .z = -1560.74f}},  // GF Storms Grotto -> Gerudo Fortress
    {.entranceIndex = 0x022D, .room = 0x00, .angle = 0x9555, .pos = {.x = -1326.34f,   .y =    15.0f, .z =  -983.994f}}, // GV Storms Grotto -> GV Fortress Side
    {.entranceIndex = 0x0117, .room = 0x00, .angle = 0x8000, .pos = {.x =   291.513f,  .y =  -555.0f, .z =  1478.39f}},  // GV Octorok Grotto -> GV Grotto Ledge
    {.entranceIndex = 0x01A9, .room = 0x06, .angle = 0x4000, .pos = {.x =    85.281f,  .y =   -20.0f, .z = -1601.42f}},  // Deku Theater -> LW Beyond Mido
};

static s16 grottoExitList[NUM_GROTTOS] = {0};
static s16 grottoLoadList[NUM_GROTTOS] = {0};
static s8 grottoId = 0xFF;
static s8 entranceFromGrottoActor = 0;

// Initialize both lists so that each index refers to itself. An index referring
// to itself means that the entrance is not shuffled. Indices will be overwritten
// later in Entrance_Init() in entrance.c if entrance shuffle is enabled.
// For the grotto load list, the entrance index is 0x1000 + the grotto id
// For the grotto exit list, the entrance index is 0x2000 + the grotto id
void Grotto_InitExitAndLoadLists(void) {
    for (u8 i = 0; i < NUM_GROTTOS; i++) {
        grottoLoadList[i] = 0x1000 + i;
        grottoExitList[i] = 0x2000 + i;
    }
}

void Grotto_SetExitOverride(s16 originalIndex, s16 overrideIndex) {
    s16 id = originalIndex & 0x00FF;
    grottoExitList[id] = overrideIndex;
}

void Grotto_SetLoadOverride(s16 originalIndex, s16 overrideIndex) {
    s16 id = originalIndex & 0x00FF;
    grottoLoadList[id] = overrideIndex;
}

static void Grotto_SetupReturnInfo(GrottoReturnInfo grotto) {
  // Set necessary grotto return data
  gSaveContext.respawn[RESPAWN_MODE_RETURN].entranceIndex = grotto.entranceIndex;
  gSaveContext.respawn[RESPAWN_MODE_RETURN].roomIndex = grotto.room;
  gSaveContext.respawn[RESPAWN_MODE_RETURN].playerParams = 0x04FF; // exiting grotto with no initial camera focus
  gSaveContext.respawn[RESPAWN_MODE_RETURN].yaw = grotto.angle;
  gSaveContext.respawn[RESPAWN_MODE_RETURN].pos = grotto.pos;
  gSaveContext.respawn[RESPAWN_MODE_RETURN].tempSwchFlags = gGlobalContext->actorCtx.flags.tempSwch;
  gSaveContext.respawn[RESPAWN_MODE_RETURN].tempCollectFlags = gGlobalContext->actorCtx.flags.tempCollect;

  gSaveContext.respawnFlag = 2;
}

// Translates and overrides the passed in entrance index if it corresponds to a
// special grotto entrance (grotto load or returnpoint)
s16 Grotto_CheckSpecialEntrance(s16 nextEntranceIndex) {

    // If Link hits a grotto exit, load the entrance index from the grotto exit list
    // based on the current grotto ID
    if (nextEntranceIndex == 0x7FFF) {
        nextEntranceIndex = grottoExitList[grottoId];
    }

    // Get the new grotto id from the next entrance
    grottoId = nextEntranceIndex & 0x00FF;
    SaveFile_SetEntranceDiscovered(nextEntranceIndex);

    // Grotto Returns
    if (nextEntranceIndex >= 0x2000 && nextEntranceIndex < 0x2000 + NUM_GROTTOS) {

        GrottoReturnInfo grotto = grottoReturnTable[grottoId];
        Grotto_SetupReturnInfo(grotto);
        gGlobalContext->fadeOutTransition = 3;
        gSaveContext.nextTransition = 3;

        // This keeps the transition lighting consistent and makes
        // grotto entrance -> grotto return point entrances work properly
        nextEntranceIndex = entranceFromGrottoActor ? grotto.entranceIndex : 0x7FFF;

    // Grotto Loads
    } else if (nextEntranceIndex >= 0x1000 && nextEntranceIndex < 0x2000) {

        GrottoLoadInfo grotto = grottoLoadTable[grottoId];
        gSaveContext.respawn[RESPAWN_MODE_RETURN].data = grotto.content;
        nextEntranceIndex = grotto.entranceIndex;

    // Otherwise just unset the current grotto ID
    } else {
        grottoId = 0xFF;
    }

    entranceFromGrottoActor = 0;
    return nextEntranceIndex;
}

// Override the entrance index when entering into a grotto actor
// thisx - pointer to the grotto actor
void Grotto_OverrideActorEntrance(Actor* thisx) {

    s8 grottoContent = thisx->params & 0x00FF;

    // Loop through the grotto load table until we find the matching index based
    // on content and scene
    for (s16 index = 0; index < NUM_GROTTOS; index++) {

        if (grottoContent == grottoLoadTable[index].content && gGlobalContext->sceneNum == grottoLoadTable[index].scene) {
            // Find the override for the matching index from the grotto Load List
            index = grottoLoadList[index];

            // Run the index through the special entrances override check
            entranceFromGrottoActor = 1;
            gGlobalContext->nextEntranceIndex = Grotto_CheckSpecialEntrance(index);
            return;
        }
    }
}
