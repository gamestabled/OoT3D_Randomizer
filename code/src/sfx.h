#ifndef _SFX_H_
#define _SFX_H_

#define SFX_BASE 0x1000001
#define SFX_COUNT 1388

typedef enum {
    // General Categories
    SEQ_PLAYER,
    SEQ_ITEM,
    SEQ_EVENT,
    SEQ_ENEMY,
    SEQ_SYSTEM,
    SEQ_VOICE,
    // Specific Categories
    SEQ_WALK,
    SEQ_MOVE,
    SEQ_JUMP,
    SEQ_LAND,
    SEQ_FLY,
    SEQ_DEAD,
    SEQ_DAMAGE,
    SEQ_ATTACK,
    SEQ_AMBIENCE,
    // Meta
    SEQTYPE_COUNT,
    SEQ_NOSHUFFLE = 0xFF,
} SeqType;

typedef struct {
    u16 rSeqMaxes[SEQTYPE_COUNT];
    SeqType rSeqTypesSFX[SFX_COUNT];
    u32 rSFXOverrides_All[SFX_COUNT];
    u32 rSFXOverrides_Types[SEQTYPE_COUNT][268];
} SFXData;

extern SFXData rSfxData;

u32 SetSFX(u32 original);

#endif // _SFX_H_
