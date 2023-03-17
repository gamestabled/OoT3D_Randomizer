#include "z3D/z3D.h"
#include "common.h"
#include "input.h"
#include "icetrap.h"

#define GyroDrawHUDIcon *(u8*)0x4FC648
s16 pitch = 0, yaw = 0;
f32 dist = 0;

f32 sins(u16 angle) {
    // Taylor expansion up to x^7. Use symmetries for larger angles.
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
    f32 n = (1 + x) * 0.5;

    while (n * n < x * 0.999f || n * n > x * 1.001f) {
        n = (n + x / n) * 0.5;
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

f32 lerpf(f32 a, f32 b, f32 t) {
    return a + (b - a) * t;
}

Vec3f lerpv(Vec3f a, Vec3f b, f32 t) {
    a.x += (b.x - a.x) * t;
    a.y += (b.y - a.y) * t;
    a.z += (b.z - a.z) * t;
    return a;
}

u8 Camera_FreeCamEnabled(Camera* camera) {
    static u8 freeCamEnabled = 0;

    // Keep track of these to smoothly switch to free cam
    dist  = distXYZ(camera->at, camera->eye);
    if (!freeCamEnabled) {
        pitch = camera->camDir.x;
        yaw   = camera->camDir.y;
    }

    // Deadzone of 30 units
    if (rInputCtx.cStick.dx * rInputCtx.cStick.dx + rInputCtx.cStick.dy * rInputCtx.cStick.dy > 900) {
        freeCamEnabled = 1;
    }

    // Titlescreen or no player or targeting or first person or cutscene or horse or crawlspace or special camera state/setting
    // (MK balcony, chu bowling, static, rotating, hedge maze, GF cells, shops, back alley)
    if (!IsInGame() || !camera->player || camera->player->stateFlags1 & 0x20938210 || camera->player->stateFlags2 & 0x00040000 || camera->status != 7 ||
        camera->setting == 0x14 || camera->setting == 0x15 || camera->setting == 0x19 || camera->setting == 0x1A ||
        camera->setting == 0x1B || camera->setting == 0x23 || camera->setting == 0x40 || camera->setting == 0x46) {
        freeCamEnabled = 0;
    }

    return freeCamEnabled;
}

void Camera_FreeCamUpdate(Vec3s* out, Camera* camera) {
    Camera_CheckWater(camera); // Changes skybox colour and audio when camera is underwater
    Camera_UpdateInterface(0); // Remove the black bars at the top/bottom of the screen
    GyroDrawHUDIcon = 0;       // Remove the icon in the top right indicating motion controls
    if (camera->player != (Player*)0x0) {
        Vec3f at;
        CamColChk eye;

        // Aim camera at Link's head. Aim lower when hanging from a ledge as position and model become disjointed
        at   = eye.pos    = camera->player->actor.world.pos;
        at.y = eye.pos.y += ((gSaveContext.linkAge) ? 38 : 56) * ((camera->player->stateFlags1 & 0x00002000) ? 0.5 : 1);

        // Invert controls for dizzy trap
        s8 speed = (IceTrap_ActiveCurse == ICETRAP_CURSE_DIZZY) ? -8 : 8;
        if (rInputCtx.cStick.dx * rInputCtx.cStick.dx + rInputCtx.cStick.dy * rInputCtx.cStick.dy > 900) {
            // Invert X input in mirror world, invert Y input if base game camera control is set to inverted Y
            yaw  -= rInputCtx.cStick.dx * speed * ((gSaveContext.masterQuestFlag) ? -1 : 1);
            pitch = Clamp(pitch + rInputCtx.cStick.dy * speed * ((gSaveContext.cameraControlSetting) ? -1 : 1));
        }

        // Set intended camera position
        dist = lerpf(dist, ((gSaveContext.linkAge) ? 150 : 200) - 50 * sins(pitch), 0.5);
        eye.pos.x -= dist * coss(pitch) * sins(yaw);
        eye.pos.y -= dist * sins(pitch);
        eye.pos.z -= dist * coss(pitch) * coss(yaw);
        // Move intended position in front of collision
        Camera_BGCheckInfo(camera, &at, &eye);

        // Move actual camera positions towards intended positions
        camera->globalCtx->view.at  = camera->at                    = lerpv(camera->globalCtx->view.at,  at,      0.3);
        camera->globalCtx->view.eye = camera->eye = camera->eyeNext = lerpv(camera->globalCtx->view.eye, eye.pos, 0.3);

        // Set the up vector for roll traps
        f32 cR = coss(IceTrap_CamRoll(0)), sR = sins(IceTrap_CamRoll(0)), r = distXZ(camera->at, camera->eye);
        camera->globalCtx->view.up.x = sR * (camera->at.z - camera->eye.z) / r;
        camera->globalCtx->view.up.y = cR;
        camera->globalCtx->view.up.z = sR * (camera->eye.x - camera->at.x) / r;

        // Set the direction of control stick inputs
        out->x = camera->inputDir.x = camera->camDir.x = pitch;
        out->y = camera->inputDir.y = camera->camDir.y = yaw;
        out->z = camera->inputDir.z = camera->camDir.z = 0;

        // Pretty much entirely for the alcoves in SpT, causes unmapped reads if jumping into them so wait until player is on ground
        s16 newSetting = camera->globalCtx->colCtx.stat.colHeader->camDataList[Camera_GetCamDataId(&camera->globalCtx->colCtx, camera->player->actor.floorPoly, 0x32)].setting;
        if (newSetting && !(camera->player->stateFlags1 & 0x00040000)) {
            camera->setting = newSetting;
        }
    }
    return;
}
