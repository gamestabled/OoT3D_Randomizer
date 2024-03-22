#include <string.h>

#include "3ds/svc.h"
#include "multiplayer_ghosts.h"
#include "link_puppet.h"
#include "common.h"

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

void Multiplayer_Ghosts_UpdateGhostData(u16 networkID, GhostData* ghostData) {
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
        ghostX->ghostData = *ghostData;
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

void Multiplayer_Ghosts_SpawnPuppets(void) {
    for (size_t i = 0; i < ARRAY_SIZE(ghosts); i++) {
        LinkGhost* ghost = &ghosts[i];

        if (ghost->inUse && ghost->ghostData.currentScene == gGlobalContext->sceneNum) {
            bool alreadyExists = false;
            // If puppet already is spawned, skip
            Actor* firstActor = gGlobalContext->actorCtx.actorList[EnLinkPuppet_InitVars.type].first;
            for (Actor* actor = firstActor; actor != NULL; actor = actor->next) {
                if (actor->id != EnLinkPuppet_InitVars.id) {
                    continue;
                }
                EnLinkPuppet* link_puppet = (EnLinkPuppet*)actor;
                if (link_puppet->base.params == ghost->networkID) {
                    alreadyExists = true;
                    break;
                }
                return;
            }
            if (alreadyExists) {
                continue;
            }
            // Otherwise, spawn it
            EnLinkPuppet_InitVars.objectId = gSaveContext.linkAge == 0 ? 20 : 21;
            EnLinkPuppet* puppet           = (EnLinkPuppet*)Actor_Spawn(
                          &gGlobalContext->actorCtx, gGlobalContext, EnLinkPuppet_InitVars.id,                   //
                          ghost->ghostData.position.x, ghost->ghostData.position.y, ghost->ghostData.position.z, //
                          0, 0, 0, ghost->networkID);
            if (puppet == NULL) {
                continue;
            }
            puppet->ghostPtr = ghost;
        }
    }
}
