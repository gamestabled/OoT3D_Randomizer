#include "z3D/z3D.h"
#include "common.h"
#include "input.h"
#include "icetrap.h"
#include "savefile.h"
#include "settings.h"

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

// Original function got inlined so recreated with help from decomp
#define CAM_DEG_TO_BINANG(degrees) (s16)(s32)((degrees)*182.04167 + 0.5)
void Camera_UpdateDistortion(Camera* camera) {
    static u16 screenPlanePhase = 0;
    f32 screenPlanePhaseStep;
    f32 xScale;
    f32 yScale;
    f32 speed;
    f32 speedFactor;
    f32 scaleFactor;

    if (camera->distortionFlags) {
        if (camera->distortionFlags & 4) {
            // DISTORTION_UNDERWATER_MEDIUM
            screenPlanePhaseStep = 170;
            xScale               = -0.01;
            yScale               = 0.01;
            speed                = 0.6;
            scaleFactor          = camera->waterDistortionTimer / 60.0;
            speedFactor          = 1;
        } else if (camera->distortionFlags & 8) {
            // DISTORTION_UNDERWATER_STRONG
            screenPlanePhaseStep = -90;
            xScale               = -0.22;
            yScale               = 0.12;
            speed                = 0.1;
            scaleFactor          = camera->waterDistortionTimer / 80.0;
            speedFactor          = 1;
        } else if (camera->distortionFlags & 2) {
            // DISTORTION_UNDERWATER_WEAK
            screenPlanePhaseStep = -18.5;
            xScale               = 0.09;
            yScale               = 0.09;
            speed                = 0.08;
            scaleFactor          = camera->waterYPos - camera->eye.y;
            scaleFactor          = ((scaleFactor > 150) ? 1 : scaleFactor / 150) * 0.45 + camera->speedRatio * 0.45;
            speedFactor          = scaleFactor;
        } else if (camera->distortionFlags & 1) {
            // DISTORTION_HOT_ROOM
            screenPlanePhaseStep = 150;
            xScale               = -0.01;
            yScale               = 0.01;
            speed                = 0.6;
            scaleFactor          = 1;
            speedFactor          = 1;
        } else {
            // DISTORTION_UNDERWATER_FISHING
            return;
        }

        screenPlanePhase += CAM_DEG_TO_BINANG(screenPlanePhaseStep * 2 / 3.0);
        speedFactor *= 2 / 3.0;

        camera->globalCtx->view.distortionScale.x = xScale * scaleFactor * sins(screenPlanePhase) + 1;
        camera->globalCtx->view.distortionScale.y = yScale * scaleFactor * coss(screenPlanePhase) + 1;
        camera->globalCtx->view.distortionSpeed   = speed * speedFactor;

        camera->stateFlags |= 0x0040;
    } else if (camera->stateFlags & 0x0040) {
        camera->globalCtx->view.distortionScale.x = 1;
        camera->globalCtx->view.distortionScale.y = 1;
        camera->globalCtx->view.distortionSpeed   = 1;
        camera->stateFlags &= ~0x0040;
    }
}

s32 Camera_UpdateHotRoom(Camera* camera) {
    camera->distortionFlags &= 0xFFFE;
    // Parts of RoomContext, bool value seems new to 3D
    if (camera->globalCtx->unk_4C31[1] == 3 || camera->globalCtx->unk_4C31[6]) {
        camera->distortionFlags |= 1;
    }
    return 1;
}

u8 Camera_FreeCamEnabled(Camera* camera) {
    static u8 freeCamEnabled = 0;

    if (!gSettingsContext.freeCamera) {
        return 0;
    }

    // Keep track of these to smoothly switch to free cam
    dist = distXYZ(camera->at, camera->eye);
    if (!freeCamEnabled) {
        pitch = camera->camDir.x;
        yaw   = camera->camDir.y;
    }

    // Deadzone of 30 units
    if (rInputCtx.cStick.dx * rInputCtx.cStick.dx + rInputCtx.cStick.dy * rInputCtx.cStick.dy > 900) {
        freeCamEnabled = 1;
    }

    // Titlescreen or cutscene or no player or targeting or first person or cutscene or horse or crawlspace or special
    // camera state/setting (MK balcony, chu bowling, static, rotating, hedge maze, GF cells, shops, back alley)
    if (!IsInGame() || camera != &camera->globalCtx->mainCamera || !camera->player ||
        camera->player->stateFlags1 & 0x20938230 || camera->player->stateFlags2 & 0x00040000 || camera->status != 7 ||
        camera->setting == 0x14 || camera->setting == 0x15 || camera->setting == 0x19 || camera->setting == 0x1A ||
        camera->setting == 0x1B || camera->setting == 0x23 || camera->setting == 0x40 || camera->setting == 0x46) {
        freeCamEnabled = 0;
    }

    return freeCamEnabled;
}

void Camera_FreeCamUpdate(Vec3s* out, Camera* camera) {
    Camera_CheckWater(camera);       // Changes skybox colour and audio when camera is underwater
    Camera_UpdateHotRoom(camera);    // Check if in a hot room (mainly for DC load planes)
    Camera_UpdateDistortion(camera); // Handle heat/water screen distortions
    Camera_UpdateInterface(0);       // Remove the black bars at the top/bottom of the screen
    GyroDrawHUDIcon = 0;             // Remove the icon in the top right indicating motion controls
    if (camera->player) {
        Vec3f at;
        CamColChk eye;

        // Fixes some weird camera behaviour when leaving free cam out of bounds
        // Causes some issues with pulling objects so don't run while in bounds
        if (!camera->player->actor.floorPoly) {
            camera->animState     = 1;
            camera->behaviorFlags = 0;
        }

        // Aim camera at Link's head. Aim lower when hanging from a ledge as position and model become disjointed
        camera->playerPosRot = camera->player->actor.world;
        at = eye.pos = camera->playerPosRot.pos;
        at.y = eye.pos.y += ((gSaveContext.linkAge) ? 38 : 50) * ((camera->player->stateFlags1 & 0x00002000) ? 0.5 : 1);

        // Invert controls for dizzy trap
        s8 speed = (IceTrap_ActiveCurse == ICETRAP_CURSE_DIZZY) ? -8 : 8;
        if (rInputCtx.cStick.dx * rInputCtx.cStick.dx + rInputCtx.cStick.dy * rInputCtx.cStick.dy > 900) {
            // Invert X input in mirror world and both axes depending on settings
            yaw -= rInputCtx.cStick.dx * speed *
                   ((gSaveContext.masterQuestFlag ^ (gExtSaveData.option_FreeCamControl >> 1)) ? -1 : 1);
            pitch = Clamp(pitch + rInputCtx.cStick.dy * speed * ((gExtSaveData.option_FreeCamControl & 1) ? -1 : 1));
        }

        // Set intended camera position
        dist = lerpf(dist, ((gSaveContext.linkAge) ? 150 : 200) - 50 * sins(pitch), 0.5);
        eye.pos.x -= dist * coss(pitch) * sins(yaw);
        eye.pos.y -= dist * sins(pitch);
        eye.pos.z -= dist * coss(pitch) * coss(yaw);
        // Move intended position in front of collision
        Camera_BGCheckInfo(camera, &at, &eye);

        // Move actual camera positions towards intended positions
        camera->globalCtx->view.at = camera->at = lerpv(camera->at, at, 0.3);
        camera->globalCtx->view.eye = camera->eye = camera->eyeNext = lerpv(camera->eye, eye.pos, 0.3);

        // Apply quake offsets
        ShakeInfo camShake;
        if (Quake_Update(camera, &camShake)) {
            camera->globalCtx->view.at.x += camShake.atOffset.x;
            camera->globalCtx->view.at.y += camShake.atOffset.y;
            camera->globalCtx->view.at.z += camShake.atOffset.z;
            camera->globalCtx->view.eye.x += camShake.eyeOffset.x;
            camera->globalCtx->view.eye.y += camShake.eyeOffset.y;
            camera->globalCtx->view.eye.z += camShake.eyeOffset.z;
        }

        // Set the up vector for roll traps
        f32 cR = coss(IceTrap_CamRoll(0)), sR = sins(IceTrap_CamRoll(0)), r = distXZ(camera->at, camera->eye);
        camera->globalCtx->view.up.x = sR * (camera->at.z - camera->eye.z) / r;
        camera->globalCtx->view.up.y = cR;
        camera->globalCtx->view.up.z = sR * (camera->eye.x - camera->at.x) / r;

        // Set the direction of control stick inputs
        out->x = camera->inputDir.x = camera->camDir.x = pitch;
        out->y = camera->inputDir.y = camera->camDir.y = yaw;
        out->z = camera->inputDir.z = camera->camDir.z = 0;

        // Update camera setting
        s16 bgId          = camera->player->actor.floorBgId;
        s16 newCamDataIdx = Camera_GetCamDataId(&camera->globalCtx->colCtx, camera->player->actor.floorPoly, bgId);
        s16 newSetting =
            (bgId == 0x32) ? camera->globalCtx->colCtx.stat.colHeader->camDataList[newCamDataIdx].setting : 0;

        if (newCamDataIdx != -1 && newSetting && (newSetting != 0x35 || gSaveContext.linkAge) &&
            camera->player->actor.world.pos.y - camera->player->actor.floorHeight < 2) {
            camera->camDataIdx = newCamDataIdx;
            if (newSetting != camera->setting) {
                camera->prevSetting = camera->setting;
                camera->setting     = newSetting;
            }
        }
    }
    return;
}
