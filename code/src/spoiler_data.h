#ifndef _SPOILER_DATA_H_
#define _SPOILER_DATA_H_

#include "../include/z3D/z3D.h"

#define SPOILER_SPHERES_MAX 22
#define SPOILER_ITEMS_MAX 20

// One line of text in the menu can be 50 chars max
#define SPOILER_LINE_LENGTH 50

typedef struct {
    char Location[SPOILER_LINE_LENGTH];
    char Item[SPOILER_LINE_LENGTH];
} SpoilerItemLocation;

typedef struct {
    u8 ItemCount;
    SpoilerItemLocation ItemLocations[SPOILER_ITEMS_MAX];
} Sphere;

typedef struct {
    u8 SphereCount;
    Sphere Spheres[SPOILER_SPHERES_MAX];
} SpoilerData;

extern SpoilerData gSpoilerData;

#endif // _SPOILER_DATA_H_