#ifndef _POE_H_
#define _POE_H_

#include "z3D/z3D.h"

/*-------------------------------
|             EnPoh             |
-------------------------------*/

typedef struct EnPoh {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x6E8];
    /* 0x910 */ SkeletonAnimationModel* saModel_1;
    /* 0x914 */ SkeletonAnimationModel* saModel_2;
    /* 0x918 */ char unk_918[0x007];
    /* 0x91F */ u8 infoIdx;
    /* 0x920 */ char unk_920[0x02C];
    /* 0x94C */ SkeletonAnimationModel* saModel_94C;
    /* 0x950 */ SkeletonAnimationModel* saModel_950;
    /* 0x954 */ u32 composerLanternCmbIndex;
    /* 0x958 */ char unk_958[0x114];
} EnPoh;
_Static_assert(sizeof(EnPoh) == 0xA6C, "EnPoh size");

void EnPoh_rInit(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_rUpdate(Actor* thisx, GlobalContext* globalCtx);

void EnPoh_ReinitModels(EnPoh* this);

/*-------------------------------
|           EnPoField           |
-------------------------------*/

struct EnPoField;

typedef void (*EnPoFieldActionFunc)(struct EnPoField* this, GlobalContext* globalCtx);

typedef enum EnPoFieldSize {
    EN_PO_FIELD_SMALL,
    EN_PO_FIELD_BIG
} EnPoFieldSize;

typedef struct EnPoField {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x680];
    /* 0x8A8 */ SkeletonAnimationModel* saModel_1;
    /* 0x8AC */ SkeletonAnimationModel* saModel_2;
    /* 0x8B0 */ char unk_8B0[0x044];
    /* 0x8F4 */ EnPoFieldActionFunc actionFunc;
    /* 0x8F8 */ char unk_8F8[0x0F8];
} EnPoField;
_Static_assert(sizeof(EnPoField) == 0x9F0, "EnPoField size");

void EnPoField_ReinitModels(EnPoField* this);

/*-------------------------------
|           EnPoSister          |
-------------------------------*/

typedef struct EnPoSisters {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x750];
    /* 0x978 */ SkeletonAnimationModel* saModel_death;
    /* 0x97C */ char unk_97C[0x17C];
} EnPoSisters;
_Static_assert(sizeof(EnPoSisters) == 0xAF8, "EnPoSisters size");

void EnPoSisters_ReinitModels(EnPoSisters* this);

#endif //_POE_H_
