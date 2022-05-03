#include "settings.h"
#include "multiplayer.h"

void SendDroppedBottleContents(s16 actorId, f32 posX, f32 posY, f32 posZ) {
    if (gSettingsContext.mp_Enabled == OFF || gSettingsContext.mp_SharedProgress == OFF) {
        return;
    }
    //             Bugs               Fish             Blue Fire
    if (actorId != 0x20 && actorId != 0x21 && actorId != 0xF0) {
        return;
    }
    PosRot posRot = { { posX, posY, posZ }, { 0x4000, PLAYER->actor.shape.rot.y, 0 } };
    s16 params = 0;
    if (actorId == 0x20) {
        params = 2;
    }
    Multiplayer_Send_ActorSpawn(actorId, posRot, params);
}
