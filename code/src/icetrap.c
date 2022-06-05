#include "icetrap.h"
#include "objects.h"
#include "z3D/z3D.h"
#include "settings.h"
#include "common.h"
#include "input.h"

#define TimerFrameCounter *(s16*)0x539D8A // Used to decrease the timer every 30 frames
#define ControlStick_X *(float*)0x5655C0
#define ControlStick_Y *(float*)0x5655C4

static u8 pendingFreezes = 0;
static u8 cooldown = 0;
static u8 modifyScale = 0;

static u32 source[16];

s8 IceTrap_ActiveCurse = -1;
static s16 previousTimer1Value = 0;
static s16 previousTimer2Value = 60;
static u32 dizzyCurseSeed = 0;

// LUT for 1 - 0.5sin(0.5x) * 1.1^-x where x = 30 - INDEX
const f32 SCALE_TRAP[] = {
    1.000f, 0.971f, 0.966f, 0.969f, 0.982f,
    1.003f, 1.027f, 1.049f, 1.061f, 1.059f,
    1.040f, 1.006f, 0.963f, 0.921f, 0.892f,
    0.888f, 0.914f, 0.969f, 1.045f, 1.124f,
    1.185f, 1.207f, 1.177f, 1.090f, 0.960f,
    0.814f, 0.690f, 0.625f, 0.652f, 0.782f
};

u32 IceTrap_IsPending(void) {
    return pendingFreezes > 0;
}

void IceTrap_Push(u32 key) {
    source[pendingFreezes++] = key;
}

void LinkDamageNoKnockback(void) {
    if (PLAYER->invincibilityTimer >= 0) {
        s32 changeHealth = Settings_ApplyDamageMultiplier(gGlobalContext, -(PLAYER->actor.colChkInfo.damage));
        gSaveContext.health += changeHealth / ((gSaveContext.doubleDefense)? 2 : 1);
    }
    if (gSaveContext.health < 0) {
        gSaveContext.health = 0;
    }
    PLAYER->actor.colChkInfo.damage = 0;
    LinkDamage(gGlobalContext, PLAYER, 0, 0.0f, 0.0f, 0, 20);
}

void IceTrap_Give(void) {
    if (cooldown == 0 && pendingFreezes &&
        ExtendedObject_IsLoaded(&gGlobalContext->objectCtx, ExtendedObject_GetIndex(&gGlobalContext->objectCtx, 0x3))) {
        u32 pRandInt = dizzyCurseSeed = Hash(source[0]);

        u8 damageType = 3; // Default to ice trap
        if (gSettingsContext.randomTrapDmg == 1) { //Basic
            damageType = pRandInt % 5 + 1; // From testing 0-4 are all the unique damage types and 0 is boring (5 is custom)
        }
        else if (gSettingsContext.randomTrapDmg == 2) { //Advanced
            damageType = pRandInt % 10; // 0 will be used for the fire trap, 6 and higher for curses
        }

        pendingFreezes--;
        for (int i = 0; i < 15; i++) {
            source[i] = source[i + 1];
        }

        if (damageType > 5) {
            if (IceTrap_ActivateCurseTrap((s8)damageType - 6))
                return;
            else
                damageType = 5; // if the curse can't trigger, use a scale trap
        }

        modifyScale = (damageType == 5);

        PLAYER->stateFlags1 &= ~0xC00;
        if (damageType == 3 || damageType == 0) {
            PLAYER->actor.colChkInfo.damage = 0;
        } else {
            PLAYER->actor.colChkInfo.damage = (gSettingsContext.mirrorWorld) ? 16 : 8; // Damage Multiplier is accounted for by the patch
        }

        if (PLAYER->invincibilityTimer > 0) {
            PLAYER->invincibilityTimer = 0;
        }

        if (damageType == 0) {
            FireDamage(&(PLAYER->actor), gGlobalContext, 0);
        }
        if (damageType == 5) {
            LinkDamageNoKnockback();
        } else {
            LinkDamage(gGlobalContext, PLAYER, damageType, 0.0f, 0.0f, 0, 20);
        }
        cooldown = 30;
    }
}

u8 IceTrap_ActivateCurseTrap(s8 curseType) {
    if (IceTrap_ActiveCurse >= 0 || gSaveContext.timer2State != 0)
        return 0;

    do {
        switch (curseType) {
            case ICETRAP_CURSE_SHIELD :
                if (!(gSaveContext.equips.equipment & 0x70)) { // no shield equipped
                    curseType++;
                    continue;
                }
                gSaveContext.equips.equipment &= ~0xF0; // unequip shield
                Player_SetEquipmentData(gGlobalContext, PLAYER);
                gGearUsabilityTable[GearSlot(ITEM_SHIELD_DEKU)]   = 0x02;
                gGearUsabilityTable[GearSlot(ITEM_SHIELD_HYLIAN)] = 0x02;
                gGearUsabilityTable[GearSlot(ITEM_SHIELD_MIRROR)] = 0x02;
                break;
            case ICETRAP_CURSE_SWORD :
                if (!(gSaveContext.equips.equipment & 0x07)) { // no sword equipped
                    curseType++;
                    continue;
                }
                break;
            case ICETRAP_CURSE_DIZZY :
                break;
            case ICETRAP_CURSE_BLIND :
                gStaticContext.dekuNutFlash = -1;
                gStaticContext.renderGeometryDisable = 1;
                break;
            default : return 0;
        }
        break;
    } while (1);

    gSaveContext.timer2State = 4; // "active"
    gSaveContext.timer2Value = 60;
    TimerFrameCounter = 30;
    DisplayTextbox(gGlobalContext, 0x8FF0 + curseType, 0);
    PlaySound(0x100035C); // Poe laugh SFX
    IceTrap_ActiveCurse = curseType;
    return 1;
}

void IceTrap_DispelCurses(void) {
    if (IceTrap_ActiveCurse >= 0) {
        gGearUsabilityTable[GearSlot(ITEM_SHIELD_DEKU)]   = gSettingsContext.dekuShieldAsAdult ? 0x09 : 0x01;
        gGearUsabilityTable[GearSlot(ITEM_SHIELD_HYLIAN)] = 0x09;
        gGearUsabilityTable[GearSlot(ITEM_SHIELD_MIRROR)] = gSettingsContext.mirrorShieldAsChild ? 0x09 : 0x00;
        gStaticContext.renderGeometryDisable = 0;
        previousTimer2Value = 60;
        gSaveContext.timer2State = 0;
        IceTrap_ActiveCurse = -1;
    }
}

void IceTrap_HandleCurses(void) {
    if (IceTrap_ActiveCurse < 0)
        return;

    // If the white timer is overriding the yellow timer, force the yellow one to decrease anyway
    if (gSaveContext.timer1State != 0 && gSaveContext.timer1Value != previousTimer1Value) {
        gSaveContext.timer2Value--;
    }
    previousTimer1Value = gSaveContext.timer1Value;

    // During the blindness curse, show geometry for 1 second every 20
    if (IceTrap_ActiveCurse == ICETRAP_CURSE_BLIND) {
        if (gSaveContext.timer2Value != previousTimer2Value && gSaveContext.timer2Value % 20 == 0) {
            gStaticContext.dekuNutFlash = -1;
            gStaticContext.renderGeometryDisable = 0;
        }
        else if (gSaveContext.timer2Value != previousTimer2Value && gSaveContext.timer2Value % 20 == 19 && gSaveContext.timer2Value < 59) {
            gStaticContext.dekuNutFlash = -1;
            gStaticContext.renderGeometryDisable = 1;
        }
        previousTimer2Value = gSaveContext.timer2Value;
    }

    // Dispel curses if the timer is reset or runs out, or if the scene is Tower Collapse Exterior
    if ((!IsInGame() || gSaveContext.timer2State != 4 || gSaveContext.timer2Value == 0 || gGlobalContext->sceneNum == 0x1A)) {
        IceTrap_DispelCurses();
        return;
    }
}

void IceTrap_Update(void) {
    // Make sure zelda_dangeon_keep is loaded
    if (ExtendedObject_GetIndex(&gGlobalContext->objectCtx, 0x3) < 0) {
        ExtendedObject_Spawn(&gGlobalContext->objectCtx, 0x3);
    }

    IceTrap_HandleCurses();

    if (cooldown != 0) {
        cooldown--;

        if (modifyScale) {
            PLAYER->actor.scale.y = 0.01f * SCALE_TRAP[cooldown];
        }
    }
}

u8 IceTrap_IsCurseActive(void) {
    return IceTrap_ActiveCurse >= 0;
}

u8 IceTrap_IsSlashHitboxDisabled(void) {
    return IceTrap_ActiveCurse == ICETRAP_CURSE_SWORD &&
            ((PLAYER->heldItemActionParam >= 3 && PLAYER->heldItemActionParam <= 5) || PLAYER->heldItemActionParam == 35);
}

void IceTrap_ReverseStick(void) {
    if (IceTrap_ActiveCurse == ICETRAP_CURSE_DIZZY) {
        ControlStick_X = -ControlStick_X;
        ControlStick_Y = -ControlStick_Y;
    }
}

btn_t IceTrap_RandomizeButtons(btn_t in) {
    if (IceTrap_ActiveCurse != ICETRAP_CURSE_DIZZY) {
        return in;
    }

    uint32_t arr[4] = {in.a, in.b, in.r, in.l};
    for (u32 i = 3; i > 0; i--) {
        u32 j = dizzyCurseSeed % i;
        u32 temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
    }

    btn_t out = in;
    out.a = arr[0];
    out.b = arr[1];
    out.r = arr[2];
    out.l = arr[3];
    return out;
}
