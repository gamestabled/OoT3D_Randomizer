#include "multiplayer_ghosts.h"
#include "3ds/svc.h"
#include "common.h"

typedef struct {
    bool inUse;
    u64 lastTick;
    u16 networkID;
    GhostData ghostData;
} LinkGhost;

static LinkGhost ghosts[16];

#define INACTIVE_TIME_LIMIT (TICKS_PER_SEC * 3)

void Multiplayer_Ghosts_Tick(void) {
    u64 currentTick = svcGetSystemTick();
    for (size_t i = 0; i < ARRAY_SIZE(ghosts); i++) {
        LinkGhost* ghost = &ghosts[i];
        if (ghost->inUse && currentTick - ghost->lastTick > INACTIVE_TIME_LIMIT) {
            ghost->inUse = false;
        }
    }
}

void Multiplayer_Ghosts_UpdateGhost(u16 networkID, GhostData* ghostData) {
    LinkGhost* ghostX = NULL;
    // Find existing ghost
    for (size_t i = 0; i < ARRAY_SIZE(ghosts); i++) {
        LinkGhost* ghost = &ghosts[i];
        if (ghost->inUse && ghost->networkID == networkID) {
            ghostX = ghost;
            break;
        }
    }
    // Assign new ghost
    if (ghostX == NULL) {
        for (size_t i = 0; i < ARRAY_SIZE(ghosts); i++) {
            LinkGhost* ghost = &ghosts[i];
            if (!ghost->inUse) {
                ghost->inUse     = true;
                ghost->networkID = networkID;
                ghostX           = ghost;
                break;
            }
        }
    }
    // Failsafe in case all spots are taken
    if (ghostX == NULL) {
        return;
    }
    // Set vars
    ghostX->lastTick = svcGetSystemTick();
    if (ghostData != NULL) {
        ghostX->ghostData.currentScene = ghostData->currentScene;
        ghostX->ghostData.age          = ghostData->age;
        ghostX->ghostData.position     = ghostData->position;
        // Temporary offset for effect
        ghostX->ghostData.position.y += (ghostData->age == 0 ? 50 : 35);
    }
}

GhostData* Multiplayer_Ghosts_GetGhostData(u16 networkID) {
    for (size_t i = 0; i < ARRAY_SIZE(ghosts); i++) {
        LinkGhost* ghost = &ghosts[i];
        if (ghost->inUse && ghost->networkID == networkID) {
            return &ghost->ghostData;
        }
    }
    return NULL;
}

void Multiplayer_Ghosts_DrawAll(void) {
    for (size_t i = 0; i < ARRAY_SIZE(ghosts); i++) {
        LinkGhost* ghost = &ghosts[i];
        if (ghost->inUse && ghost->ghostData.currentScene == gGlobalContext->sceneNum) {
            // Temporary effect
            static Vec3f vecEmpty;
            static f32 colorR[] = { 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.5 };
            static f32 colorG[] = { 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.5, 0.0 };
            static f32 colorB[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0 };

            s16 envR = 100 * colorR[(ghost->networkID - 1) % ARRAY_SIZE(colorR)];
            s16 envG = 100 * colorG[(ghost->networkID - 1) % ARRAY_SIZE(colorG)];
            s16 envB = 100 * colorB[(ghost->networkID - 1) % ARRAY_SIZE(colorB)];

            EffectSsDeadDb_Spawn(gGlobalContext, &ghost->ghostData.position, &vecEmpty, &vecEmpty,
                                 ghost->ghostData.age == 0 ? 100 : 70, -1, 80, 80, 80, 0xFF, envR, envG, envB, 1, 8, 0);
        }
    }
}
