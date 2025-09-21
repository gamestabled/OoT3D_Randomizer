#include "sheik.h"
#include "settings.h"
#include "objects.h"
#include "common.h"

static u8 Sheik_IsAt_TempleOfTime(void) {
    return gGlobalContext->sceneNum == 0x43 && gGlobalContext->roomNum == 1;
}

static u8 Sheik_IsAt_GanonsCastle(void) {
    return gGlobalContext->sceneNum == 0xD && gGlobalContext->roomNum == 1;
}

static u8 HasGanonsBK(void) {
    return gSaveContext.dungeonItems[DUNGEON_GANONS_TOWER] & 1;
}

static u8 PlayerCanFightGanon(void) {
    return
        // Dispelled Barrier
        gSaveContext.eventChkInf[12] & (1 << 3) &&
        // Has Bow
        gSaveContext.items[SLOT_BOW] != ITEM_NONE &&
        // Has Magic
        gSaveContext.magicAcquired &&
        // Has Light Arrows
        gSaveContext.items[SLOT_ARROW_LIGHT] != ITEM_NONE &&
        // Has Master Sword
        gSaveContext.equipment & (1 << 1);
}

void Sheik_Spawn(void) {
    if (!IsInGame() || !gSettingsContext.sheikHints || gSaveContext.linkAge != AGE_ADULT) {
        return;
    }

    if ((Sheik_IsAt_TempleOfTime() && !HasGanonsBK()) || (Sheik_IsAt_GanonsCastle() && HasGanonsBK())) {
        Object_FindEntryOrSpawn(0x8A);

        Vec3f pos;
        Vec3s rot;

        if (Sheik_IsAt_TempleOfTime()) {
            pos = (Vec3f){ -110, -40, 2375 };
            rot = (Vec3s){ 0, -32768, 0 };
        } else if (Sheik_IsAt_GanonsCastle()) {
            pos = (Vec3f){ 95, 150, 115 };
            rot = (Vec3s){ 0, -4096, 0 };
        }

        EnXc* sheik = (EnXc*)Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, 0x48, //
                                         pos.x, pos.y, pos.z,                             //
                                         rot.x, rot.y, rot.z,                             //
                                         100, FALSE);
        if (sheik == (void*)0) {
            return;
        }
        if (Sheik_IsAt_TempleOfTime()) {
            // Sometimes causes unmapped reads?!
            // Animation_Change(&sheik->anime, 0x12, 1.0, 0.0, Animation_GetLastFrame(&sheik->anime, 0x12), 0.0, 0);
        }
        sheik->action    = 0x4F;
        sheik->draw_mode = 1;
    }
}

s32 Sheik_GetTextID(Actor* sheik) {
    if (Sheik_IsAt_TempleOfTime()) {
        if (!HasGanonsBK()) {
            return 0x9150;
        } else {
            return 0x9151;
        }
    } else if (Sheik_IsAt_GanonsCastle()) {
        if (!PlayerCanFightGanon()) {
            return 0x9152;
        } else {
            return 0x9153;
        }
    }
    // Shouldn't be reached
    return 0;
}
