#ifndef _MULTIPLAYER_GHOSTS_H_
#define _MULTIPLAYER_GHOSTS_H_

#include "3ds/types.h"
#include "z3D/z3D.h"

// ASSUMED! Game crashes when copying more than this while paused.
#define LINK_JOINT_COUNT 217
// 48 for adult, 26 for child?
#define LINK_MESH_GROUP_COUNT 48

typedef struct {
    s16 currentScene;
    s32 age;
    Vec3f position;
    Vec3s rotation;
    // Animation vars here
    u32 meshGroups1;
    u32 meshGroups2;
    Vec3s jointTable[LINK_JOINT_COUNT]; // ALWAYS KEEP LAST
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
