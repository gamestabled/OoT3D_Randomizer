#ifndef _MULTIPLAYER_H_
#define _MULTIPLAYER_H_

#include "3ds/types.h"
#include "z3D/z3D.h"

extern u32 mp_receivedPackets;
extern bool mp_duplicateSendProtection;
extern bool mp_isSyncing;
extern bool mp_foundSyncer;
extern bool mp_completeSyncs[6];
extern bool mSaveContextInit;

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
u8 Multiplayer_GetNeededPacketsMask(void);
void Multiplayer_Send_FullSyncRequest(u8 neededPacketsMask);
void Multiplayer_Send_FullSyncPing(u16 targetID);
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
void Multiplayer_Send_ExtInfBit(u8 index, u8 bit, u8 setOrUnset);
void Multiplayer_Send_TriforcePieces(u32 piecesDiff);
void Multiplayer_Send_FullEntranceSync(u16 targetID);
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
