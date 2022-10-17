#include "multiplayer_ghosts.h"
#include "3ds/svc.h"
#include "common.h"
#include "settings.h"
#include "savefile.h"

typedef struct {
    bool inUse;
    u64 lastTick;
    u16 networkID;
    GhostData ghostData;
} LinkGhost;

static LinkGhost ghosts[16];

#define INACTIVE_TIME_LIMIT (TICKS_PER_SEC * 3)

int powOf(int base, int exp){
    if(exp < 0){
        return -1;
    }
    int result = 1;
    while (exp){
        if (exp & 1){
            result *= base;
        }
        exp >>= 1;
        base *= base;
    }
    return result;
}
float sqroot(int x) {
    int i;
    float s;
    s=((x/2)+x/(x/2)) / 2;
    for(i=1;i<=4;i++) {
        s=(x+s/s)/2;
    }
    return s;
}
float dist(float x1, float y1, float x2, float y2){
    float result=sqroot(powOf((x2- x1), 2)+powOf((y2- y1), 2));
    return(result);
}

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
                ghost->inUse = true;
                ghost->networkID = networkID;
                ghostX = ghost;
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
        ghostX->ghostData.age = ghostData->age;
        ghostX->ghostData.position = ghostData->position;
        ghostX->ghostData.hideSeek = ghostData->hideSeek;
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

typedef void(*EffectSsDeadDb_Spawn_proc)(GlobalContext* globalCtx, Vec3f* position, Vec3f* velocity, Vec3f* acceleration,
    s16 scale, s16 scale_step,
    s16 prim_r, s16 prim_g, s16 prim_b, s16 prim_a,
    s16 env_r, s16 env_g, s16 env_b,
    s16 unused, s32 frame_duration, s16 play_sound);
#define EffectSsDeadDb_Spawn_addr 0x3642F4
#define EffectSsDeadDb_Spawn ((EffectSsDeadDb_Spawn_proc)EffectSsDeadDb_Spawn_addr)

void Multiplayer_Ghosts_DrawAll(void) {
    for (size_t i = 0; i < ARRAY_SIZE(ghosts); i++) {
        LinkGhost* ghost = &ghosts[i];
        if (ghost->inUse && ghost->ghostData.currentScene == gGlobalContext->sceneNum) {
            // Temporary effect
            static Vec3f vecEmpty;
            static f32 colorR[] = { 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.5 };
            static f32 colorG[] = { 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.5, 0.0 };
            static f32 colorB[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0 };

            int GhostPosX=ghost->ghostData.position.x;
            int GhostPosY=ghost->ghostData.position.y - (ghost->ghostData.age==0?50:35);
            int GhostPosZ=ghost->ghostData.position.z;
            int ghostHeight=ghost->ghostData.age == 0 ? 60 : 48;

            int PlayerPosX=PLAYER->actor.world.pos.x;
            int PlayerPosY=PLAYER->actor.world.pos.y;
            int PlayerPosZ=PLAYER->actor.world.pos.z;
            int playerHeight=gSaveContext.linkAge == 0 ? 60 : 48;
            
            s16 envR = 100 * colorR[(ghost->networkID - 1) % ARRAY_SIZE(colorR)];
            s16 envG = 100 * colorG[(ghost->networkID - 1) % ARRAY_SIZE(colorG)];
            s16 envB = 100 * colorB[(ghost->networkID - 1) % ARRAY_SIZE(colorB)];
            if(dist(PlayerPosX,PlayerPosZ, GhostPosX,GhostPosZ)<24&&PlayerPosY+playerHeight>GhostPosY-5 && PlayerPosY<GhostPosY+ghostHeight+5 && gExtSaveData.option_HideSeek==1 && ghost->ghostData.hideSeek==2){
                gExtSaveData.option_HideSeek=2;
                gSaveContext.health = 0;
            }

            EffectSsDeadDb_Spawn(gGlobalContext, &ghost->ghostData.position, &vecEmpty, &vecEmpty,
                ghost->ghostData.age == 0 ? 100 : 70, -1,
                80, 80, 80, 0xFF,
                envR, envG, envB,
                1, 8, 0);
        }
    }
}
