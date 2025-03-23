#ifndef _COMMON_H_
#define _COMMON_H_

#include "../include/z3D/z3D.h"

#include <stdarg.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#define BIT_COUNT(x) (sizeof(x) * 8)
#define ABS(x) ((x) >= 0 ? (x) : -(x))

#define TICKS_PER_SEC 268123480
#define SEQ_AUDIO_BLANK 0x1000142

extern u8 playingOnCitra;
extern u32 rGameplayFrames; // globalCtx->gameplayFrames is not accurate, it doesn't increment on file 3

/// Returns 1 if the bit is set in value1 but not in value2, -1 if vice versa, and 0 if they're the same
s8 BitCompare(u32 value1, u32 value2, u8 bit);

u32 Hash(u32);
u8 Bias(u32);

u8 IsInGame(void);
u8 IsInGameOrBossChallenge(void);
void CitraPrint(const char*, ...);

#endif //_COMMON_H_
