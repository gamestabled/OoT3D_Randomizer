#ifndef _SKULLTULA_H_
#define _SKULLTULA_H_

#include "../../code/include/z3D/z3D.h"

/* Bit usage of "params" for Gold Skulltula:
 *   0-7: Bit in gsFlags
 *  8-12: Index of gsFlags
 * 13-15: Attributes or type? If any is set, the Skulltula is Gold
 */

#define GS_ARRAY_INDEX(params) ((params & 0x1F00) >> 8)
#define GS_BIT_FLAG(params) (params & 0xFF)

typedef struct {
    /* 0x000 */ Actor base;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x478];
    /* 0x6A0 */ void* action_fn;
    /* 0x6A4 */ char collider[0x20];
    /* 0x6C4 */ char jnt_sph_element[0x50];
    /* 0x714 */ char unk_714[0x2E];
    /* 0x742 */ s16 unk_word1;
    /* 0x744 */ char unk_744[0x6];
    /* 0x74A */ s16 unk_word2;
    /* 0x74C */ s16 deathTimer_maybe;
    /* 0x74E */ char unk_74E[0x6A];
    /* 0x7B8 */ f32 unk_float1;
    /* 0x7BC */ char unk_7BC[0xC];
    /* 0x7C8 */ Vec3f unk_7C8;
    /* 0x7D4 */ s16 unk_7D4;
    /* 0x7D6 */ s16 timer_7D6;
    /* 0x7D8 */ s16 targetRot;
    /* 0x7DA */ s16 unk_7DA;
    /* 0x7DC */ Vec3f targetPos;
    /* 0x7E8 */ Vec3f unk_7E8;
    /* 0x7F4 */ Vec3f unk_7F4;
    /* 0x800 */ Vec3f unk_800;
    /* 0x80C */ Vec3f unk_80C;
    /* 0x818 */ Vec3f unk_818;
    /* 0x824 */ char unk_824[0xC];
} EnSw;
_Static_assert(sizeof(EnSw) == 0x830, "EnSw size");

void EnSw_rInit(Actor* thisx, GlobalContext* globalCtx);
void EnSw_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void EnSw_Kill(EnSw* thisx, GlobalContext* globalCtx);

typedef enum {
    GS_PPT_ACTORENTRY,
    GS_PPT_ACTOR_GS,
    GS_PPT_ACTOR_CRATE,
    GS_PPT_ACTOR_TREE,
    GS_PPT_ACTOR_SOIL,
} GsParamPointerType;

u8 Gs_HasAltLoc(void* ptr, GsParamPointerType ppt, u8 adjustArrayIndex);
void Gs_SpawnAltLocs(void);

typedef enum {
    GS_AGE_ADULT,
    GS_AGE_CHILD,
    GS_AGE_BOTH,
} GsAgeCondition;

typedef enum {
    GS_TIME_ALWAYS,
    GS_TIME_NIGHT,
} GsTimeCondition;

typedef struct {
    u8 arrayIndex;
    u8 bitFlag;
    s16 scene;
    s8 room;
    GsAgeCondition ageCondition;
    GsTimeCondition timeCondition;
    PosRot posRot;
} GsLocOverride;

#endif //_SKULLTULA_H_
