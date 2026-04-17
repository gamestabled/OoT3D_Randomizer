#ifndef _Z3DAUDIO_H_
#define _Z3DAUDIO_H_

#include "s_types.h"
#include "s_seq_id.h"

typedef enum SequencePlayerId {
    /* 0 */ SEQ_PLAYER_BGM_MAIN,
    /* 1 */ SEQ_PLAYER_FANFARE,
    /* 2 */ SEQ_PLAYER_SFX,
    /* 3 */ SEQ_PLAYER_BGM_SUB,
    /* 4 */ SEQ_PLAYER_MAX,
} SequencePlayerId;

typedef struct UnkSequencePlayerData {
    /* 0x00 */ void* vTable;
    /* 0x04 */ char unk_04[0x2C];
    /* 0x30 */ f32 volume;
    /* 0x34 */ f32 freq;
    // ...
} UnkSequencePlayerData;

extern UnkSequencePlayerData* gUnkSequencePlayerData[SEQ_PLAYER_MAX];

extern f32 gSfxDefaultFreqAndVolScale;
extern s8 gSfxDefaultReverb;
extern s32 sPrevMainBgmSeqId;

void Audio_PlaySfxGeneral(u32 sfxId, Vec3f* pos, u32 token, f32* freqScale, f32* a4, s8* reverbAdd);
// This function plays sound effects and music tracks, overlaid on top of the current BGM
void Audio_PlayFanfare(u32);
u32 Audio_GetActiveSeqId(SequencePlayerId seqPlayerIndex);
// Restores the original sequence to the main BGM player after a mini-boss battle or a minigame.
void Audio_RestoreBGM(void);
void Audio_PlaySequence(SequencePlayerId seqPlayerIndex, u32 seqId);
void Audio_StopSequence(SequencePlayerId seqPlayerId, u32 fadeOutDuration);

#endif //_Z3DAUDIO_H_
