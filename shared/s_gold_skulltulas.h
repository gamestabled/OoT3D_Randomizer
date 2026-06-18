#pragma once
#include "s_types.h"

typedef enum GsAgeCondition {
    GS_AGE_ADULT,
    GS_AGE_CHILD,
    GS_AGE_BOTH,
} GsAgeCondition;

typedef enum GsTimeCondition {
    GS_TIME_ALWAYS,
    GS_TIME_NIGHT,
} GsTimeCondition;

typedef struct GsLocOverride {
    u8 arrayIndex;
    u8 bitFlag;
    s16 scene;
    s8 room;
    GsAgeCondition ageCondition;
    GsTimeCondition timeCondition;
    PosRot posRot;
} GsLocOverride;
