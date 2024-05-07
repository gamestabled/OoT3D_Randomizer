#include <string.h>
#include "3ds/services/uds.h"
#include "3ds/result.h"
#include "multiplayer.h"
#include "multiplayer_ghosts.h"
#include "oot_malloc.h"
#include "common.h"
#include "item_effect.h"
#include "savefile.h"
#include "settings.h"
#include "giants_knife.h"
#include "triforce.h"

#include "web.h"
#include "skulltula.h"
#include "graveyard_objects.h"
#include "collapsing_platform.h"
#include "boulder_red.h"
#include "door.h"
#include "carpenter.h"
#include "business_scrubs.h"
#include "shops.h"
#include "pushblock.h"
#include "bean_plant.h"

// Self Vars
u32 mp_receivedPackets          = 0;
bool mp_duplicateSendProtection = false;
static s8 netStage              = 0;
bool mp_isSyncing               = false;
bool mp_foundSyncer             = false;
bool mp_completeSyncs[6];
bool mSaveContextInit = false;
// Shared Progress: The ID that this client fullsyncs with
static u16 fullSyncerID = 0;

// Network Vars
u32* mBuffer;
size_t mBufSize;
u8 data_channel = 1;
udsBindContext bindctx;

static void Multiplayer_Sync_Init();
static void Multiplayer_Sync_SharedProgress();
static void Multiplayer_SendPacket(u16 packageSize, u16 targetID);
static void Multiplayer_UnpackPacket(u16 senderID);

typedef struct {
    // SaveContext
    u16 healthCapacity;
    s16 health;
    s16 rupees;
    s8 magicLevel;
    s8 magic;
    u16 bgsHitsLeft;
    u8 magicAcquired;
    u8 doubleMagic;
    u8 doubleDefense;
    s8 bgsFlag;
    u8 childEquipsButtonB;
    u8 items[26];
    s8 ammo[15];
    u8 magic_beans_available;
    u16 equipment;
    u32 upgrades;
    u32 questItems;
    u8 dungeonItems[20];
    s8 dungeonKeys[19];
    s16 gsTokens;
    SaveSceneFlags sceneFlags[124];
    u8 gsFlags[22];
    u32 bigPoePoints;
    u8 fishingFlags;
    u16 eventChkInf[14];
    u16 itemGetInf[4];
    u16 infTable[30];
    u32 worldMapAreaData;
    u16 magicMeterSize;
    // ExtData
    u8 extInf[EXTINF_SIZE];
    u32 scenesDiscovered[SAVEFILE_SCENES_DISCOVERED_IDX_COUNT];
    u32 entrancesDiscovered[SAVEFILE_ENTRANCES_DISCOVERED_IDX_COUNT];
    u8 triforcePieces;
} MultiplayerSaveContext;

static MultiplayerSaveContext mSaveContext;

static void Multiplayer_Overwrite_mSaveContext(void) {
    // SaveContext
    mSaveContext.healthCapacity     = gSaveContext.healthCapacity;
    mSaveContext.health             = gSaveContext.health;
    mSaveContext.rupees             = gSaveContext.rupees;
    mSaveContext.magicLevel         = gSaveContext.magicLevel;
    mSaveContext.magic              = gSaveContext.magic;
    mSaveContext.bgsHitsLeft        = gSaveContext.bgsHitsLeft;
    mSaveContext.magicAcquired      = gSaveContext.magicAcquired;
    mSaveContext.doubleMagic        = gSaveContext.doubleMagic;
    mSaveContext.doubleDefense      = gSaveContext.doubleDefense;
    mSaveContext.bgsFlag            = gSaveContext.bgsFlag;
    mSaveContext.childEquipsButtonB = gSaveContext.childEquips.buttonItems[0];
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.items); i++) {
        mSaveContext.items[i] = gSaveContext.items[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.ammo); i++) {
        mSaveContext.ammo[i] = gSaveContext.ammo[i];
    }
    mSaveContext.magic_beans_available = gSaveContext.magic_beans_available;
    mSaveContext.equipment             = gSaveContext.equipment;
    mSaveContext.upgrades              = gSaveContext.upgrades;
    mSaveContext.questItems            = gSaveContext.questItems;
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.dungeonItems); i++) {
        mSaveContext.dungeonItems[i] = gSaveContext.dungeonItems[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.dungeonKeys); i++) {
        mSaveContext.dungeonKeys[i] = gSaveContext.dungeonKeys[i];
    }
    mSaveContext.gsTokens = gSaveContext.gsTokens;
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.sceneFlags); i++) {
        mSaveContext.sceneFlags[i] = gSaveContext.sceneFlags[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.gsFlags); i++) {
        mSaveContext.gsFlags[i] = gSaveContext.gsFlags[i];
    }
    mSaveContext.bigPoePoints = gSaveContext.bigPoePoints;
    mSaveContext.fishingFlags = gSaveContext.fishingStats.flags;
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.eventChkInf); i++) {
        mSaveContext.eventChkInf[i] = gSaveContext.eventChkInf[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.itemGetInf); i++) {
        mSaveContext.itemGetInf[i] = gSaveContext.itemGetInf[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.infTable); i++) {
        mSaveContext.infTable[i] = gSaveContext.infTable[i];
    }
    mSaveContext.worldMapAreaData = gSaveContext.worldMapAreaData;
    mSaveContext.magicMeterSize   = gSaveContext.magicMeterSize;
    // ExtData
    for (size_t i = 0; i < EXTINF_SIZE; i++) {
        mSaveContext.extInf[i] = gExtSaveData.extInf[i];
    }
    for (size_t i = 0; i < SAVEFILE_SCENES_DISCOVERED_IDX_COUNT; i++) {
        mSaveContext.scenesDiscovered[i] = gExtSaveData.scenesDiscovered[i];
    }
    for (size_t i = 0; i < SAVEFILE_ENTRANCES_DISCOVERED_IDX_COUNT; i++) {
        mSaveContext.entrancesDiscovered[i] = gExtSaveData.entrancesDiscovered[i];
    }
    mSaveContext.triforcePieces = gExtSaveData.triforcePieces;
}

static void Multiplayer_Overwrite_gSaveContext(void) {
    // SaveContext
    gSaveContext.healthCapacity             = mSaveContext.healthCapacity;
    gSaveContext.health                     = mSaveContext.health;
    gSaveContext.rupees                     = mSaveContext.rupees;
    gSaveContext.magicLevel                 = mSaveContext.magicLevel;
    gSaveContext.magic                      = mSaveContext.magic;
    gSaveContext.bgsHitsLeft                = mSaveContext.bgsHitsLeft;
    gSaveContext.magicAcquired              = mSaveContext.magicAcquired;
    gSaveContext.doubleMagic                = mSaveContext.doubleMagic;
    gSaveContext.doubleDefense              = mSaveContext.doubleDefense;
    gSaveContext.bgsFlag                    = mSaveContext.bgsFlag;
    gSaveContext.childEquips.buttonItems[0] = mSaveContext.childEquipsButtonB;
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.items); i++) {
        gSaveContext.items[i] = mSaveContext.items[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.ammo); i++) {
        gSaveContext.ammo[i] = mSaveContext.ammo[i];
    }
    gSaveContext.magic_beans_available = mSaveContext.magic_beans_available;
    gSaveContext.equipment             = mSaveContext.equipment;
    gSaveContext.upgrades              = mSaveContext.upgrades;
    gSaveContext.questItems            = mSaveContext.questItems;
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.dungeonItems); i++) {
        gSaveContext.dungeonItems[i] = mSaveContext.dungeonItems[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.dungeonKeys); i++) {
        gSaveContext.dungeonKeys[i] = mSaveContext.dungeonKeys[i];
    }
    gSaveContext.gsTokens = mSaveContext.gsTokens;
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.sceneFlags); i++) {
        gSaveContext.sceneFlags[i] = mSaveContext.sceneFlags[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.gsFlags); i++) {
        gSaveContext.gsFlags[i] = mSaveContext.gsFlags[i];
    }
    gSaveContext.bigPoePoints       = mSaveContext.bigPoePoints;
    gSaveContext.fishingStats.flags = mSaveContext.fishingFlags;
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.eventChkInf); i++) {
        gSaveContext.eventChkInf[i] = mSaveContext.eventChkInf[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.itemGetInf); i++) {
        gSaveContext.itemGetInf[i] = mSaveContext.itemGetInf[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.infTable); i++) {
        gSaveContext.infTable[i] = mSaveContext.infTable[i];
    }
    gSaveContext.worldMapAreaData = mSaveContext.worldMapAreaData;
    gSaveContext.magicMeterSize   = mSaveContext.magicMeterSize;
    // ExtData
    for (size_t i = 0; i < EXTINF_SIZE; i++) {
        gExtSaveData.extInf[i] = mSaveContext.extInf[i];
    }
    for (size_t i = 0; i < SAVEFILE_SCENES_DISCOVERED_IDX_COUNT; i++) {
        gExtSaveData.scenesDiscovered[i] = mSaveContext.scenesDiscovered[i];
    }
    for (size_t i = 0; i < SAVEFILE_ENTRANCES_DISCOVERED_IDX_COUNT; i++) {
        gExtSaveData.entrancesDiscovered[i] = mSaveContext.entrancesDiscovered[i];
    }
    gExtSaveData.triforcePieces = mSaveContext.triforcePieces;
}

void Multiplayer_OnFileLoad(void) {
    if (gSettingsContext.mp_Enabled == OFF || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }

    if (!mSaveContextInit) {
        mSaveContextInit = true;
        Multiplayer_Overwrite_mSaveContext();
    } else {
        Multiplayer_Overwrite_gSaveContext();
    }

    // Clear Empty Slots
    for (u8 i = 0; i < 0x18; ++i) {
        if (gSaveContext.itemMenuChild[i] != SLOT_NONE &&
            gSaveContext.items[gSaveContext.itemMenuChild[i]] == ITEM_NONE) {
            gSaveContext.itemMenuChild[i] = SLOT_NONE;
        }
        if (gSaveContext.itemMenuAdult[i] != SLOT_NONE &&
            gSaveContext.items[gSaveContext.itemMenuAdult[i]] == ITEM_NONE) {
            gSaveContext.itemMenuAdult[i] = SLOT_NONE;
        }
    }
    // Place Magic Arrows
    static const u8 SLOT_MAGIC_ARROW[] = { SLOT_ARROW_FIRE, SLOT_ARROW_ICE, SLOT_ARROW_LIGHT };
    for (size_t i = 0; i < ARRAY_SIZE(SLOT_MAGIC_ARROW); i++) {
        if (gSaveContext.items[SLOT_BOW] == ITEM_NONE && gSaveContext.items[SLOT_MAGIC_ARROW[i]] != ITEM_NONE &&
            !SaveFile_InventoryMenuHasSlot(0, SLOT_MAGIC_ARROW[i]) &&
            !SaveFile_InventoryMenuHasSlot(1, SLOT_MAGIC_ARROW[i])) {
            PushSlotIntoInventoryMenu(SLOT_MAGIC_ARROW[i]);
        } else if (gSaveContext.items[SLOT_BOW] != ITEM_NONE || gSaveContext.items[SLOT_MAGIC_ARROW[i]] == ITEM_NONE) {
            SaveFile_ResetItemSlotsIfMatchesID(SLOT_MAGIC_ARROW[i]);
        }
    }

    Multiplayer_Sync_Init();
}

// Previous Values
u16 prevHealthCapacity;
u8 prevItems[26];
s8 prevAmmo[15];
u8 prevMagicBeansBought;
u16 prevEquipment;
u32 prevUpgrades;
u32 prevQuestItems;
u8 prevDungeonItems[20];
s8 prevDungeonKeys[19];
s16 prevGSTokens;
u16 prevEventChkInf[14];
u16 prevItemGetInf[4];
u16 prevInfTable[30];
ActorFlags prevActorFlags;
SaveSceneFlags prevSaveSceneFlags[124];
u8 prevGSFlags[22];
u32 prevBigPoePoints;
u8 prevFishingFlags;
u32 prevWorldMapAreaData;
u32 prevAdultTrade;
u8 prevExtInf[EXTINF_SIZE];
u8 prevTriforcePieces;
s16 prevHealth;
s16 prevRupees;

typedef enum {
    // Ghost Data
    PACKET_GHOSTPING,
    PACKET_GHOSTDATA,
    PACKET_GHOSTDATA_JOINTTABLE,
    PACKET_LINKSFX,
    // Shared Progress
    PACKET_FULLSYNCREQUEST,
    PACKET_FULLSYNCPING,
    PACKET_BASESYNC,
    PACKET_FULLSCENEFLAGSYNC,
    PACKET_FULLENTRANCESYNC,
    PACKET_ITEM,
    PACKET_MAXHEALTH,
    PACKET_KOKIRISWORDEQUIP,
    PACKET_BGSFLAG,
    PACKET_MAGICARROW,
    PACKET_GREATFAIRYBUFF,
    PACKET_MAGICBEANDIFF,
    PACKET_MAGICBEANSBOUGHT,
    PACKET_EQUIPMENT,
    PACKET_UPGRADES,
    PACKET_QUESTITEM,
    PACKET_DUNGEONITEM,
    PACKET_DUNGEONKEY,
    PACKET_GSTOKENDIFF,
    PACKET_EVENTCHKINF,
    PACKET_ITEMGETINF,
    PACKET_INFTABLE,
    PACKET_ACTORFLAGS,
    PACKET_SAVESCENEFLAG,
    PACKET_GSFLAGS,
    PACKET_BIGPOEPOINTS,
    PACKET_FISHINGFLAG,
    PACKET_WORLDMAPBIT,
    PACKET_EXTINF,
    PACKET_DISCOVEREDSCENE,
    PACKET_DISCOVEREDENTRANCE,
    PACKET_TRIFORCEPIECES,
    PACKET_UNLOCKEDDOOR,
    PACKET_ACTORUPDATE,
    PACKET_ACTORSPAWN,
    // Etc
    PACKET_HEALTHCHANGE,
    PACKET_RUPEESCHANGE,
    PACKET_AMMOCHANGE,
} PacketIdentifier;

static u8 IsSendReceiveReady(void) {
    return gSettingsContext.mp_Enabled != OFF && netStage >= 3;
}

void Multiplayer_Run(void) {
    if (gSettingsContext.mp_Enabled == OFF) {
        return;
    }

    Result result;
    static u8 initTimer     = 0;
    const u32 wlancommID    = 0x3656B7DA; // Unique ID set manually
    static u8 netScanChecks = 0;

    switch (netStage) {
        case 0:
            initTimer++;
            // Initializing too fast fails
            if (initTimer >= 30) {
                result = udsInit(0x3000, NULL);
                if (R_FAILED(result)) {
                    netStage = -1;
                    return;
                }
                mBufSize = 0x4000;
                mBuffer  = SystemArena_Malloc(mBufSize);
                netStage++;
            }
            break;
        case 1:
            // Connect or host: Scan for a bit before creating a network
            if (netScanChecks < (playingOnCitra ? 30 : 3)) {
                netScanChecks++;

                size_t total_networks        = 0;
                udsNetworkScanInfo* networks = NULL;
                udsNetworkScanInfo* network  = NULL;

                memset(mBuffer, 0, sizeof(mBufSize));
                result = udsScanBeacons(mBuffer, mBufSize, &networks, &total_networks, wlancommID, 0, NULL, false);
                if (R_FAILED(result)) {
                    return;
                }

                if (total_networks) {
                    // Connect to first found
                    network = &networks[0];

                    // Try 10 times?
                    for (size_t i = 0; i < 10; i++) {
                        result = udsConnectNetwork(&network->network, "", 1, &bindctx, UDS_BROADCAST_NETWORKNODEID,
                                                   UDSCONTYPE_Client, data_channel, UDS_DEFAULT_RECVBUFSIZE);
                        if (R_SUCCEEDED(result)) {
                            break;
                        }
                    }
                    SystemArena_Free(networks);

                    if (R_FAILED(result)) {
                        return;
                    }
                    netStage++;
                }
            } else {
                u8 max_players = UDS_MAXNODES;
                // Citra crashes when allowing too many nodes
                if (playingOnCitra) {
                    max_players /= 2;
                }
                udsNetworkStruct networkstruct;
                udsGenerateDefaultNetworkStruct(&networkstruct, wlancommID, 0, max_players);
                result = udsCreateNetwork(&networkstruct, "", 1, &bindctx, data_channel, UDS_DEFAULT_RECVBUFSIZE);
                if (R_FAILED(result)) {
                    netStage = -1;
                    return;
                }

                netStage++;
            }
            break;
        case 2:
            // Free buffer
            SystemArena_Free(mBuffer);
            mBufSize = UDS_DATAFRAME_MAXSIZE;
            mBuffer  = SystemArena_Malloc(mBufSize);

            if (gSettingsContext.mp_SharedProgress == ON) {
                mp_isSyncing = true;
            }

            netStage++;

            break;
        case 3:
            // Ready to go! This update is only called in-game with the gfx menu closed
            if (IsInGameOrBossChallenge()) {
                Multiplayer_Update(1);
                Multiplayer_Ghosts_SpawnPuppets();
            }
            break;
    }
}

void Multiplayer_Update(u8 fromGlobalContextUpdate) {
    if (!IsSendReceiveReady()) {
        return;
    }
    Multiplayer_ReceivePackets();
    Multiplayer_Ghosts_Tick();
    if (fromGlobalContextUpdate) {
        Multiplayer_Send_GhostData();
        if (playingOnCitra) {
            Multiplayer_Send_GhostData_JointTable();
        }
    } else {
        Multiplayer_Send_GhostPing();
    }
}

s8 Multiplayer_PlayerCount() {
    udsConnectionStatus status;
    if (R_SUCCEEDED(udsGetConnectionStatus(&status))) {
        return status.total_nodes;
    }
    return -1;
}

static void Multiplayer_Sync_Init(void) {
    // Max Health
    prevHealthCapacity = gSaveContext.healthCapacity;

    // Items
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.items); i++) {
        prevItems[i] = gSaveContext.items[i];
    }

    // Ammo
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.ammo); i++) {
        prevAmmo[i] = gSaveContext.ammo[i];
    }

    // Magic Beans Bought
    prevMagicBeansBought = gSaveContext.magic_beans_available;

    // Equipment
    prevEquipment = gSaveContext.equipment;

    // Upgrades
    prevUpgrades = gSaveContext.upgrades;

    // Quest Items
    prevQuestItems = gSaveContext.questItems;

    // Dungeon Items
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.dungeonItems); i++) {
        prevDungeonItems[i] = gSaveContext.dungeonItems[i];
    }

    // Dungeon Keys
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.dungeonKeys); i++) {
        prevDungeonKeys[i] = gSaveContext.dungeonKeys[i];
    }

    // GS Tokens
    prevGSTokens = gSaveContext.gsTokens;

    // Inf
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.eventChkInf); i++) {
        prevEventChkInf[i] = gSaveContext.eventChkInf[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.itemGetInf); i++) {
        prevItemGetInf[i] = gSaveContext.itemGetInf[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.infTable); i++) {
        prevInfTable[i] = gSaveContext.infTable[i];
    }

    // Actor Flags
    prevActorFlags = gGlobalContext->actorCtx.flags;

    // Save Scene Flags
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.sceneFlags); i++) {
        prevSaveSceneFlags[i] = gSaveContext.sceneFlags[i];
    }

    // GS Flags
    for (size_t i = 0; i < ARRAY_SIZE(gSaveContext.gsFlags); i++) {
        prevGSFlags[i] = gSaveContext.gsFlags[i];
    }

    // Big Poe Points
    prevBigPoePoints = gSaveContext.bigPoePoints;

    // Fishing Flags
    prevFishingFlags = gSaveContext.fishingStats.flags;

    // World Map
    prevWorldMapAreaData = gSaveContext.worldMapAreaData;

    // Adult Trade
    prevAdultTrade = gSaveContext.sceneFlags[0x60].unk;

    // Extra Info Table
    for (size_t i = 0; i < EXTINF_SIZE; i++) {
        prevExtInf[i] = gExtSaveData.extInf[i];
    }

    // Triforce Pieces
    prevTriforcePieces = gExtSaveData.triforcePieces;

    // Health
    prevHealth = gSaveContext.health;

    // Rupees
    prevRupees = gSaveContext.rupees;
}

void Multiplayer_Sync_Update(void) {
    if (!IsSendReceiveReady() || !IsInGame()) {
        return;
    }

    // Shared Progress
    if (gSettingsContext.mp_SharedProgress == ON) {
        Multiplayer_Sync_SharedProgress();
    }

    // Health
    if (gSettingsContext.mp_SharedHealth == ON) {
        if (prevHealth != gSaveContext.health) {
            Multiplayer_Send_HealthChange(gSaveContext.health - prevHealth);
        }
        prevHealth = gSaveContext.health;
    }

    // Rupees
    if (gSettingsContext.mp_SharedRupees == ON) {
        if (prevRupees != gSaveContext.rupees) {
            Multiplayer_Send_RupeeChange(gSaveContext.rupees - prevRupees);
        }
        prevRupees = gSaveContext.rupees;
    }

    // Ammo
    if (gSettingsContext.mp_SharedAmmo == ON) {
        for (size_t slot = 0; slot < ARRAY_SIZE(gSaveContext.ammo); slot++) {
            if (slot == SLOT_BEAN) {
                continue;
            }
            if (prevAmmo[slot] != gSaveContext.ammo[slot]) {
                Multiplayer_Send_AmmoChange(slot, gSaveContext.ammo[slot] - prevAmmo[slot]);
            }
            prevAmmo[slot] = gSaveContext.ammo[slot];
        }
    }
}

static void Multiplayer_Sync_SharedProgress(void) {
    // If a player gets the 4th heart piece but stays in the item get message while another
    // player gets another heart piece, the 4th heart piece bit never unsets and causes various issues.
    // To avoid this, unset it instantly and give the health increase directly.
    if (gSaveContext.questItems & (1 << 30)) {
        gSaveContext.questItems &= ~(1 << 30);
        gSaveContext.healthCapacity += 0x10;
    }

    // Max Health
    if (prevHealthCapacity != gSaveContext.healthCapacity) {
        Multiplayer_Send_MaxHealth();
    }
    prevHealthCapacity = gSaveContext.healthCapacity;

    // Items
    for (size_t slot = 0; slot < ARRAY_SIZE(gSaveContext.items); slot++) {
        if (prevItems[slot] != gSaveContext.items[slot] && slot != SLOT_TRADE_ADULT) {
            Multiplayer_Send_Item(slot, gSaveContext.items[slot]);
        }
        prevItems[slot] = gSaveContext.items[slot];
    }

    // Magic Beans Ammo
    if (prevAmmo[SLOT_BEAN] != gSaveContext.ammo[SLOT_BEAN]) {
        Multiplayer_Send_MagicBeanDiff(gSaveContext.ammo[SLOT_BEAN] - prevAmmo[SLOT_BEAN]);
    }
    prevAmmo[SLOT_BEAN] = gSaveContext.ammo[SLOT_BEAN];

    // Magic Beans Bought
    if (prevMagicBeansBought != gSaveContext.magic_beans_available) {
        Multiplayer_Send_MagicBeansBoughtUpdate();
    }
    prevMagicBeansBought = gSaveContext.magic_beans_available;

    // Equipment
    if (prevEquipment != gSaveContext.equipment) {
        for (size_t bit = 0; bit < BIT_COUNT(gSaveContext.equipment); bit++) {
            // Don't sync Master Sword in final Ganon fight, nor giant's knife's state
            if ((bit == 1 && gGlobalContext->sceneNum == 0x4F) || bit == 3) {
                continue;
            }
            s8 result = BitCompare(gSaveContext.equipment, prevEquipment, bit);
            if (result > 0) {
                Multiplayer_Send_EquipmentBit(bit, 1);
            } else if (result < 0) {
                Multiplayer_Send_EquipmentBit(bit, 0);
            }
        }
    }
    prevEquipment = gSaveContext.equipment;

    // Upgrades
    if (prevUpgrades != gSaveContext.upgrades) {
        for (size_t bit = 0; bit < BIT_COUNT(gSaveContext.upgrades); bit++) {
            s8 result = BitCompare(gSaveContext.upgrades, prevUpgrades, bit);
            if (result > 0) {
                Multiplayer_Send_UpgradesBit(bit, 1);
            } else if (result < 0) {
                Multiplayer_Send_UpgradesBit(bit, 0);
            }
        }
    }
    prevUpgrades = gSaveContext.upgrades;

    // Quest Items
    if (prevQuestItems != gSaveContext.questItems) {
        for (size_t bit = 0; bit < BIT_COUNT(gSaveContext.questItems); bit++) {
            s8 result = BitCompare(gSaveContext.questItems, prevQuestItems, bit);
            if (result > 0) {
                Multiplayer_Send_QuestItemBit(bit, 1);
            } else if (result < 0) {
                Multiplayer_Send_QuestItemBit(bit, 0);
            }
        }
    }
    prevQuestItems = gSaveContext.questItems;

    // Dungeon Items
    for (size_t index = 0; index < ARRAY_SIZE(gSaveContext.dungeonItems); index++) {
        if (prevDungeonItems[index] != gSaveContext.dungeonItems[index]) {
            for (size_t bit = 0; bit < BIT_COUNT(gSaveContext.dungeonItems[index]); bit++) {
                s8 result = BitCompare(gSaveContext.dungeonItems[index], prevDungeonItems[index], bit);
                if (result > 0) {
                    Multiplayer_Send_DungeonItemBit(index, bit, 1);
                } else if (result < 0) {
                    Multiplayer_Send_DungeonItemBit(index, bit, 0);
                }
            }
        }
        prevDungeonItems[index] = gSaveContext.dungeonItems[index];
    }

    // Dungeon Keys
    for (size_t index = 0; index < ARRAY_SIZE(gSaveContext.dungeonKeys); index++) {
        // Don't sync chest minigame keys when the setting is off
        if (index == DUNGEON_TREASURE_CHEST_SHOP && gSettingsContext.shuffleChestMinigame == SHUFFLECHESTMINIGAME_OFF) {
            continue;
        }
        // Only look for increased key count and handle used keys in Multiplayer_Send_UnlockedDoor()
        if (prevDungeonKeys[index] < gSaveContext.dungeonKeys[index]) {
            Multiplayer_Send_DungeonKeyUpdate(index, gSaveContext.dungeonKeys[index] - prevDungeonKeys[index]);
        }
        prevDungeonKeys[index] = gSaveContext.dungeonKeys[index];
    }

    // GS Tokens
    if (prevGSTokens != gSaveContext.gsTokens) {
        Multiplayer_Send_GSTokenDiff(gSaveContext.gsTokens - prevGSTokens);
    }
    prevGSTokens = gSaveContext.gsTokens;

    // EventChkInf
    for (size_t index = 0; index < ARRAY_SIZE(gSaveContext.eventChkInf); index++) {
        if (prevEventChkInf[index] != gSaveContext.eventChkInf[index]) {
            for (size_t bit = 0; bit < BIT_COUNT(gSaveContext.eventChkInf[index]); bit++) {
                s8 result = BitCompare(gSaveContext.eventChkInf[index], prevEventChkInf[index], bit);
                if (result > 0) {
                    Multiplayer_Send_EventChkInfBit(index, bit, 1);
                } else if (result < 0) {
                    Multiplayer_Send_EventChkInfBit(index, bit, 0);
                }
            }
        }
        prevEventChkInf[index] = gSaveContext.eventChkInf[index];
    }

    // ItemGetInf
    for (size_t index = 0; index < ARRAY_SIZE(gSaveContext.itemGetInf); index++) {
        if (prevItemGetInf[index] != gSaveContext.itemGetInf[index]) {
            for (size_t bit = 0; bit < BIT_COUNT(gSaveContext.itemGetInf[index]); bit++) {
                s8 result = BitCompare(gSaveContext.itemGetInf[index], prevItemGetInf[index], bit);
                if (result > 0) {
                    Multiplayer_Send_ItemGetInfBit(index, bit, 1);
                } else if (result < 0) {
                    Multiplayer_Send_ItemGetInfBit(index, bit, 0);
                }
            }
        }
        prevItemGetInf[index] = gSaveContext.itemGetInf[index];
    }

    // InfTable
    for (size_t index = 0; index < ARRAY_SIZE(gSaveContext.infTable); index++) {
        if (prevInfTable[index] != gSaveContext.infTable[index]) {
            for (size_t bit = 0; bit < BIT_COUNT(gSaveContext.infTable[index]); bit++) {
                // Skip swordless flag
                if (index == 29 && bit == 0) {
                    continue;
                }
                s8 result = BitCompare(gSaveContext.infTable[index], prevInfTable[index], bit);
                if (result > 0) {
                    Multiplayer_Send_InfTableBit(index, bit, 1);
                } else if (result < 0) {
                    Multiplayer_Send_InfTableBit(index, bit, 0);
                }
            }
        }
        prevInfTable[index] = gSaveContext.infTable[index];
    }

    // Actor Flags
    u32* actorFlagPtr[] = {
        &gGlobalContext->actorCtx.flags.swch,
        &gGlobalContext->actorCtx.flags.chest,
        &gGlobalContext->actorCtx.flags.clear,
        &gGlobalContext->actorCtx.flags.collect,
    };
    u32* prevActorFlagPtr[] = {
        &prevActorFlags.swch,
        &prevActorFlags.chest,
        &prevActorFlags.clear,
        &prevActorFlags.collect,
    };
    for (size_t member = 0; member < ARRAY_SIZE(actorFlagPtr); member++) {
        // Don't sync chest minigame chests (except the final one) when the setting is off
        if (member == 1 && gGlobalContext->sceneNum == 16 && gGlobalContext->roomNum != 6 &&
            gSettingsContext.shuffleChestMinigame == SHUFFLECHESTMINIGAME_OFF) {
            continue;
        }
        if (*prevActorFlagPtr[member] != *actorFlagPtr[member]) {
            for (size_t bit = 0; bit < BIT_COUNT(*actorFlagPtr[member]); bit++) {
                s8 result = BitCompare(*actorFlagPtr[member], *prevActorFlagPtr[member], bit);
                if (result > 0) {
                    Multiplayer_Send_ActorFlagBit(member, bit, 1);
                } else if (result < 0) {
                    Multiplayer_Send_ActorFlagBit(member, bit, 0);
                }
            }
        }
        *prevActorFlagPtr[member] = *actorFlagPtr[member];
    }

    // Save Scene Flags
    for (size_t scene = 0; scene < ARRAY_SIZE(gSaveContext.sceneFlags); scene++) {
        u32* sceneFlagPtr[] = {
            &gSaveContext.sceneFlags[scene].unk,
            &gSaveContext.sceneFlags[scene].rooms1,
            &gSaveContext.sceneFlags[scene].rooms2,
        };
        u32* prevSceneFlagPtr[] = {
            &prevSaveSceneFlags[scene].unk,
            &prevSaveSceneFlags[scene].rooms1,
            &prevSaveSceneFlags[scene].rooms2,
        };
        for (size_t member = 0; member < ARRAY_SIZE(sceneFlagPtr); member++) {
            if (*prevSceneFlagPtr[member] != *sceneFlagPtr[member]) {
                for (size_t bit = 0; bit < BIT_COUNT(*sceneFlagPtr[member]); bit++) {
                    s8 result = BitCompare(*sceneFlagPtr[member], *prevSceneFlagPtr[member], bit);
                    if (result > 0) {
                        Multiplayer_Send_SceneFlagBit(scene, member, bit, 1);
                    } else if (result < 0) {
                        Multiplayer_Send_SceneFlagBit(scene, member, bit, 0);
                    }
                }
            }
            *prevSceneFlagPtr[member] = *sceneFlagPtr[member];
        }
    }

    // GS Flags
    for (size_t index = 0; index < ARRAY_SIZE(gSaveContext.gsFlags); index++) {
        if (prevGSFlags[index] != gSaveContext.gsFlags[index]) {
            for (size_t bit = 0; bit < BIT_COUNT(gSaveContext.gsFlags[index]); bit++) {
                s8 result = BitCompare(gSaveContext.gsFlags[index], prevGSFlags[index], bit);
                if (result > 0) {
                    Multiplayer_Send_GSFlagBit(index, bit, 1);
                } else if (result < 0) {
                    Multiplayer_Send_GSFlagBit(index, bit, 0);
                }
            }
        }
        prevGSFlags[index] = gSaveContext.gsFlags[index];
    }

    // Big Poe Points
    if (prevBigPoePoints != gSaveContext.bigPoePoints) {
        Multiplayer_Send_BigPoePoints(gSaveContext.bigPoePoints - prevBigPoePoints);
    }
    prevBigPoePoints = gSaveContext.bigPoePoints;

    // Fishing Flags
    if (prevFishingFlags != gSaveContext.fishingStats.flags) {
        for (size_t bit = 0; bit < BIT_COUNT(gSaveContext.fishingStats.flags); bit++) {
            s8 result = BitCompare(gSaveContext.fishingStats.flags, prevFishingFlags, bit);
            if (result > 0) {
                Multiplayer_Send_FishingFlag(bit, 1);
            } else if (result < 0) {
                Multiplayer_Send_FishingFlag(bit, 0);
            }
        }
    }
    prevFishingFlags = gSaveContext.fishingStats.flags;

    // World Map
    if (prevWorldMapAreaData != gSaveContext.worldMapAreaData) {
        for (size_t bit = 0; bit < BIT_COUNT(gSaveContext.worldMapAreaData); bit++) {
            s8 result = BitCompare(gSaveContext.worldMapAreaData, prevWorldMapAreaData, bit);
            if (result > 0) {
                Multiplayer_Send_WorldMapBit(bit, 1);
            } else if (result < 0) {
                Multiplayer_Send_WorldMapBit(bit, 0);
            }
        }
    }
    prevWorldMapAreaData = gSaveContext.worldMapAreaData;

    // Adult Trade
    if (prevAdultTrade != gSaveContext.sceneFlags[0x60].unk) {
        if (!SaveFile_TradeItemIsOwned(gSaveContext.items[SLOT_TRADE_ADULT])) {
            SaveFile_SetOwnedTradeItemEquipped();
        }
    }
    prevAdultTrade = gSaveContext.sceneFlags[0x60].unk;

    // Extra Info Table
    for (size_t index = 0; index < ARRAY_SIZE(gExtSaveData.extInf); index++) {
        // Don't send this to allow all current players to watch the cutscene
        if (index == EXTINF_HASTIMETRAVELED) {
            continue;
        }
        if (prevExtInf[index] != gExtSaveData.extInf[index]) {
            for (size_t bit = 0; bit < BIT_COUNT(gExtSaveData.extInf[index]); bit++) {
                s8 result = BitCompare(gExtSaveData.extInf[index], prevExtInf[index], bit);
                if (result > 0) {
                    Multiplayer_Send_ExtInfBit(index, bit, 1);
                } else if (result < 0) {
                    Multiplayer_Send_ExtInfBit(index, bit, 0);
                }
            }
        }
        prevExtInf[index] = gExtSaveData.extInf[index];
    }

    // Triforce Pieces
    if (prevTriforcePieces != gExtSaveData.triforcePieces) {
        Multiplayer_Send_TriforcePieces(gExtSaveData.triforcePieces - prevTriforcePieces);
    }
    prevTriforcePieces = gExtSaveData.triforcePieces;
}

void Multiplayer_Sync_UpdatePrevActorFlags(void) {
    // Prevents redundant packets from being sent when switching scenes
    if (gGlobalContext != NULL) {
        prevActorFlags = gGlobalContext->actorCtx.flags;
    }
}

// Ghost Data

void Multiplayer_Send_GhostPing(void) {
    if (!IsSendReceiveReady()) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer         = 0;
    mBuffer[memSpacer++] = PACKET_GHOSTPING; // 0: Identifier
    mBuffer[memSpacer++] = IsInGameOrBossChallenge();
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_GhostPing(u16 senderID) {
    u8 isInGame = mBuffer[1];
    Multiplayer_Ghosts_UpdateGhostData(senderID, NULL, isInGame);
}

void Multiplayer_Send_GhostData(void) {
    if (!IsSendReceiveReady()) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u16 memSpacer        = 0;
    mBuffer[memSpacer++] = PACKET_GHOSTDATA; // 0: Identifier

    GhostData ghostData;
    ghostData.currentScene = gGlobalContext->sceneNum;
    ghostData.age          = gSaveContext.linkAge;
    ghostData.position     = PLAYER->actor.world.pos;
    ghostData.rotation     = PLAYER->actor.shape.rot;

    ghostData.meshGroups1 = 0;
    ghostData.meshGroups2 = 0;
    s32 meshGroupCount    = Model_GetMeshGroupCount(PLAYER->skelAnime.unk_28);

    for (size_t index = 0; index < BIT_COUNT(u32); index++) {
        if (index > meshGroupCount) {
            break;
        }
        if (Model_IsMeshGroupUsed(PLAYER->skelAnime.unk_28, index)) {
            ghostData.meshGroups1 |= 1 << index;
        }
    }
    for (size_t index = BIT_COUNT(u32); index < meshGroupCount; index++) {
        if (Model_IsMeshGroupUsed(PLAYER->skelAnime.unk_28, index)) {
            ghostData.meshGroups2 |= 1 << (index - BIT_COUNT(u32));
        }
    }

    // Always have body enabled
    if (gSaveContext.gameMode == 0) {
        if (gSaveContext.linkAge == 0) {
            ghostData.meshGroups2 |= 0x6000;
        } else {
            ghostData.meshGroups1 |= 0x7000000;
        }
    }

    ghostData.currentTunic = PLAYER->currentTunic;

    u32 totalSize = sizeof(GhostData) - sizeof(ghostData.jointTable);
    memcpy(&mBuffer[memSpacer], &ghostData, totalSize);
    memSpacer += totalSize / 4;

    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_GhostData(u16 senderID) {
    GhostData ghostData;
    u32 packetSize = sizeof(GhostData) - sizeof(ghostData.jointTable);
    memcpy(&ghostData, &mBuffer[1], packetSize);

    Multiplayer_Ghosts_UpdateGhostData(senderID, &ghostData, TRUE);
}

void Multiplayer_Send_GhostData_JointTable(void) {
    if (!IsSendReceiveReady()) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u16 memSpacer        = 0;
    mBuffer[memSpacer++] = PACKET_GHOSTDATA_JOINTTABLE; // 0: Identifier

    memcpy(&mBuffer[memSpacer], &PLAYER->jointTable, sizeof(PLAYER->jointTable));
    memSpacer += sizeof(PLAYER->jointTable) / 4;

    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_GhostData_JointTable(u16 senderID) {
    Multiplayer_Ghosts_UpdateGhostData_JointTable(senderID, (LimbData*)&mBuffer[1]);
}

void Multiplayer_Send_LinkSFX(u32 sfxID_) {
    if (!IsSendReceiveReady()) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer         = 0;
    mBuffer[memSpacer++] = PACKET_LINKSFX; // 0: Identifier
    mBuffer[memSpacer++] = sfxID_;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_LinkSFX(u16 senderID) {
    GhostData* ghostDataPtr = Multiplayer_Ghosts_GetGhostData(senderID);
    if (ghostDataPtr == NULL || ghostDataPtr->currentScene != gGlobalContext->sceneNum) {
        return;
    }

    mp_duplicateSendProtection = true;
    PlaySFX(mBuffer[1], &ghostDataPtr->position, 4, (f32*)GAME_ADDR(0x54AC20), (f32*)GAME_ADDR(0x54AC20),
            (s8*)GAME_ADDR(0x54AC24));
}

// Shared Progress

// Places the identifier, sync id, and hash in the buffer in order, and returns the memSpacer offset.
static u8 PrepareSharedProgressPacket(u8 packetIdentifier) {
    u8 memSpacer = 0;

    mBuffer[memSpacer++] = packetIdentifier;
    mBuffer[memSpacer++] = gSettingsContext.mp_SyncId;
    for (size_t i = 0; i < ARRAY_SIZE(gSettingsContext.hashIndexes); i++) {
        mBuffer[memSpacer++] = gSettingsContext.hashIndexes[i];
    }

    return memSpacer;
}

// Follows the standard of putting the indentifier, sync id, and hash in the same order.
static u8 GetSharedProgressMemSpacerOffset(void) {
    u8 memSpacerOffset = 0;

    memSpacerOffset++; // Identifier
    memSpacerOffset++; // Sync Id
    memSpacerOffset += ARRAY_SIZE(gSettingsContext.hashIndexes);

    return memSpacerOffset;
}

// This function should only be called inside shared-progress-receive functions, right after mBuffer has been filled.
static bool IsInSameSyncGroup(void) {
    u8 receivedSyncId    = mBuffer[1];
    u32* receivedHashPtr = &mBuffer[2];

    if (receivedSyncId != gSettingsContext.mp_SyncId) {
        return false;
    }
    for (size_t i = 0; i < ARRAY_SIZE(gSettingsContext.hashIndexes); i++) {
        if (receivedHashPtr[i] != gSettingsContext.hashIndexes[i]) {
            return false;
        }
    }
    return true;
}

u8 Multiplayer_GetNeededPacketsMask(void) {
    u8 neededPacketsMask = 0;

    for (size_t i = 0; i < ARRAY_SIZE(mp_completeSyncs); i++) {
        if (!mp_completeSyncs[i]) {
            neededPacketsMask |= 1 << i;
        }
    }

    return neededPacketsMask;
}

void Multiplayer_Send_FullSyncRequest(u8 neededPacketsMask) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_FULLSYNCREQUEST);

    mBuffer[memSpacer++] = neededPacketsMask;
    Multiplayer_SendPacket(memSpacer, neededPacketsMask == 0 ? UDS_BROADCAST_NETWORKNODEID : fullSyncerID);
}

void Multiplayer_Receive_FullSyncRequest(u16 senderID) {
    if (gSettingsContext.mp_SharedProgress == OFF || !IsInSameSyncGroup() || !mSaveContextInit) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 neededPacketsMask = mBuffer[memSpacer++];

    if (neededPacketsMask == 0) {
        Multiplayer_Send_FullSyncPing(senderID);
        return;
    }

    u8 maskSpacer = 0;
    if (neededPacketsMask & 1 << maskSpacer++) {
        Multiplayer_Send_BaseSync(senderID);
    }
    if (neededPacketsMask & 1 << maskSpacer++) {
        Multiplayer_Send_FullSceneFlagSync(senderID, 0);
    }
    if (neededPacketsMask & 1 << maskSpacer++) {
        Multiplayer_Send_FullSceneFlagSync(senderID, 1);
    }
    if (neededPacketsMask & 1 << maskSpacer++) {
        Multiplayer_Send_FullSceneFlagSync(senderID, 2);
    }
    if (neededPacketsMask & 1 << maskSpacer++) {
        Multiplayer_Send_FullSceneFlagSync(senderID, 3);
    }
    if (neededPacketsMask & 1 << maskSpacer++) {
        Multiplayer_Send_FullEntranceSync(senderID);
    }
}

void Multiplayer_Send_FullSyncPing(u16 targetID) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_FULLSYNCPING);

    Multiplayer_SendPacket(memSpacer, targetID);
}

void Multiplayer_Receive_FullSyncPing(u16 senderID) {
    if (gSettingsContext.mp_SharedProgress == OFF || !IsInSameSyncGroup() || fullSyncerID != 0) {
        return;
    }

    fullSyncerID   = senderID;
    mp_foundSyncer = true;
}

void Multiplayer_Send_BaseSync(u16 targetID) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_BASESYNC);

    mBuffer[memSpacer++] = mSaveContext.healthCapacity;
    mBuffer[memSpacer++] = mSaveContext.doubleDefense;
    mBuffer[memSpacer++] = mSaveContext.magicLevel;
    mBuffer[memSpacer++] = mSaveContext.bgsHitsLeft;
    mBuffer[memSpacer++] = mSaveContext.magicAcquired;
    mBuffer[memSpacer++] = mSaveContext.doubleMagic;
    mBuffer[memSpacer++] = mSaveContext.magicMeterSize;
    mBuffer[memSpacer++] = mSaveContext.doubleDefense;
    mBuffer[memSpacer++] = mSaveContext.bgsFlag;
    mBuffer[memSpacer++] = mSaveContext.childEquipsButtonB;
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.items); i++) {
        mBuffer[memSpacer++] = mSaveContext.items[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.ammo); i++) {
        mBuffer[memSpacer++] = mSaveContext.ammo[i];
    }
    mBuffer[memSpacer++] = mSaveContext.magic_beans_available;
    mBuffer[memSpacer++] = mSaveContext.equipment;
    mBuffer[memSpacer++] = mSaveContext.upgrades;
    mBuffer[memSpacer++] = mSaveContext.questItems;
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.dungeonItems); i++) {
        mBuffer[memSpacer++] = mSaveContext.dungeonItems[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.dungeonKeys); i++) {
        mBuffer[memSpacer++] = mSaveContext.dungeonKeys[i];
    }
    mBuffer[memSpacer++] = mSaveContext.gsTokens;
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.gsFlags); i++) {
        mBuffer[memSpacer++] = mSaveContext.gsFlags[i];
    }
    mBuffer[memSpacer++] = mSaveContext.bigPoePoints;
    mBuffer[memSpacer++] = mSaveContext.fishingFlags;
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.eventChkInf); i++) {
        mBuffer[memSpacer++] = mSaveContext.eventChkInf[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.itemGetInf); i++) {
        mBuffer[memSpacer++] = mSaveContext.itemGetInf[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.infTable); i++) {
        mBuffer[memSpacer++] = mSaveContext.infTable[i];
    }
    mBuffer[memSpacer++] = mSaveContext.worldMapAreaData;
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.extInf); i++) {
        mBuffer[memSpacer++] = mSaveContext.extInf[i];
    }
    mBuffer[memSpacer++] = mSaveContext.triforcePieces;
    mBuffer[memSpacer++] = mSaveContext.health;
    mBuffer[memSpacer++] = mSaveContext.rupees;
    Multiplayer_SendPacket(memSpacer, targetID);
}

void Multiplayer_Receive_BaseSync(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF || mp_completeSyncs[0]) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    mSaveContext.healthCapacity     = mBuffer[memSpacer++];
    mSaveContext.doubleDefense      = mBuffer[memSpacer++];
    mSaveContext.magicLevel         = mBuffer[memSpacer++];
    mSaveContext.magic              = 0x30 * mSaveContext.magicLevel;
    mSaveContext.bgsHitsLeft        = mBuffer[memSpacer++];
    mSaveContext.magicAcquired      = mBuffer[memSpacer++];
    mSaveContext.doubleMagic        = mBuffer[memSpacer++];
    mSaveContext.magicMeterSize     = mBuffer[memSpacer++];
    mSaveContext.doubleDefense      = mBuffer[memSpacer++];
    mSaveContext.bgsFlag            = mBuffer[memSpacer++];
    mSaveContext.childEquipsButtonB = mBuffer[memSpacer++];
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.items); i++) {
        mSaveContext.items[i] = mBuffer[memSpacer++];
    }
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.ammo); i++) {
        mSaveContext.ammo[i] = mBuffer[memSpacer++];
    }
    mSaveContext.magic_beans_available = mBuffer[memSpacer++];
    mSaveContext.equipment             = mBuffer[memSpacer++];
    mSaveContext.upgrades              = mBuffer[memSpacer++];
    mSaveContext.questItems            = mBuffer[memSpacer++];
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.dungeonItems); i++) {
        mSaveContext.dungeonItems[i] = mBuffer[memSpacer++];
    }
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.dungeonKeys); i++) {
        mSaveContext.dungeonKeys[i] = mBuffer[memSpacer++];
    }
    mSaveContext.gsTokens = mBuffer[memSpacer++];
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.gsFlags); i++) {
        mSaveContext.gsFlags[i] = mBuffer[memSpacer++];
    }
    mSaveContext.bigPoePoints = mBuffer[memSpacer++];
    mSaveContext.fishingFlags = mBuffer[memSpacer++];
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.eventChkInf); i++) {
        mSaveContext.eventChkInf[i] = mBuffer[memSpacer++];
    }
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.itemGetInf); i++) {
        mSaveContext.itemGetInf[i] = mBuffer[memSpacer++];
    }
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.infTable); i++) {
        mSaveContext.infTable[i] = mBuffer[memSpacer++];
    }
    mSaveContext.worldMapAreaData = mBuffer[memSpacer++];
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.extInf); i++) {
        mSaveContext.extInf[i] = mBuffer[memSpacer++];
    }
    mSaveContext.triforcePieces = mBuffer[memSpacer++];
    if (gSettingsContext.mp_SharedHealth) {
        mSaveContext.health = mBuffer[memSpacer++];
    } else {
        mSaveContext.health = mSaveContext.healthCapacity;
        memSpacer++;
    }
    if (gSettingsContext.mp_SharedRupees) {
        mSaveContext.rupees = mBuffer[memSpacer++];
    } else if (gSettingsContext.startingMaxRupees) {
        static u16 maxRupees[] = { 99, 200, 500, 999 };
        mSaveContext.rupees    = maxRupees[mSaveContext.upgrades >> 12 & 0x3];
        memSpacer++;
    }

    mp_completeSyncs[0] = true;
}

void Multiplayer_Send_FullSceneFlagSync(u16 targetID, u8 part) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_FULLSCENEFLAGSYNC);

    mBuffer[memSpacer++] = part;
    u8 start             = 31 * part;
    u8 end               = start + 31;
    for (size_t i = start; i < end; i++) {
        mBuffer[memSpacer++] = mSaveContext.sceneFlags[i].chest;
        mBuffer[memSpacer++] = mSaveContext.sceneFlags[i].swch;
        mBuffer[memSpacer++] = mSaveContext.sceneFlags[i].clear;
        mBuffer[memSpacer++] = mSaveContext.sceneFlags[i].collect;
        mBuffer[memSpacer++] = mSaveContext.sceneFlags[i].unk;
        mBuffer[memSpacer++] = mSaveContext.sceneFlags[i].rooms1;
        mBuffer[memSpacer++] = mSaveContext.sceneFlags[i].rooms2;
    }
    Multiplayer_SendPacket(memSpacer, targetID);
}

void Multiplayer_Receive_FullSceneFlagSync(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 part = mBuffer[memSpacer++];

    if (mp_completeSyncs[1 + part]) {
        return;
    }

    u8 start = 31 * part;
    u8 end   = start + 31;
    for (size_t i = start; i < end; i++) {
        mSaveContext.sceneFlags[i].chest   = mBuffer[memSpacer++];
        mSaveContext.sceneFlags[i].swch    = mBuffer[memSpacer++];
        mSaveContext.sceneFlags[i].clear   = mBuffer[memSpacer++];
        mSaveContext.sceneFlags[i].collect = mBuffer[memSpacer++];
        mSaveContext.sceneFlags[i].unk     = mBuffer[memSpacer++];
        mSaveContext.sceneFlags[i].rooms1  = mBuffer[memSpacer++];
        mSaveContext.sceneFlags[i].rooms2  = mBuffer[memSpacer++];
    }

    mp_completeSyncs[1 + part] = true;
}

void Multiplayer_Send_FullEntranceSync(u16 targetID) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_FULLENTRANCESYNC);

    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.scenesDiscovered); i++) {
        mBuffer[memSpacer++] = mSaveContext.scenesDiscovered[i];
    }
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.entrancesDiscovered); i++) {
        mBuffer[memSpacer++] = mSaveContext.entrancesDiscovered[i];
    }
    Multiplayer_SendPacket(memSpacer, targetID);
}

void Multiplayer_Receive_FullEntranceSync(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF || mp_completeSyncs[5]) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.scenesDiscovered); i++) {
        mSaveContext.scenesDiscovered[i] = mBuffer[memSpacer++];
    }
    for (size_t i = 0; i < ARRAY_SIZE(mSaveContext.entrancesDiscovered); i++) {
        mSaveContext.entrancesDiscovered[i] = mBuffer[memSpacer++];
    }

    mp_completeSyncs[5] = true;
}

void Multiplayer_Send_Item(u8 slot, ItemID item) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_ITEM);

    mBuffer[memSpacer++] = slot;
    mBuffer[memSpacer++] = item;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_Item(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 slot     = mBuffer[memSpacer++];
    ItemID item = mBuffer[memSpacer++];

    // Ignore arrow type changes
    if (slot == SLOT_BOW && mSaveContext.items[slot] != ITEM_NONE) {
        return;
    }

    // Skip bottle content syncing except for removing Big Poes and Rutos Letter
    if (slot >= SLOT_BOTTLE_1 && slot <= SLOT_BOTTLE_4 && mSaveContext.items[slot] != ITEM_NONE &&
        !(item == ITEM_BOTTLE &&
          (mSaveContext.items[slot] == ITEM_BIG_POE || mSaveContext.items[slot] == ITEM_LETTER_RUTO))) {
        return;
    }
    // Skip post-letter child trade syncing, aka masks/sold out
    if (slot == SLOT_TRADE_CHILD && item != ITEM_NONE && item != ITEM_WEIRD_EGG && item != ITEM_CHICKEN &&
        item != ITEM_LETTER_ZELDA) {
        return;
    }
    // Adult trade slot/item syncing is handled in Multiplayer_Sync_SharedProgress
    if (slot == SLOT_TRADE_ADULT) {
        return;
    }

    // Add bombchu ammo when they're unlocked and in logic
    if (gSettingsContext.bombchusInLogic && slot == SLOT_BOMBCHU && mSaveContext.items[slot] == ITEM_NONE &&
        item != ITEM_NONE) {
        mSaveContext.ammo[SLOT_BOMBCHU] = 20;
        prevAmmo[SLOT_BOMBCHU]          = 20;
    }

    mSaveContext.items[slot] = item;
    prevItems[slot]          = item;
}

void Multiplayer_Send_MaxHealth(void) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_MAXHEALTH);

    mBuffer[memSpacer++] = gSaveContext.healthCapacity;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_MaxHealth(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u16 newMaxHealth = mBuffer[memSpacer++];

    mSaveContext.healthCapacity = newMaxHealth;
    prevHealthCapacity          = newMaxHealth;
}

void Multiplayer_Send_KokiriSwordEquip(void) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_KOKIRISWORDEQUIP);

    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_KokiriSwordEquip(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }

    mSaveContext.childEquipsButtonB = ITEM_SWORD_KOKIRI;
}

void Multiplayer_Send_BGSFlag(void) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_BGSFLAG);

    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_BGSFlag(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }

    mSaveContext.bgsFlag     = 1;
    mSaveContext.bgsHitsLeft = GK_SetDurability();
}

void Multiplayer_Send_MagicArrow(u8 type) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_MAGICARROW);

    mBuffer[memSpacer++] = type;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_MagicArrow(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF || !IsInGame()) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 type = mBuffer[memSpacer++];

    mp_duplicateSendProtection = true;
    ItemEffect_PlaceMagicArrowsInInventory(&gSaveContext, type, -1);
}

void Multiplayer_Send_GreatFairyBuff(u8 type) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_GREATFAIRYBUFF);

    mBuffer[memSpacer++] = type;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_GreatFairyBuff(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 type = mBuffer[memSpacer++];

    switch (type) {
        case 0:
            mSaveContext.doubleDefense = 1;
            break;
        case 1:
            mSaveContext.magicLevel     = 1;
            mSaveContext.magicAcquired  = 1;
            mSaveContext.magicMeterSize = 0x30;
            mSaveContext.magic          = 0x30;
            break;
        case 2:
            mSaveContext.magicLevel     = 2;
            mSaveContext.magicAcquired  = 1;
            mSaveContext.doubleMagic    = 1;
            mSaveContext.magicMeterSize = 0x60;
            mSaveContext.magic          = 0x60;
            break;
    }
}

void Multiplayer_Send_MagicBeanDiff(s8 diff) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_MAGICBEANDIFF);

    mBuffer[memSpacer++] = diff;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_MagicBeanDiff(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 beanDiff = mBuffer[memSpacer++];

    mSaveContext.ammo[SLOT_BEAN] += beanDiff;
    prevAmmo[SLOT_BEAN] += beanDiff;
}

void Multiplayer_Send_MagicBeansBoughtUpdate(void) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_MAGICBEANSBOUGHT);

    mBuffer[memSpacer++] = gSaveContext.magic_beans_available;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_MagicBeansBoughtUpdate(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 magic_beans_available = mBuffer[memSpacer++];

    mSaveContext.magic_beans_available = magic_beans_available;
    prevMagicBeansBought               = magic_beans_available;
}

void Multiplayer_Send_EquipmentBit(u8 bit, u8 setOrUnset) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_EQUIPMENT);

    mBuffer[memSpacer++] = bit;
    mBuffer[memSpacer++] = setOrUnset;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_EquipmentBit(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 bit        = mBuffer[memSpacer++];
    u8 setOrUnset = mBuffer[memSpacer++];

    // Giant's Knife / Biggoron Sword
    if (setOrUnset && bit == 2) {
        mSaveContext.bgsHitsLeft = GK_SetDurability();
    }

    // Don't remove losable shields or tunics
    if (!setOrUnset && (bit == 4 || bit == 5 || bit == 9 || bit == 10)) {
        return;
    }

    if (setOrUnset) {
        mSaveContext.equipment |= (1 << bit);
        prevEquipment |= (1 << bit);
    } else {
        mSaveContext.equipment &= ~(1 << bit);
        prevEquipment &= ~(1 << bit);
    }
}

void Multiplayer_Send_UpgradesBit(u8 bit, u8 setOrUnset) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_UPGRADES);

    mBuffer[memSpacer++] = bit;
    mBuffer[memSpacer++] = setOrUnset;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_UpgradesBit(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 bit        = mBuffer[memSpacer++];
    u8 setOrUnset = mBuffer[memSpacer++];

    if (setOrUnset) {
        mSaveContext.upgrades |= (1 << bit);
        prevUpgrades |= (1 << bit);
    } else {
        mSaveContext.upgrades &= ~(1 << bit);
        prevUpgrades &= ~(1 << bit);
    }

    // Add ammo
    if (setOrUnset) {
        u8 upgradeNum = 0;
        switch (bit) {
            case 0:
            case 1:
                upgradeNum                  = (mSaveContext.upgrades >> 0) & 0b11;
                mSaveContext.ammo[SLOT_BOW] = 30 + 10 * (upgradeNum - 1);
                prevAmmo[SLOT_BOW]          = 30 + 10 * (upgradeNum - 1);
                break;
            case 3:
            case 4:
                upgradeNum                   = (mSaveContext.upgrades >> 3) & 0b11;
                mSaveContext.ammo[SLOT_BOMB] = 20 + 10 * (upgradeNum - 1);
                prevAmmo[SLOT_BOMB]          = 20 + 10 * (upgradeNum - 1);
                break;
            case 14:
            case 15:
                upgradeNum                        = (mSaveContext.upgrades >> 14) & 0b11;
                mSaveContext.ammo[SLOT_SLINGSHOT] = 30 + 10 * (upgradeNum - 1);
                prevAmmo[SLOT_SLINGSHOT]          = 30 + 10 * (upgradeNum - 1);
                break;
            case 17:
            case 18:
                upgradeNum = (mSaveContext.upgrades >> 17) & 0b11;
                if (upgradeNum > 1) {
                    mSaveContext.ammo[SLOT_STICK] = 10 + 10 * (upgradeNum - 1);
                    prevAmmo[SLOT_STICK]          = 10 + 10 * (upgradeNum - 1);
                }
                break;
            case 20:
            case 21:
                upgradeNum = (mSaveContext.upgrades >> 20) & 0b11;
                if (upgradeNum > 1) {
                    mSaveContext.ammo[SLOT_NUT] = 20 + 10 * (upgradeNum - 1);
                    prevAmmo[SLOT_NUT]          = 20 + 10 * (upgradeNum - 1);
                }
                break;
        }
    }
}

void Multiplayer_Send_QuestItemBit(u8 bit, u8 setOrUnset) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_QUESTITEM);

    mBuffer[memSpacer++] = bit;
    mBuffer[memSpacer++] = setOrUnset;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_QuestItemBit(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 bit        = mBuffer[memSpacer++];
    u8 setOrUnset = mBuffer[memSpacer++];

    if (setOrUnset) {
        mSaveContext.questItems |= (1 << bit);
        prevQuestItems |= (1 << bit);
    } else {
        mSaveContext.questItems &= ~(1 << bit);
        prevQuestItems &= ~(1 << bit);
    }
}

void Multiplayer_Send_DungeonItemBit(u8 index, u8 bit, u8 setOrUnset) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_DUNGEONITEM);

    mBuffer[memSpacer++] = index;
    mBuffer[memSpacer++] = bit;
    mBuffer[memSpacer++] = setOrUnset;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_DungeonItemBit(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 index      = mBuffer[memSpacer++];
    u8 bit        = mBuffer[memSpacer++];
    u8 setOrUnset = mBuffer[memSpacer++];

    if (setOrUnset) {
        mSaveContext.dungeonItems[index] |= (1 << bit);
        prevDungeonItems[index] |= (1 << bit);
    } else {
        mSaveContext.dungeonItems[index] &= ~(1 << bit);
        prevDungeonItems[index] &= ~(1 << bit);
    }
}

void Multiplayer_Send_DungeonKeyUpdate(u8 index, s8 diff) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_DUNGEONKEY);

    mBuffer[memSpacer++] = index;
    mBuffer[memSpacer++] = diff;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_DungeonKeyUpdate(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 index = mBuffer[memSpacer++];
    s8 diff  = mBuffer[memSpacer++];

    mSaveContext.dungeonKeys[index] += diff;
    prevDungeonKeys[index] += diff;
}

void Multiplayer_Send_GSTokenDiff(s16 diff) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_GSTOKENDIFF);

    mBuffer[memSpacer++] = diff;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_GSTokenDiff(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    s16 diff = mBuffer[memSpacer++];

    mSaveContext.gsTokens += diff;
    prevGSTokens += diff;
}

void Multiplayer_Send_EventChkInfBit(u8 index, u8 bit, u8 setOrUnset) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_EVENTCHKINF);

    mBuffer[memSpacer++] = index;
    mBuffer[memSpacer++] = bit;
    mBuffer[memSpacer++] = setOrUnset;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_EventChkInfBit(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 index      = mBuffer[memSpacer++];
    u8 bit        = mBuffer[memSpacer++];
    u8 setOrUnset = mBuffer[memSpacer++];

    // Ignore Lake Hylia water switch
    if (index == 6 && bit == 9) {
        return;
    }

    // Ignore Tower Collapse cutscene flag
    if (index == 12 && bit == 7) {
        return;
    }

    if (setOrUnset) {
        mSaveContext.eventChkInf[index] |= (1 << bit);
        prevEventChkInf[index] |= (1 << bit);
    } else {
        mSaveContext.eventChkInf[index] &= ~(1 << bit);
        prevEventChkInf[index] &= ~(1 << bit);
    }
}

void Multiplayer_Send_ItemGetInfBit(u8 index, u8 bit, u8 setOrUnset) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_ITEMGETINF);

    mBuffer[memSpacer++] = index;
    mBuffer[memSpacer++] = bit;
    mBuffer[memSpacer++] = setOrUnset;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_ItemGetInfBit(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 index      = mBuffer[memSpacer++];
    u8 bit        = mBuffer[memSpacer++];
    u8 setOrUnset = mBuffer[memSpacer++];

    if (setOrUnset) {
        mSaveContext.itemGetInf[index] |= (1 << bit);
        prevItemGetInf[index] |= (1 << bit);
    } else {
        mSaveContext.itemGetInf[index] &= ~(1 << bit);
        prevItemGetInf[index] &= ~(1 << bit);
    }
}

void Multiplayer_Send_InfTableBit(u8 index, u8 bit, u8 setOrUnset) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_INFTABLE);

    mBuffer[memSpacer++] = index;
    mBuffer[memSpacer++] = bit;
    mBuffer[memSpacer++] = setOrUnset;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_InfTableBit(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 index      = mBuffer[memSpacer++];
    u8 bit        = mBuffer[memSpacer++];
    u8 setOrUnset = mBuffer[memSpacer++];

    if (setOrUnset) {
        mSaveContext.infTable[index] |= (1 << bit);
        prevInfTable[index] |= (1 << bit);
    } else {
        mSaveContext.infTable[index] &= ~(1 << bit);
        prevInfTable[index] &= ~(1 << bit);
    }
}

void Multiplayer_Send_ActorFlagBit(u8 member, u8 bit, u8 setOrUnset) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_ACTORFLAGS);

    mBuffer[memSpacer++] = gGlobalContext->sceneNum;
    mBuffer[memSpacer++] = member;
    mBuffer[memSpacer++] = bit;
    mBuffer[memSpacer++] = setOrUnset;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_ActorFlagBit(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    s16 scene     = mBuffer[memSpacer++];
    u8 member     = mBuffer[memSpacer++];
    u8 bit        = mBuffer[memSpacer++];
    u8 setOrUnset = mBuffer[memSpacer++];

    switch (member) {
        case 0: // swch
            if (setOrUnset) {
                mSaveContext.sceneFlags[scene].swch |= (1 << bit);
                prevSaveSceneFlags[scene].swch |= (1 << bit);

                if (gGlobalContext->sceneNum == scene) {
                    gGlobalContext->actorCtx.flags.swch |= (1 << bit);
                    prevActorFlags.swch |= (1 << bit);
                }
            } else {
                mSaveContext.sceneFlags[scene].swch &= ~(1 << bit);
                prevSaveSceneFlags[scene].swch &= ~(1 << bit);

                if (gGlobalContext->sceneNum == scene) {
                    gGlobalContext->actorCtx.flags.swch &= ~(1 << bit);
                    prevActorFlags.swch &= ~(1 << bit);
                }
            }
            break;
        case 1: // chest
            if (setOrUnset) {
                mSaveContext.sceneFlags[scene].chest |= (1 << bit);
                prevSaveSceneFlags[scene].chest |= (1 << bit);

                if (gGlobalContext->sceneNum == scene) {
                    gGlobalContext->actorCtx.flags.chest |= (1 << bit);
                    prevActorFlags.chest |= (1 << bit);
                }
            } else {
                mSaveContext.sceneFlags[scene].chest &= ~(1 << bit);
                prevSaveSceneFlags[scene].chest &= ~(1 << bit);

                if (gGlobalContext->sceneNum == scene) {
                    gGlobalContext->actorCtx.flags.chest &= ~(1 << bit);
                    prevActorFlags.chest &= ~(1 << bit);
                }
            }
            break;
        case 2: // clear
            if (setOrUnset) {
                mSaveContext.sceneFlags[scene].clear |= (1 << bit);
                prevSaveSceneFlags[scene].clear |= (1 << bit);

                if (gGlobalContext->sceneNum == scene) {
                    gGlobalContext->actorCtx.flags.clear |= (1 << bit);
                    prevActorFlags.clear |= (1 << bit);
                }
            } else {
                mSaveContext.sceneFlags[scene].clear &= ~(1 << bit);
                prevSaveSceneFlags[scene].clear &= ~(1 << bit);

                if (gGlobalContext->sceneNum == scene) {
                    gGlobalContext->actorCtx.flags.clear &= ~(1 << bit);
                    prevActorFlags.clear &= ~(1 << bit);
                }
            }
            break;
        case 3: // collect
            if (setOrUnset) {
                mSaveContext.sceneFlags[scene].collect |= (1 << bit);
                prevSaveSceneFlags[scene].collect |= (1 << bit);

                if (gGlobalContext->sceneNum == scene) {
                    gGlobalContext->actorCtx.flags.collect |= (1 << bit);
                    prevActorFlags.collect |= (1 << bit);
                }
            } else {
                mSaveContext.sceneFlags[scene].collect &= ~(1 << bit);
                prevSaveSceneFlags[scene].collect &= ~(1 << bit);

                if (gGlobalContext->sceneNum == scene) {
                    gGlobalContext->actorCtx.flags.collect &= ~(1 << bit);
                    prevActorFlags.collect &= ~(1 << bit);
                }
            }
            break;
    }
}

void Multiplayer_Send_SceneFlagBit(u8 scene, u8 member, u8 bit, u8 setOrUnset) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_SAVESCENEFLAG);

    mBuffer[memSpacer++] = scene;
    mBuffer[memSpacer++] = member;
    mBuffer[memSpacer++] = bit;
    mBuffer[memSpacer++] = setOrUnset;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_SceneFlagBit(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 scene      = mBuffer[memSpacer++];
    u8 member     = mBuffer[memSpacer++];
    u8 bit        = mBuffer[memSpacer++];
    u8 setOrUnset = mBuffer[memSpacer++];

    switch (member) {
        case 0:
            if (setOrUnset) {
                mSaveContext.sceneFlags[scene].unk |= (1 << bit);
                prevSaveSceneFlags[scene].unk |= (1 << bit);
            } else {
                mSaveContext.sceneFlags[scene].unk &= ~(1 << bit);
                prevSaveSceneFlags[scene].unk &= ~(1 << bit);
            }
            break;
        case 1:
            if (setOrUnset) {
                mSaveContext.sceneFlags[scene].rooms1 |= (1 << bit);
                prevSaveSceneFlags[scene].rooms1 |= (1 << bit);
            } else {
                mSaveContext.sceneFlags[scene].rooms1 &= ~(1 << bit);
                prevSaveSceneFlags[scene].rooms1 &= ~(1 << bit);
            }
            break;
        case 2:
            if (setOrUnset) {
                mSaveContext.sceneFlags[scene].rooms2 |= (1 << bit);
                prevSaveSceneFlags[scene].rooms2 |= (1 << bit);
            } else {
                mSaveContext.sceneFlags[scene].rooms2 &= ~(1 << bit);
                prevSaveSceneFlags[scene].rooms2 &= ~(1 << bit);
            }
            break;
    }
}

void Multiplayer_Send_GSFlagBit(u8 index, u8 bit, u8 setOrUnset) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_GSFLAGS);

    mBuffer[memSpacer++] = index;
    mBuffer[memSpacer++] = bit;
    mBuffer[memSpacer++] = setOrUnset;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_GSFlagBit(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 index      = mBuffer[memSpacer++];
    u8 bit        = mBuffer[memSpacer++];
    u8 setOrUnset = mBuffer[memSpacer++];

    if (setOrUnset) {
        mSaveContext.gsFlags[index] |= (1 << bit);
        prevGSFlags[index] |= (1 << bit);
    } else {
        mSaveContext.gsFlags[index] &= ~(1 << bit);
        prevGSFlags[index] &= ~(1 << bit);
    }
}

void Multiplayer_Send_BigPoePoints(u32 pointDiff) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_BIGPOEPOINTS);

    mBuffer[memSpacer++] = pointDiff;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_BigPoePoints(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u32 pointDiff = mBuffer[memSpacer++];

    mSaveContext.bigPoePoints += pointDiff;
    prevBigPoePoints += pointDiff;
}

void Multiplayer_Send_FishingFlag(u8 bit, u8 setOrUnset) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_FISHINGFLAG);

    mBuffer[memSpacer++] = bit;
    mBuffer[memSpacer++] = setOrUnset;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_FishingFlag(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 bit        = mBuffer[memSpacer++];
    u8 setOrUnset = mBuffer[memSpacer++];

    if (setOrUnset) {
        mSaveContext.fishingFlags |= (1 << bit);
        prevFishingFlags |= (1 << bit);
    } else {
        mSaveContext.fishingFlags &= ~(1 << bit);
        prevFishingFlags &= ~(1 << bit);
    }
}

void Multiplayer_Send_WorldMapBit(u8 bit, u8 setOrUnset) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_WORLDMAPBIT);

    mBuffer[memSpacer++] = bit;
    mBuffer[memSpacer++] = setOrUnset;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_WorldMapBit(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 bit        = mBuffer[memSpacer++];
    u8 setOrUnset = mBuffer[memSpacer++];

    if (setOrUnset) {
        mSaveContext.worldMapAreaData |= (1 << bit);
        prevWorldMapAreaData |= (1 << bit);
    } else {
        mSaveContext.worldMapAreaData &= ~(1 << bit);
        prevWorldMapAreaData &= ~(1 << bit);
    }
}

void Multiplayer_Send_ExtInfBit(u8 index, u8 bit, u8 setOrUnset) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_EXTINF);

    mBuffer[memSpacer++] = index;
    mBuffer[memSpacer++] = bit;
    mBuffer[memSpacer++] = setOrUnset;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_ExtInfBit(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u8 index      = mBuffer[memSpacer++];
    u8 bit        = mBuffer[memSpacer++];
    u8 setOrUnset = mBuffer[memSpacer++];

    if (setOrUnset) {
        mSaveContext.extInf[index] |= (1 << bit);
        prevExtInf[index] |= (1 << bit);
    } else {
        mSaveContext.extInf[index] &= ~(1 << bit);
        prevExtInf[index] &= ~(1 << bit);
    }
}

void Multiplayer_Send_DiscoveredScene(u32 index, u32 bit) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_DISCOVEREDSCENE);

    mBuffer[memSpacer++] = index;
    mBuffer[memSpacer++] = bit;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_DiscoveredScene(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u32 index = mBuffer[memSpacer++];
    u32 bit   = mBuffer[memSpacer++];

    mSaveContext.scenesDiscovered[index] |= bit;
}

void Multiplayer_Send_DiscoveredEntrance(u32 index, u32 bit) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_DISCOVEREDENTRANCE);

    mBuffer[memSpacer++] = index;
    mBuffer[memSpacer++] = bit;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_DiscoveredEntrance(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u32 index = mBuffer[memSpacer++];
    u32 bit   = mBuffer[memSpacer++];

    mSaveContext.entrancesDiscovered[index] |= bit;
}

void Multiplayer_Send_TriforcePieces(u32 piecesDiff) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_TRIFORCEPIECES);

    mBuffer[memSpacer++] = piecesDiff;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_TriforcePieces(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    u32 piecesDiff = mBuffer[memSpacer++];

    mSaveContext.triforcePieces += piecesDiff;

    if ((prevTriforcePieces < gSettingsContext.triforcePiecesRequired) &&
        (mSaveContext.triforcePieces >= gSettingsContext.triforcePiecesRequired)) {
        TriforceWarpStatus = TRIFORCEWARP_WHEN_PLAYER_READY;
    }

    prevTriforcePieces += piecesDiff;
}

void Multiplayer_Send_UnlockedDoor(u32 flag) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_UNLOCKEDDOOR);

    // Set this prev flag to prevent sending the swch bit packet.
    prevSaveSceneFlags[gGlobalContext->sceneNum].swch |= (1 << flag);

    mBuffer[memSpacer++] = gGlobalContext->sceneNum;
    mBuffer[memSpacer++] = gSaveContext.dungeonIndex;
    mBuffer[memSpacer++] = flag;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_UnlockedDoor(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    s16 sceneNum     = mBuffer[memSpacer++];
    u16 dungeonIndex = mBuffer[memSpacer++];
    u32 flag         = mBuffer[memSpacer++];

    if (mSaveContext.sceneFlags[sceneNum].swch & (1 << flag)) {
        return;
    }

    mSaveContext.dungeonKeys[dungeonIndex]--;
    prevDungeonKeys[dungeonIndex]--;
    mSaveContext.sceneFlags[sceneNum].swch |= (1 << flag);
    prevSaveSceneFlags[sceneNum].swch |= (1 << flag);
}

void Multiplayer_Send_ActorUpdate(Actor* actor, void* extraData, u32 extraDataSize) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_ACTORUPDATE);

    mBuffer[memSpacer++] = gGlobalContext->sceneNum;
    mBuffer[memSpacer++] = gGlobalContext->roomNum;
    mBuffer[memSpacer++] = actor->id;
    mBuffer[memSpacer++] = actor->type;
    mBuffer[memSpacer++] = actor->params;
    memcpy(&mBuffer[memSpacer], &actor->home, sizeof(PosRot));
    memSpacer += sizeof(PosRot) / 4;
    // Always keep extra data last
    memcpy(&mBuffer[memSpacer], extraData, extraDataSize);
    memSpacer += (extraDataSize / 4) + 1;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_ActorUpdate(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    s16 sceneNum = mBuffer[memSpacer++];
    u8 roomNum   = mBuffer[memSpacer++];

    if (sceneNum != gGlobalContext->sceneNum || roomNum != gGlobalContext->roomNum) {
        return;
    }

    s16 actorId     = mBuffer[memSpacer++];
    u8 actorType    = mBuffer[memSpacer++];
    s16 actorParams = mBuffer[memSpacer++];
    PosRot actorHome;
    memcpy(&actorHome, &mBuffer[memSpacer], sizeof(PosRot));
    memSpacer += sizeof(PosRot) / 4;

    u8 amountWithSameParams = 0;
    for (Actor* actor = gGlobalContext->actorCtx.actorList[actorType].first; actor != NULL; actor = actor->next) {
        if (actor->id != actorId) {
            continue;
        }
        if (actor->params == actorParams) {
            amountWithSameParams++;
            if (amountWithSameParams >= 2) {
                // No need to search for more
                break;
            }
        }
    }
    for (Actor* actor = gGlobalContext->actorCtx.actorList[actorType].first; actor != NULL; actor = actor->next) {
        if (actor->id != actorId) {
            continue;
        }
        // If only one actor has the same params, check for that. Otherwise use the home PosRot
        if ((amountWithSameParams <= 1 && actor->params == actorParams) ||
            (amountWithSameParams > 1 && (s32)actorHome.pos.x == (s32)actor->home.pos.x &&
             actorHome.rot.x == actor->home.rot.x && (s32)actorHome.pos.y == (s32)actor->home.pos.y &&
             actorHome.rot.y == actor->home.rot.y && (s32)actorHome.pos.z == (s32)actor->home.pos.z &&
             actorHome.rot.z == actor->home.rot.z)) {
            switch (actorId) {
                case 0x4: // Shop Items
                {
                    u16 index = (u16)mBuffer[memSpacer];
                    ShopsanityItem_SellOut(actor, index);
                    break;
                }
                case 0x9: // Regular Doors
                    EnDoor_Unlock((EnDoor*)actor);
                    break;
                case 0x2E: // Shutter Doors
                    DoorShutter_Unlock((DoorShutter*)actor);
                    break;
                case 0x95: // Gold Skulltulas
                    EnSw_Kill((EnSw*)actor, gGlobalContext);
                    break;
                case 0x9C: // Royal Grave
                    BgSpot02Objects_ExplodeGrave((BgSpot02Objects*)actor);
                    break;
                case 0xFF: // Pushblocks
                {
                    Vec3f newPos;
                    memcpy(&newPos, &mBuffer[memSpacer], sizeof(Vec3f));
                    actor->world.pos = newPos;
                    actor->home.pos  = newPos;
                    break;
                }
                case 0x11A: // Business Scrubs
                    EnDns_StartBurrow((EnDns*)actor);
                    break;
                case 0x126: // Bean Plant (Child)
                    ObjBean_StartGrowth((ObjBean*)actor);
                    break;
                case 0x12C: // Collapsing Platforms
                {
                    void* new_action_fn = (void*)mBuffer[memSpacer];
                    ObjLift_SetActionFn((ObjLift*)actor, new_action_fn);
                    break;
                }
                case 0x133: // Carpenters
                    EnDaiku_StartEscape((EnDaiku*)actor);
                    break;
                case 0x14E: // Silver Boulders
                    Flags_SetSwitch(gGlobalContext, (actor->params >> 10 & 0x3C) | (actor->params << 0x18) >> 0x1E);
                    Actor_Kill(actor);
                    break;
                case 0x172: // Theives' Hideout Cell Doors
                    DoorGerudo_Unlock((DoorGerudo*)actor);
                    break;
                case 0x1D2: // Red Boulders
                    ObjHamishi_Hit((ObjHamishi*)actor);
                    break;
            }
        }
    }

    // Extra/Alternate actions
    switch (actorId) {
        case 0xF: // Spider Webs
        {
            BgYdanSp_SendData sendData;
            memcpy(&sendData, &mBuffer[memSpacer], sizeof(BgYdanSp_SendData));
            for (Actor* actor = gGlobalContext->actorCtx.actorList[actorType].first; actor != NULL;
                 actor        = actor->next) {
                if (actor->id != actorId) {
                    continue;
                }
                if ((s32)sendData.homePos.x == (s32)actor->home.pos.x &&
                    (s32)sendData.homePos.y == (s32)actor->home.pos.y &&
                    (s32)sendData.homePos.z == (s32)actor->home.pos.z) {
                    BgYdanSp_SetActionFn((BgYdanSp*)actor, sendData.action_fn);
                    break;
                }
            }
            break;
        }
        case 0x107: // Milk Crates
        {
            BgSpot15Rrbox_SendData sendData;
            memcpy(&sendData, &mBuffer[memSpacer], sizeof(BgSpot15Rrbox_SendData));
            for (Actor* actor = gGlobalContext->actorCtx.actorList[actorType].first; actor != NULL;
                 actor        = actor->next) {
                if (actor->id != actorId) {
                    continue;
                }
                if ((s32)sendData.focusPos.x == (s32)actor->focus.pos.x &&
                    (s32)sendData.focusPos.y == (s32)actor->focus.pos.y &&
                    (s32)sendData.focusPos.z == (s32)actor->focus.pos.z) {
                    actor->world.pos = sendData.worldPos;
                    actor->home.pos  = sendData.worldPos;
                    break;
                }
            }
            break;
        }
        case 0x11A: // Business Scrubs
            for (Actor* actor = gGlobalContext->actorCtx.actorList[ACTORTYPE_ENEMY].first; actor != NULL;
                 actor        = actor->next) {
                if (actor->id != 0x195) {
                    continue;
                }
                if ((s32)actorHome.pos.x == (s32)actor->home.pos.x && (s32)actorHome.pos.y == (s32)actor->home.pos.y &&
                    (s32)actorHome.pos.z == (s32)actor->home.pos.z) {
                    Actor_Kill(actor);
                    break;
                }
            }
            break;
        case 0x126: // Bean Plant (Adult)
            if (gSaveContext.linkAge == 0 && Actor_Find(&gGlobalContext->actorCtx, actorId, actorType) == NULL) {
                // Set flag so it doesn't despawn. Needs to be set in gSaveContext, even though
                // it gets overwritten later, because the actor init function gets called in Actor_Spawn.
                Flags_SetSwitch(gGlobalContext, lastBeanPlant_Params & 0x3F);
                Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, actorId, lastBeanPlant_Home.pos.x,
                            lastBeanPlant_Home.pos.y, lastBeanPlant_Home.pos.z, lastBeanPlant_Home.rot.x,
                            lastBeanPlant_Home.rot.y, lastBeanPlant_Home.rot.z, lastBeanPlant_Params, FALSE);
            }
            break;
    }
}

void Multiplayer_Send_ActorSpawn(s16 actorId, PosRot posRot, s16 params) {
    if (!IsSendReceiveReady() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_ACTORSPAWN);

    mBuffer[memSpacer++] = gGlobalContext->sceneNum;
    mBuffer[memSpacer++] = gGlobalContext->roomNum;
    mBuffer[memSpacer++] = actorId;
    memcpy(&mBuffer[memSpacer], &posRot, sizeof(PosRot));
    memSpacer += sizeof(PosRot) / 4;
    mBuffer[memSpacer++] = params;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_ActorSpawn(u16 senderID) {
    if (!IsInSameSyncGroup() || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    s16 sceneNum = mBuffer[memSpacer++];
    u8 roomNum   = mBuffer[memSpacer++];

    if (sceneNum != gGlobalContext->sceneNum || roomNum != gGlobalContext->roomNum || !IsInGame()) {
        return;
    }

    s16 actorId = mBuffer[memSpacer++];
    PosRot rcvdPosRot;
    memcpy(&rcvdPosRot, &mBuffer[memSpacer], sizeof(PosRot));
    memSpacer += sizeof(PosRot) / 4;
    s16 params = mBuffer[memSpacer++];

    Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, actorId, rcvdPosRot.pos.x, rcvdPosRot.pos.y,
                rcvdPosRot.pos.z, rcvdPosRot.rot.x, rcvdPosRot.rot.y, rcvdPosRot.rot.z, params, FALSE);
}

// Etc

void Multiplayer_Send_HealthChange(s16 diff) {
    if (!IsSendReceiveReady()) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_HEALTHCHANGE);

    mBuffer[memSpacer++] = gSaveContext.health;
    mBuffer[memSpacer++] = diff;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_HealthChange(u16 senderID) {
    if (gSettingsContext.mp_SharedHealth == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    s16 newHealth = mBuffer[memSpacer++];
    s16 diff      = mBuffer[memSpacer++];

    if (gSettingsContext.mp_SharedProgress == ON) {
        if (IsInSameSyncGroup()) {
            mSaveContext.health = newHealth;
        } else {
            mSaveContext.health += diff;

            if (mSaveContext.health > mSaveContext.healthCapacity) {
                mSaveContext.health = mSaveContext.healthCapacity;
            } else if (mSaveContext.health < 0) {
                mSaveContext.health = 0;
            }
        }
        prevHealth = mSaveContext.health;
    } else {
        if (!IsInGame()) {
            return;
        }
        gSaveContext.health += diff;

        SaveFile_EnforceHealthLimit();

        prevHealth = gSaveContext.health;
    }
}

void Multiplayer_Send_RupeeChange(s16 diff) {
    if (!IsSendReceiveReady()) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_RUPEESCHANGE);

    mBuffer[memSpacer++] = gSaveContext.rupees;
    mBuffer[memSpacer++] = diff;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_RupeeChange(u16 senderID) {
    if (gSettingsContext.mp_SharedRupees == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    s16 newRupees = mBuffer[memSpacer++];
    s16 diff      = mBuffer[memSpacer++];

    if (gSettingsContext.mp_SharedProgress == ON) {
        if (IsInSameSyncGroup()) {
            mSaveContext.rupees = newRupees;
        } else {
            mSaveContext.rupees += diff;

            static u16 maxRupees[] = { 99, 200, 500, 999 };
            u8 upgrade             = mSaveContext.upgrades >> 12 & 0x3;
            if (mSaveContext.rupees > maxRupees[upgrade]) {
                mSaveContext.rupees = maxRupees[upgrade];
            } else if (mSaveContext.rupees < 0) {
                mSaveContext.rupees = 0;
            }
        }
        prevRupees = mSaveContext.rupees;
    } else {
        if (!IsInGame()) {
            return;
        }
        gSaveContext.rupees += diff;

        static const u16 maxRupees[] = { 99, 200, 500, 999 };
        u8 upgrade                   = gSaveContext.upgrades >> 12 & 0x3;
        if (gSaveContext.rupees > maxRupees[upgrade]) {
            gSaveContext.rupees = maxRupees[upgrade];
        } else if (gSaveContext.rupees < 0) {
            gSaveContext.rupees = 0;
        }

        prevRupees = gSaveContext.rupees;
    }
}

void Multiplayer_Send_AmmoChange(u8 slot, s8 diff) {
    if (!IsSendReceiveReady()) {
        return;
    }
    memset(mBuffer, 0, mBufSize);
    u8 memSpacer = PrepareSharedProgressPacket(PACKET_AMMOCHANGE);

    mBuffer[memSpacer++] = gSaveContext.ammo[slot];
    mBuffer[memSpacer++] = slot;
    mBuffer[memSpacer++] = diff;
    Multiplayer_SendPacket(memSpacer, UDS_BROADCAST_NETWORKNODEID);
}

void Multiplayer_Receive_AmmoChange(u16 senderID) {
    if (gSettingsContext.mp_SharedAmmo == OFF) {
        return;
    }
    u8 memSpacer = GetSharedProgressMemSpacerOffset();

    s8 newAmmo = mBuffer[memSpacer++];
    u8 slot    = mBuffer[memSpacer++];
    s8 diff    = mBuffer[memSpacer++];

    // TODO: Don't go over max
    if (gSettingsContext.mp_SharedProgress == ON) {
        if (IsInSameSyncGroup()) {
            mSaveContext.ammo[slot] = newAmmo;
        } else {
            mSaveContext.ammo[slot] += diff;
            if (mSaveContext.ammo[slot] < 0) {
                mSaveContext.ammo[slot] = 0;
            }
        }
        prevAmmo[slot] = mSaveContext.ammo[slot];
    } else {
        if (!IsInGame()) {
            return;
        }
        gSaveContext.ammo[slot] += diff;
        if (gSaveContext.ammo[slot] < 0) {
            gSaveContext.ammo[slot] = 0;
        }
        prevAmmo[slot] = gSaveContext.ammo[slot];
    }
}

// Send & Receive

static void Multiplayer_SendPacket(u16 packageSize, u16 targetID) {
    udsSendTo(targetID, data_channel, UDS_SENDFLAG_Default, mBuffer, packageSize * sizeof(mBuffer[0]));
}

void Multiplayer_ReceivePackets() {
    if (!IsSendReceiveReady()) {
        return;
    }

    if (gSettingsContext.mp_SharedProgress == ON && IsInGame()) {
        gSaveContext.sceneFlags[gGlobalContext->sceneNum].swch    = gGlobalContext->actorCtx.flags.swch;
        gSaveContext.sceneFlags[gGlobalContext->sceneNum].chest   = gGlobalContext->actorCtx.flags.chest;
        gSaveContext.sceneFlags[gGlobalContext->sceneNum].clear   = gGlobalContext->actorCtx.flags.clear;
        gSaveContext.sceneFlags[gGlobalContext->sceneNum].collect = gGlobalContext->actorCtx.flags.collect;
        Multiplayer_Overwrite_mSaveContext();
    }

    mp_receivedPackets = 0;
    size_t actual_size = 0;
    do {
        memset(mBuffer, 0, mBufSize);
        u16 src_NetworkNodeID = 0;
        udsPullPacket(&bindctx, mBuffer, mBufSize, &actual_size, &src_NetworkNodeID);
        if (actual_size) {
            Multiplayer_UnpackPacket(src_NetworkNodeID);
        }
    } while (actual_size);

    if (gSettingsContext.mp_SharedProgress == ON && IsInGame()) {
        Multiplayer_Overwrite_gSaveContext();
    }
}

static void Multiplayer_UnpackPacket(u16 senderID) {
    mp_receivedPackets++;
    PacketIdentifier identifier = mBuffer[0];

    // Make sure these are lined up with the PacketIdentifier enum
    static void (*receive_funcs[])(u16 senderID_) = {
        // Ghost Data
        Multiplayer_Receive_GhostPing,
        Multiplayer_Receive_GhostData,
        Multiplayer_Receive_GhostData_JointTable,
        Multiplayer_Receive_LinkSFX,
        // Shared Progress
        Multiplayer_Receive_FullSyncRequest,
        Multiplayer_Receive_FullSyncPing,
        Multiplayer_Receive_BaseSync,
        Multiplayer_Receive_FullSceneFlagSync,
        Multiplayer_Receive_FullEntranceSync,
        Multiplayer_Receive_Item,
        Multiplayer_Receive_MaxHealth,
        Multiplayer_Receive_KokiriSwordEquip,
        Multiplayer_Receive_BGSFlag,
        Multiplayer_Receive_MagicArrow,
        Multiplayer_Receive_GreatFairyBuff,
        Multiplayer_Receive_MagicBeanDiff,
        Multiplayer_Receive_MagicBeansBoughtUpdate,
        Multiplayer_Receive_EquipmentBit,
        Multiplayer_Receive_UpgradesBit,
        Multiplayer_Receive_QuestItemBit,
        Multiplayer_Receive_DungeonItemBit,
        Multiplayer_Receive_DungeonKeyUpdate,
        Multiplayer_Receive_GSTokenDiff,
        Multiplayer_Receive_EventChkInfBit,
        Multiplayer_Receive_ItemGetInfBit,
        Multiplayer_Receive_InfTableBit,
        Multiplayer_Receive_ActorFlagBit,
        Multiplayer_Receive_SceneFlagBit,
        Multiplayer_Receive_GSFlagBit,
        Multiplayer_Receive_BigPoePoints,
        Multiplayer_Receive_FishingFlag,
        Multiplayer_Receive_WorldMapBit,
        Multiplayer_Receive_ExtInfBit,
        Multiplayer_Receive_DiscoveredScene,
        Multiplayer_Receive_DiscoveredEntrance,
        Multiplayer_Receive_TriforcePieces,
        Multiplayer_Receive_UnlockedDoor,
        Multiplayer_Receive_ActorUpdate,
        Multiplayer_Receive_ActorSpawn,
        // Etc
        Multiplayer_Receive_HealthChange,
        Multiplayer_Receive_RupeeChange,
        Multiplayer_Receive_AmmoChange,
    };

    receive_funcs[identifier](senderID);
}
