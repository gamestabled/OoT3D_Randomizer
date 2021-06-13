#ifndef _ENTRANCE_H_
#define _ENTRANCE_H_

#include "z3D/z3D.h"

typedef struct {
    s16 index;
    s16 override;
    s16 blueWarp;
} EntranceOverride;

void Entrance_Init(void);

#endif //_ENTRANCE_H_
