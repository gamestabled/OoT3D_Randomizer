#ifndef _SPOILER_DATA_H_
#define _SPOILER_DATA_H_

#include "../include/z3D/z3D.h"

#define SPOILER_SPHERES_MAX                 40
#define SPOILER_SPHERE_ITEM_LOCATIONS_MAX   40
#define SPOILER_ITEMS_MAX                   512
#define SPOILER_STRING_DATA_SIZE            16384

typedef struct {
    u16 LocationOffset;
    u16 ItemOffset;
} SpoilerItemLocation;

typedef struct {
    u8 ItemCount;
    u16 ItemLocations[SPOILER_SPHERE_ITEM_LOCATIONS_MAX];
} SpoilerSphere;

typedef struct {
    u8 SphereCount;
    u16 ItemLocationsCount;
    SpoilerSphere Spheres[SPOILER_SPHERES_MAX];
    SpoilerItemLocation ItemLocations[SPOILER_ITEMS_MAX];
    char StringData[SPOILER_STRING_DATA_SIZE];
} SpoilerData;

extern SpoilerData gSpoilerData;

char *SpoilerData_GetItemLocationString(u16 itemIndex);
char *SpoilerData_GetItemNameString(u16 itemIndex);

#endif // _SPOILER_DATA_H_