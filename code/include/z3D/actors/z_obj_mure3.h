#ifndef Z_OBJ_MURE3_H
#define Z_OBJ_MURE3_H

#include "z3D/z3D.h"

typedef void (*ObjMure3ActionFunc)(struct Actor*, struct GlobalContext*);
typedef void (*ObjMure3SpawnFunc)(struct Actor*, struct GlobalContext*);

struct ObjMure3;

typedef struct ObjMure3 {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ ObjMure3ActionFunc actionFunc;
    /* 0x0150 */ struct EnItem00* spawnedRupees[7];
    /* 0x016C */ u16 unk_16C;
} ObjMure3; // size = 0x0170

#endif
