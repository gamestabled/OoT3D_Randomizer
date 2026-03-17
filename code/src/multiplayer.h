#ifndef _MULTIPLAYER_H_
#define _MULTIPLAYER_H_

#include "3ds/types.h"
#include "z3D/z3D.h"
#include "savefile.h"

#define EXTINF_SYNC_PART_SIZE 0x400
// Count of parts that ExtInf will be split into for syncing
#define EXTINF_SYNCS_COUNT (EXTINF_SIZE / EXTINF_SYNC_PART_SIZE + 1)

enum FullSyncType {
    FULLSYNC_BASE,
    FULLSYNC_ENTRANCES,
    FULLSYNC_FLAGS_FIRST,
    FULLSYNC_FLAGS_LAST = FULLSYNC_FLAGS_FIRST + 3,
    FULLSYNC_EXTINF_FIRST,
    FULLSYNC_MAX = FULLSYNC_EXTINF_FIRST + EXTINF_SYNCS_COUNT,
};

typedef struct PacketMask {
    // 1 bit for each needed sync part
    u8 arr[FULLSYNC_MAX / 8 + 1];
} PacketMask;

static inline bool PacketMask_GetBit(PacketMask* mask, size_t bitIdx) {
    return (mask->arr[bitIdx >> 3] & (1 << (bitIdx & 0b111))) != 0;
}
static inline void PacketMask_SetBit(PacketMask* mask, size_t bitIdx) {
    mask->arr[bitIdx >> 3] |= (1 << (bitIdx & 0b111));
}

extern u32 mp_receivedPackets;
extern bool mp_duplicateSendProtection;
extern bool mp_isSyncing;
extern bool mp_foundSyncer;
extern bool mp_completeSyncs[FULLSYNC_MAX];
extern bool mSaveContextInit;
extern u16 mp_fullSyncerID;

void Multiplayer_Run(void);
void Multiplayer_Update(u8 fromGlobalContextUpdate);
s8 Multiplayer_PlayerCount();
void Multiplayer_Sync_Update(void);
void Multiplayer_ReceivePackets();
void Multiplayer_OnFileLoad(void);

// Ghost Data
void Multiplayer_Send_GhostPing(void);
void Multiplayer_Send_GhostData(void);
void Multiplayer_Send_GhostData_JointTable(void);
void Multiplayer_Send_LinkSFX(u32 sfxID);
// Shared Progress
PacketMask Multiplayer_GetNeededPacketsMask(void);
void Multiplayer_Send_FullSyncProviderRequest(void);
void Multiplayer_Send_FullSyncProviderOffer(u16 targetID);
void Multiplayer_Send_FullSyncRequest(PacketMask neededPackets);
void Multiplayer_Send_BaseSync(u16 targetID);
void Multiplayer_Send_FullSceneFlagSync(u16 targetID, u8 part);
void Multiplayer_Send_Item(u8 slot, ItemID item);
void Multiplayer_Send_KokiriSwordEquip(void);
void Multiplayer_Send_MaxHealth(void);
void Multiplayer_Send_BGSFlag(void);
void Multiplayer_Send_MagicArrow(u8 type);
void Multiplayer_Send_GreatFairyBuff(u8 type);
void Multiplayer_Send_MagicBeanDiff(s8 diff);
void Multiplayer_Send_MagicBeansBoughtUpdate();
void Multiplayer_Send_EquipmentBit(u8 bit, u8 setOrUnset);
void Multiplayer_Send_UpgradesBit(u8 bit, u8 setOrUnset);
void Multiplayer_Send_QuestItemBit(u8 bit, u8 setOrUnset);
void Multiplayer_Send_DungeonItemBit(u8 index, u8 bit, u8 setOrUnset);
void Multiplayer_Send_DungeonKeyUpdate(u8 index, s8 diff);
void Multiplayer_Send_GSTokenDiff(s16 diff);
void Multiplayer_Send_EventChkInfBit(u8 index, u8 bit, u8 setOrUnset);
void Multiplayer_Send_ItemGetInfBit(u8 index, u8 bit, u8 setOrUnset);
void Multiplayer_Send_InfTableBit(u8 index, u8 bit, u8 setOrUnset);
void Multiplayer_Send_ActorFlagBit(u8 index, u8 bit, u8 setOrUnset);
void Multiplayer_Send_SceneFlagBit(u8 scene, u8 member, u8 bit, u8 setOrUnset);
void Multiplayer_Send_GSFlagBit(u8 index, u8 bit, u8 setOrUnset);
void Multiplayer_Send_BigPoePoints(u32 pointDiff);
void Multiplayer_Send_FishingFlag(u8 bit, u8 setOrUnset);
void Multiplayer_Send_WorldMapBit(u8 bit, u8 setOrUnset);
void Multiplayer_Send_ExtInfBit(u16 index, u8 bit, u8 setOrUnset);
void Multiplayer_Send_TriforcePieces(u32 piecesDiff);
void Multiplayer_Send_FullEntranceSync(u16 targetID);
void Multiplayer_Send_FullExtInfSync(u16 targetID, u8 partIdx);
void Multiplayer_Send_DiscoveredScene(u32 index, u32 bit);
void Multiplayer_Send_DiscoveredEntrance(u32 index, u32 bit);
void Multiplayer_Send_UnlockedDoor(u32 flag);
void Multiplayer_Send_ActorUpdate(Actor* actor, void* extraData, u32 extraDataSize);
void Multiplayer_Send_ActorSpawn(s16 actorId, PosRot posRot, s16 params);
// Etc
void Multiplayer_Send_HealthChange(s16 diff);
void Multiplayer_Send_RupeeChange(s16 diff);
void Multiplayer_Send_AmmoChange(u8 index, s8 diff);

#endif //_MULTIPLAYER_H_
