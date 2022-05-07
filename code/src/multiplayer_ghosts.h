#ifndef _MULTIPLAYER_GHOSTS_H_
#define _MULTIPLAYER_GHOSTS_H_

#include "3ds/types.h"
#include "z3D/z3D.h"

typedef struct {
    s16 currentScene;
    s32 age;
    Vec3f position;
    // Animation vars here
} GhostData;

void Multiplayer_Ghosts_Tick(void);
void Multiplayer_Ghosts_UpdateGhost(u16 networkID, GhostData* ghostData);
GhostData* Multiplayer_Ghosts_GetGhostData(u16 networkID);
void Multiplayer_Ghosts_DrawAll(void);

#endif //_MULTIPLAYER_GHOSTS_H_
