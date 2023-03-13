#include "z3D/z3D.h"
#include "common.h"
#include "input.h"

s16 pitch = 0, yaw = 0;

u8 Camera_FreeCamEnabled(Camera* camera) {
    static u8 freeCamEnabled = 0;

    if (!freeCamEnabled) {
        yaw   = camera->inputDir.x;
        pitch = camera->inputDir.y;
    }

    if (rInputCtx.cStick.dx > 48 || rInputCtx.cStick.dx < -48 || rInputCtx.cStick.dy > 48 || rInputCtx.cStick.dy < -48) {
        freeCamEnabled = 1;
    }

    // Titlescreen or no player or targeting or first person or cutscene or crawlspace or special camera state
    if (!IsInGame() || !camera->player || camera->player->stateFlags1 & 0x20138010 || camera->player->stateFlags2 & 0x00040000 || camera->status != 7) {
        freeCamEnabled = 0;
    }

    // TODO: Prevent free cam in houses/market/probably others

    return freeCamEnabled;
}

f32 fastSin(u16 angle) {
    if (angle < 0x2000)
        return angle * 0.0000863167f;
    if (angle <= 0x4000)
        return angle * 0.0000357536f + 0.414214f;
    if (angle < 0x8000)
        return fastSin(0x8000 - angle);
    return -fastSin(angle - 0x8000);
}

s16 Clamp(f32 val) {
    if (val >= 0x3000)
        return 0x3000;
    if (val <= -0x3000)
        return -0x3000;
    return (s16)val;
}

void Camera_FreeCamUpdate(Vec3s* out, Camera* camera) {
    // TODO: Handle HUD, distance to player, collision, roll traps, dizzy trap
    if (camera->player != (Player*)0x0) {
        camera->globalCtx->view.at = camera->globalCtx->view.eye = camera->at = camera->eye = camera->player->actor.world.pos;
        camera->globalCtx->view.at.y = camera->globalCtx->view.eye.y = camera->at.y = camera->eye.y +=
            ((camera->player->stateFlags1 & (1 << 23)) ? 32 : 0) + ((gSaveContext.linkAge) ? 44 : 68);

        if (rInputCtx.cStick.dx > 48 || rInputCtx.cStick.dx < -48 || rInputCtx.cStick.dy > 48 || rInputCtx.cStick.dy < -48) {
            pitch -= rInputCtx.cStick.dx * 0x0008;
            yaw    = Clamp(yaw + rInputCtx.cStick.dy * 0x0008);
        }

        camera->globalCtx->view.eye.x = camera->eye.x -= 150 * fastSin(pitch)          * fastSin(yaw + 0x4000);
        camera->globalCtx->view.eye.y = camera->eye.y -= 150                           * fastSin(yaw);
        camera->globalCtx->view.eye.z = camera->eye.z -= 150 * fastSin(pitch + 0x4000) * fastSin(yaw + 0x4000);

        camera->globalCtx->view.up.x = 0;
        camera->globalCtx->view.up.y = 1;
        camera->globalCtx->view.up.z = 0;

        out->x = camera->inputDir.x = yaw;
        out->y = camera->inputDir.y = pitch;
        out->z = camera->inputDir.z = 0;
    }
    return;
}
