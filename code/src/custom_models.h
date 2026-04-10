#ifndef _CUSTOM_MODELS_H_
#define _CUSTOM_MODELS_H_

#include "s_custom_models.h"

void CustomModel_EditLinkToCustomTunic(void* linkCMB);
void CustomModel_EditChildLinkToCustomTunic(void* linkCMB);
void CustomModel_EditTitleScreenLogo(void* titleScreenZAR);
void CustomModel_Update(void);
void CustomModels_EditItemCMB(void* ZARBuf, u16 objectId, s8 special);
void CustomModels_ApplyItemCMAB(SkeletonAnimationModel* model, u16 objectId, s8 special);
void CustomModels_UpdateMatrix(nn_math_MTX34* modelMtx, u16 objectId);

typedef enum {
    TEXANIMFRAME_ZELDAS_LULLABY,
    TEXANIMFRAME_EPONAS_SONG,
    TEXANIMFRAME_SARIAS_SONG,
    TEXANIMFRAME_SONG_STORMS,
    TEXANIMFRAME_SUNS_SONG,
    TEXANIMFRAME_SONG_TIME
} ChildSongTexAnimFrames;

typedef enum {
    TEXANIMFRAME_BOLERO,
    TEXANIMFRAME_MINUET,
    TEXANIMFRAME_NOCTURNE,
    TEXANIMFRAME_PRELUDE,
    TEXANIMFRAME_REQUIEM,
    TEXANIMFRAME_SERENADE
} AdultSongTexAnimFrames;

typedef enum {
    TEXANIMFRAME_FOREST,
    TEXANIMFRAME_FIRE,
    TEXANIMFRAME_WATER,
    TEXANIMFRAME_SHADOW,
    TEXANIMFRAME_SPIRIT,
    TEXANIMFRAME_GANON
} BossKeyTexAnimFrames;

#endif //_CUSTOM_MODELS_H_
