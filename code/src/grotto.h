#ifndef _GROTTO_H_
#define _GROTTO_H_

#include "z3D/z3Dvec.h"

#define NUM_GROTTOS 33
#define NOT_GROTTO 0
#define GROTTO_LOAD 1
#define GROTTO_RETURN 2

#define GET_REAL_RETURN_INDEX 1

typedef struct {
    s16 entranceIndex;
    s8 content;
    s8 scene;
} GrottoLoadInfo;

typedef struct {
    s16 entranceIndex;
    s8 room;
    s16 angle;
    Vec3f pos;
} GrottoReturnInfo;

void Grotto_InitExitAndLoadLists(void);
void Grotto_SetExitOverride(s16 originalIndex, s16 overrideIndex);
void Grotto_SetLoadOverride(s16 originalIndex, s16 overrideIndex);
s16  Grotto_CheckSpecialEntrance(s16 nextEntranceIndex, u32 realIndexOnGrottoReturn);
void Grotto_ForceGrottoReturnOnSpecialEntrance(void);

#endif //_GROTTO_H_
