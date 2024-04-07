#ifndef _MULTIPLAYER_GHOSTS_H_
#define _MULTIPLAYER_GHOSTS_H_

#include "3ds/types.h"
#include "z3D/z3D.h"

#define LINK_LIMB_COUNT 25

// Filler struct to match allocated size in SkelAnime_InitLink
typedef struct {
    u8 data[0x34];
} JointData;

typedef struct {
    s16 currentScene;
    s32 age;
    Vec3f position;
    Vec3s rotation;
    u32 meshGroups1;
    u32 meshGroups2;
    s8 currentTunic;
    JointData jointTable[LINK_LIMB_COUNT]; // ALWAYS KEEP LAST
} GhostData;

typedef struct {
    bool inUse;
    u64 lastTick;
    u16 networkID;
    GhostData ghostData;
} LinkGhost;

void Multiplayer_Ghosts_Tick(void);
void Multiplayer_Ghosts_UpdateGhostData(u16 networkID, GhostData* ghostData);
GhostData* Multiplayer_Ghosts_GetGhostData(u16 networkID);
// Updates the data of the existing puppet actors, or spawns new ones in the scene
void Multiplayer_Ghosts_SpawnPuppets(void);

#endif //_MULTIPLAYER_GHOSTS_H_
