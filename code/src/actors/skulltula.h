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
    Actor base;
    SkelAnime anime;
    char unk_228[1144];
    void* action_fn;
    char collider[32];
    char jnt_sph_element[80];
    char unk_714[46];
    s16 unk_word1;
    char unk_744[6];
    s16 unk_word2;
    s16 deathTimer_maybe;
    char unk_74E[106];
    f32 unk_float1;
} EnSw;

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
