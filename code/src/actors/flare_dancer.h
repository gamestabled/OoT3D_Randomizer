#ifndef _FLARE_DANCER_H_
#define _FLARE_DANCER_H_

#include "z3D/z3D.h"
#include "colors.h"

struct EnFd;
struct EnFdFire;

typedef void (*EnFdActionFunc)(struct EnFd*, GlobalContext*);
typedef void (*EnFdFireActionFunc)(struct EnFdFire*, GlobalContext*);

typedef enum FdEffectType {
    FD_EFFECT_NONE,
    FD_EFFECT_FLAME,
    FD_EFFECT_DOT
} FdEffectType;

#define EN_FD_EFFECT_COUNT 100

typedef struct EnFdEffect {
    /* 0x0000 */ u8 type;
    /* 0x0001 */ u8 timer;
    /* 0x0002 */ u8 initialTimer;
    /* 0x0004 */ f32 scale;
    /* 0x0008 */ f32 scaleStep;
    /* 0x000C */ Color_RGBA8 color;
    /* 0x0010 */ char unk_10[4];
    /* 0x0014 */ Vec3f pos;
    /* 0x0020 */ Vec3f velocity;
    /* 0x002C */ Vec3f accel;
    /* 0x0038 */ char unk_38[4];
} EnFdEffect;
_Static_assert(sizeof(EnFdEffect) == 0x3C, "EnFdEffect size");

typedef struct EnFd {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ SkelAnime skelAnime;
    /* 0x0228 */ char unk_0228[0x004];
    /* 0x022C */ EnFdActionFunc actionFunc;
    /* 0x0230 */ char unk_0230[0xC28];
    /* 0x0E58 */ EnFdEffect effects[EN_FD_EFFECT_COUNT];
    /* 0x25C8 */ char unk_25C8[0x324];
} EnFd;
_Static_assert(sizeof(EnFd) == 0x28EC, "EnFd size");

typedef struct EnFdFire {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ EnFdFireActionFunc actionFunc;
    /* 0x01A8 */ ColliderCylinder collider;
    /* 0x0200 */ f32 spawnRadius;
    /* 0x0204 */ f32 scale;
    /* 0x0208 */ char unk_208[0x2];
    /* 0x020A */ s16 deathTimer;
    /* 0x020C */ s16 tile2Y;
    /* 0x020E */ char unk_20E[0xE];
} EnFdFire;
_Static_assert(sizeof(EnFdFire) == 0x21C, "EnFdFire size");

void EnFd_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_FLARE_DANCER_H_
