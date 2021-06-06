#ifndef _SPOILER_DATA_H_
#define _SPOILER_DATA_H_

#include "../include/z3D/z3D.h"

#define SPOILER_SPHERES_MAX                 32
#define SPOILER_SPHERE_ITEM_LOCATIONS_MAX   40
#define SPOILER_ITEMS_MAX                   256
#define SPOILER_STRING_DATA_SIZE            8192

typedef struct {
    u16 LocationOffset;
    u16 ItemOffset;
} SpoilerItemLocation;

typedef struct {
    u8 ItemCount;
    u8 ItemLocations[SPOILER_SPHERE_ITEM_LOCATIONS_MAX];
} Sphere;

typedef struct {
    u8 SphereCount;
    Sphere Spheres[SPOILER_SPHERES_MAX];
    SpoilerItemLocation ItemLocations[SPOILER_ITEMS_MAX];
    char StringData[SPOILER_STRING_DATA_SIZE];
} SpoilerData;

extern SpoilerData gSpoilerData;

char *SpoilerData_GetItemLocationString(u8 itemIndex);
char *SpoilerData_GetItemNameString(u8 itemIndex);

#endif // _SPOILER_DATA_H_