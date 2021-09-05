#ifndef _SFX_H_
#define _SFX_H_

#define SFX_BASE 0x1000001
#define SFX_COUNT 1388
#define SFX_COUNT_TRIMMED (1388 - 213)

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
    /// Contains the amount of sound effects in each group, excluding SEQ_NOSHUFFLE.
    u16 rSeqMaxes[SEQTYPE_COUNT];

    /// Contains the original list of SeqTypes.
    /// Can be used to check which type a sound effect is.
    SeqType rSeqTypesSFX[SFX_COUNT];

    /// Contains all sound effects.
    u32 rSFXOverrides_All[SFX_COUNT];

    /// Contains all sound effects excluding SEQ_NOSHUFFLE.
    u32 rSFXOverrides_AllTrimmed[SFX_COUNT_TRIMMED];

    /// Contains all sound effects grouped into their SeqTypes.
    /// The size of the second dimension should be the amount in the largest group, currently SEQ_ENEMY.
    u32 rSFXOverrides_Types[SEQTYPE_COUNT][264];
} SFXData;

extern SFXData rSfxData;

u32 SetSFX(u32 original);

#endif // _SFX_H_
