#ifndef _Z3DEFFECT_H_
#define _Z3DEFFECT_H_

#include "z3Dvec.h"
#include "z3Dcolor.h"

/* Effects */

#define SPARK_COUNT 24
#define BLURE_COUNT 25
#define SHIELD_PARTICLE_COUNT 10

typedef struct EffectStatus {
    /* 0x00 */ u8 active;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x02 */ char _pad_04;
} EffectStatus;

typedef struct EffectSpark {
    /* 0x000 */ char unk_000[0x550];
} EffectSpark;
_Static_assert(sizeof(EffectSpark) == 0x550, "EffectSpark size");

typedef struct {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 timer;
    /* 0x08 */ Vec3f p1;
    /* 0x14 */ Vec3f p2;
    /* 0x20 */ u32 flags;
} EffectBlureElement;
_Static_assert(sizeof(EffectBlureElement) == 0x24, "EffectBlureElement size");

typedef struct EffectBlure {
    /* 0x000 */ EffectBlureElement elements[16];
    /* 0x240 */ char unk_240[0x08];
    /* 0x248 */ u16 flags;
    /* 0x24A */ char unk_24A[0x04];
    /* 0x24E */ Color_RGBA8 p1StartColor;
    /* 0x252 */ Color_RGBA8 p2StartColor;
    /* 0x256 */ Color_RGBA8 p1EndColor;
    /* 0x25A */ Color_RGBA8 p2EndColor;
    /* 0x25E */ u8 numElements;
    /* 0x25F */ u8 elemDuration;
    /* 0x260 */ u8 unkFlag;
    /* 0x261 */ u8 drawMode;
    /* 0x262 */ char unk_262[0x0A];
    /* 0x26C */ u32 unk_pointer_26C;
    /* 0x270 */ u32 unk_pointer_270;
    /* 0x274 */ char unk_274[0x0E];
    /* 0x282 */ u8 unkDrawMode1;
    /* 0x283 */ u8 unkDrawMode2;
    /* 0x284 */ char unk_284[0x4];
} EffectBlure;
_Static_assert(sizeof(EffectBlure) == 0x288, "EffectBlure size");

typedef struct EffectShieldParticle {
    /* 0x000 */ char unk_000[0x1DC];
} EffectShieldParticle;
_Static_assert(sizeof(EffectShieldParticle) == 0x1DC, "EffectShieldParticle size");

typedef struct EffectContext {
    /* 0x0000 */ struct GlobalContext* play;
    struct {
        EffectStatus status;
        EffectSpark effect;
    } /* 0x0004 */ sparks[SPARK_COUNT];
    struct {
        EffectStatus status;
        EffectBlure effect;
    } /* 0x7FE4 */ blures[BLURE_COUNT];
    struct {
        EffectStatus status;
        EffectShieldParticle effect;
    } /* 0xBF90 */ shieldParticles[SHIELD_PARTICLE_COUNT];
} EffectContext;
_Static_assert(sizeof(EffectContext) == 0xD250, "EffectContext size");

#define gEffectContext (*(EffectContext*)GAME_ADDR(0x58B2E0))

#define EffectBlure_Update ((void (*)(EffectBlure*))GAME_ADDR(0x227000))

typedef void (*Effect_Delete_proc)(struct GlobalContext* globalCtx, s32 index);
#define Effect_Delete ((Effect_Delete_proc)GAME_ADDR(0x34F0F4))

/* Effect Soft Sprites */

typedef enum EffectSsType {
    /* 0x00 */ EFFECT_SS_DUST,
    /* 0x01 */ EFFECT_SS_KIRAKIRA,
    /* 0x02 */ EFFECT_SS_BOMB,
    /* 0x03 */ EFFECT_SS_BOMB2,
    /* 0x04 */ EFFECT_SS_BLAST,
    /* 0x05 */ EFFECT_SS_G_SPK,
    /* 0x06 */ EFFECT_SS_D_FIRE,
    /* 0x07 */ EFFECT_SS_BUBBLE,
    /* 0x08 */ EFFECT_SS_UNSET,
    /* 0x09 */ EFFECT_SS_G_RIPPLE,
    /* 0x0A */ EFFECT_SS_G_SPLASH,
    /* 0x0B */ EFFECT_SS_G_MAGMA,
    /* 0x0C */ EFFECT_SS_G_FIRE,
    /* 0x0D */ EFFECT_SS_LIGHTNING,
    /* 0x0E */ EFFECT_SS_DT_BUBBLE,
    /* 0x0F */ EFFECT_SS_HAHEN,
    /* 0x10 */ EFFECT_SS_STICK,
    /* 0x11 */ EFFECT_SS_SIBUKI,
    /* 0x12 */ EFFECT_SS_SIBUKI2,
    /* 0x13 */ EFFECT_SS_G_MAGMA2,
    /* 0x14 */ EFFECT_SS_STONE1,
    /* 0x15 */ EFFECT_SS_HITMARK,
    /* 0x16 */ EFFECT_SS_FHG_FLASH,
    /* 0x17 */ EFFECT_SS_K_FIRE,
    /* 0x18 */ EFFECT_SS_SOLDER_SRCH_BALL,
    /* 0x19 */ EFFECT_SS_KAKERA,
    /* 0x1A */ EFFECT_SS_ICE_PIECE,
    /* 0x1B */ EFFECT_SS_EN_ICE,
    /* 0x1C */ EFFECT_SS_FIRE_TAIL,
    /* 0x1D */ EFFECT_SS_EN_FIRE,
    /* 0x1E */ EFFECT_SS_EXTRA,
    /* 0x1F */ EFFECT_SS_FCIRCLE,
    /* 0x20 */ EFFECT_SS_DEAD_DB,
    /* 0x21 */ EFFECT_SS_DEAD_DD,
    /* 0x22 */ EFFECT_SS_DEAD_DS,
    /* 0x23 */ EFFECT_SS_DEAD_SOUND,
    /* 0x24 */ EFFECT_SS_ICE_SMOKE,
    /* 0x25 */ EFFECT_SS_TYPE_MAX,
} EffectSsType;

typedef struct EffectSs {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f velocity;
    /* 0x18 */ Vec3f accel;
    /* 0x24 */ void* update;
    /* 0x28 */ void* draw;
    /* 0x2C */ Vec3f vec;           // usage specific per effect
    /* 0x38 */ void* gfx;           // mostly used for display lists, sometimes textures
    /* 0x3C */ struct Actor* actor; // interfacing actor, usually the actor that spawned the effect
    /* 0x40 */ char unk_40[0x04];
    /* 0x44 */ s16 regs[13]; // specific per effect
    /* 0x5E */ u16 flags;
    /* 0x60 */ s16 life;    // -1 means this entry is free
    /* 0x62 */ u8 priority; // Lower value means higher priority
    /* 0x63 */ u8 type;
    /* 0x64 */ char unk_64[0x24];
} EffectSs;
_Static_assert(sizeof(EffectSs) == 0x88, "EffectSs size");

typedef struct EffectSsInfo {
    /* 0x00 */ EffectSs* table;
    /* 0x04 */ s32 tableSize;
    // ...
} EffectSsInfo;

#define gEffectSsInfo (*(EffectSsInfo*)GAME_ADDR(0x598530))

typedef void (*EffectSs_Delete_proc)(EffectSs* effectSs);
#define EffectSs_Delete ((EffectSs_Delete_proc)GAME_ADDR(0x2D6A50))

#endif //_Z3DEFFECT_H_
