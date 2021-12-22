#ifndef _COMMON_H_
#define _COMMON_H_

#include "../include/z3D/z3D.h"
#include "../include/3ds/svc.h"
#include "../include/lib/printf.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

#define SEQ_AUDIO_BLANK 0x1000142

u32 Hash(u32);
u8  Bias(u32);

u8 IsInGame(void);
void DebugPrintNumber(const char *, int);

#endif //_COMMON_H_
