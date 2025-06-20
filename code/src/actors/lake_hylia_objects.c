#include "z3D/z3D.h"
#include "lake_hylia_objects.h"
#include "objects.h"

#define BgSpot06Objects_Update ((ActorFunc)GAME_ADDR(0x3833F8))

#define BgSpot06Objects_Destroy ((ActorFunc)GAME_ADDR(0x2AD1E4))

static u8 actionCounter = 0; // used to perform some actions on subsequent frames
static s8 waterMovement = 0; // to be used when implementing moving water plane
static Actor* floorSwitch;

void BgSpot06Objects_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    BgSpot06Objects_Update(thisx, globalCtx);
    if (gSaveContext.linkAge == 1)
        return; // don't do anything for child Link

    if (actionCounter == 0) {
        Object_FindEntryOrSpawn(0x3); // object containing floor switch data (and ice block data)

        s16 switchParams;
        if (gSaveContext.eventChkInf[4] & 0x0400) { // Water Temple blue warp cleared
            switchParams = 0x3E10; // Toggle-able floor switch, linked to temp_switch 0x1E (room temporary,
                                   // cleared when room unloads)
        } else {
            switchParams = 0x3E81; // Frozen rusty switch, same flag as above.
                                   // It's glitched and can't be pressed, which is perfect
        }

        // if Lake Hylia's water is lowered, set the temp_switch flag
        if (!(gSaveContext.eventChkInf[6] & 0x0200)) {
            globalCtx->actorCtx.flags.tempSwch |= (0x40 << 24);
        }

        // Spawn a floor switch
        floorSwitch = Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x12A, -896.0f, -1243.0f, 6953.0f, 0, 0, 0,
                                  switchParams, FALSE);

        // Spawn a sign
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x141, -970.0f, -1242.0f, 6954.0f, 0, 0, 0, 0x0046, FALSE);

        // Spawn a Navi check spot
        if (!(gSaveContext.eventChkInf[4] & 0x0400)) { // Water Temple blue warp not cleared
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x173, -896.0f, -1243.0f, 6953.0f, 0, 0, 0, 0x3DB3, FALSE);
        }

        actionCounter++;
        return;
    } else if (actionCounter == 1) {
        if (!(gSaveContext.eventChkInf[4] & 0x0400)) { // Water Temple blue warp not cleared
            // remove link to ice block so melting that doesn't set the flag
            floorSwitch->params = 0x3E01;
        }
        actionCounter++;
        return;
    }

    if (globalCtx->actorCtx.flags.tempSwch & (0x40 << 24)) {                   // switch pressed
        if (thisx->params == 0x0002 && gSaveContext.eventChkInf[6] & 0x0200) { // if water is raised, lower it
            waterMovement = -1;
            PlaySound(0x100025B);
            gSaveContext.eventChkInf[6] &= ~0x0200;
            // TODO: remove this warp when the water will properly move
            globalCtx->nextEntranceIndex = 0x0604;
            globalCtx->sceneLoadFlag     = 0x14;
            globalCtx->fadeOutTransition = 5;
        }
    } else {
        if (thisx->params == 0x0002 && !(gSaveContext.eventChkInf[6] & 0x0200)) {
            waterMovement = 1;
            PlaySound(0x100025B);
            gSaveContext.eventChkInf[6] |= 0x0200;
            // TODO: remove this warp when the water will properly move
            globalCtx->nextEntranceIndex = 0x0604;
            globalCtx->sceneLoadFlag     = 0x14;
            globalCtx->fadeOutTransition = 5;
        }
    }
    /*  //TODO: change shape of the water texture to cover the entire lake, then change collision context stuff to make
       the water plane move
        //this only moves the texture
        if(thisx->params==0x0002 && thisx->world.pos.y <= -1313 && thisx->world.pos.y >= -1994){
            thisx->world.pos.y += waterMovement;
        }
    */
}

void BgSpot06Objects_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    BgSpot06Objects_Destroy(thisx, globalCtx);
    actionCounter = 0;
    waterMovement = 0;
}
