#include "z3D/z3D.h"
#include "common.h"
#include "input.h"
#include "icetrap.h"

#define GyroDrawHUDIcon *(u8*)0x4FC648

f32 sins(u16 angle) {
    if (angle <= 0x4000) {
        f32 theta = angle * 0.0000958737992429, theta2 = theta * theta, result = theta;
        theta *= theta2 * 0.166666666667;
        result -= theta;
        theta *= theta2 * 0.05;
        result += theta;
        theta *= theta2 * 0.0238095238095;
        result -= theta;
        return result;
    } else if (angle <= 0x8000) {
        return sins(0x8000 - angle);
    }
    return -sins(angle - 0x8000);
}

f32 coss(u16 angle) {
    return sins(angle + 0x4000);
}

f32 sqrtf(f32 x) {
    f32 n = (1 + x) / 2;

    while (n * n < x * 0.999f || n * n > x * 1.001f) {
        n = (n + x / n) / 2;
    }

    return n;
}

f32 distXYZ(Vec3f a, Vec3f b) {
    f32 x = a.x - b.x, y = a.y - b.y, z = a.z - b.z;
    return sqrtf(x * x + y * y + z * z);
}

f32 distXZ(Vec3f a, Vec3f b) {
    f32 x = a.x - b.x, z = a.z - b.z;
    return sqrtf(x * x + z * z);
}

s16 Clamp(f32 val) {
    if (val >= 0x3000)
        return 0x3000;
    if (val <= -0x3000)
        return -0x3000;
    return (s16)val;
}

s16 pitch = 0, yaw = 0;
f32 dist = 0;

u8 Camera_FreeCamEnabled(Camera* camera) {
    static u8 freeCamEnabled = 0;

    if (!freeCamEnabled) {
        pitch = camera->inputDir.x;
        yaw   = camera->inputDir.y;
        dist  = distXYZ(camera->at, camera->eye);
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

f32 lerpf(f32 a, f32 b, f32 t) {
    return a + (b - a) * t;
}

Vec3f lerpv(Vec3f a, Vec3f b, f32 t) {
    a.x += (b.x - a.x) * t;
    a.y += (b.y - a.y) * t;
    a.z += (b.z - a.z) * t;
    return a;
}

void Camera_FreeCamUpdate(Vec3s* out, Camera* camera) {
    // TODO: Collision
    Camera_CheckWater(camera);
    Camera_UpdateInterface(0);
    GyroDrawHUDIcon = 0;
    if (camera->player != (Player*)0x0) {
        Vec3f at, eye;
        at   = eye    = camera->player->actor.world.pos;
        at.y = eye.y += (gSaveContext.linkAge) ? 38 : 56;

        s8 speed = (IceTrap_ActiveCurse == ICETRAP_CURSE_DIZZY) ? -8 : 8;
        if (rInputCtx.cStick.dx > 48 || rInputCtx.cStick.dx < -48 || rInputCtx.cStick.dy > 48 || rInputCtx.cStick.dy < -48) {
            yaw  -= rInputCtx.cStick.dx * speed * ((gSaveContext.masterQuestFlag) ? -1 : 1);
            pitch = Clamp(pitch + rInputCtx.cStick.dy * speed * ((gSaveContext.cameraControlSetting) ? -1 : 1));
        }

        dist = lerpf(dist, (gSaveContext.linkAge) ? 150 : 200, 0.1);

        eye.x -= dist * coss(pitch) * sins(yaw);
        eye.y -= dist * sins(pitch);
        eye.z -= dist * coss(pitch) * coss(yaw);

        camera->globalCtx->view.at  = camera->at  = lerpv(camera->globalCtx->view.at,  at,  0.3);
        camera->globalCtx->view.eye = camera->eye = lerpv(camera->globalCtx->view.eye, eye, 0.3);

        f32 cR = coss(IceTrap_CamRoll(0)), sR = sins(IceTrap_CamRoll(0)), r = distXZ(camera->at, camera->eye);
        camera->globalCtx->view.up.x = sR * (camera->at.z - camera->eye.z) / r;
        camera->globalCtx->view.up.y = cR;
        camera->globalCtx->view.up.z = sR * (camera->eye.x - camera->at.x) / r;

        out->x = camera->inputDir.x = pitch;
        out->y = camera->inputDir.y = yaw;
        out->z = camera->inputDir.z = 0;
    }
    return;
}
