#include "icetrap.h"
#include "objects.h"
#include "z3D/z3D.h"
#include "settings.h"
#include "common.h"
#include "input.h"

#define TimerFrameCounter *(s16*)GAME_ADDR(0x539D8A) // Used to decrease the timer every 30 frames
#define ControlStick_X *(float*)GAME_ADDR(0x5655C0)
#define ControlStick_Y *(float*)GAME_ADDR(0x5655C4)

static u8 pendingFreezes = 0;
static u8 cooldown       = 0;
static u8 modifyScale    = 0;

static u32 source[16];

s8 IceTrap_ActiveCurse         = -1;
static s16 previousTimer1Value = 0;
static s16 previousTimer2Value = 60;
u32 dizzyCurseSeed             = 0;
u16 rollOffset                 = 0;
u16 targetOffset               = 0;

// LUT for 1 - 0.5sin(0.5x) * 1.1^-x where x = 30 - INDEX
const f32 SCALE_TRAP[] = { 1.000f, 0.971f, 0.966f, 0.969f, 0.982f, 1.003f, 1.027f, 1.049f, 1.061f, 1.059f,
                           1.040f, 1.006f, 0.963f, 0.921f, 0.892f, 0.888f, 0.914f, 0.969f, 1.045f, 1.124f,
                           1.185f, 1.207f, 1.177f, 1.090f, 0.960f, 0.814f, 0.690f, 0.625f, 0.652f, 0.782f };

u32 possibleChestTraps[20]         = { ICETRAP_KNOCKDOWN, ICETRAP_ZELDA2_KNOCKBACK, ICETRAP_VANILLA,
                                       ICETRAP_SHOCK,     ICETRAP_BOMB_SIMPLE,      ICETRAP_BOMB_KNOCKDOWN };
u32 possibleChestTrapsAmount       = 0;
static u32 possibleItemTraps[20]   = { ICETRAP_KNOCKDOWN, ICETRAP_ZELDA2_KNOCKBACK, ICETRAP_VANILLA, ICETRAP_SHOCK,
                                       ICETRAP_SCALE };
static u32 possibleItemTrapsAmount = 0;

void IceTrap_InitTypes(void) {
    possibleChestTrapsAmount = 6;
    possibleItemTrapsAmount  = 5;

    if (gSettingsContext.randomTrapDmg == RANDOMTRAPS_BASIC)
        return;

    possibleChestTraps[possibleChestTrapsAmount++] = ICETRAP_RUPPY;
    possibleItemTraps[possibleItemTrapsAmount++]   = ICETRAP_RUPPY;

    if (gSettingsContext.fireTrap) {
        possibleChestTraps[possibleChestTrapsAmount++] = ICETRAP_FIRE;
        possibleItemTraps[possibleItemTrapsAmount++]   = ICETRAP_FIRE;
    }
    if (gSettingsContext.antiFairyTrap) {
        possibleChestTraps[possibleChestTrapsAmount++] = ICETRAP_ANTIFAIRY;
    }
    if (gSettingsContext.curseTraps) {
        possibleChestTraps[possibleChestTrapsAmount++] = ICETRAP_CURSE_SWORD;
        possibleChestTraps[possibleChestTrapsAmount++] = ICETRAP_CURSE_SHIELD;
        possibleChestTraps[possibleChestTrapsAmount++] = ICETRAP_CURSE_DIZZY;
        possibleChestTraps[possibleChestTrapsAmount++] = ICETRAP_CURSE_BLIND;
        possibleChestTraps[possibleChestTrapsAmount++] = ICETRAP_CURSE_SLOW;
        possibleItemTraps[possibleItemTrapsAmount++]   = ICETRAP_CURSE_SWORD;
        possibleItemTraps[possibleItemTrapsAmount++]   = ICETRAP_CURSE_SHIELD;
        possibleItemTraps[possibleItemTrapsAmount++]   = ICETRAP_CURSE_DIZZY;
        possibleItemTraps[possibleItemTrapsAmount++]   = ICETRAP_CURSE_BLIND;
        possibleItemTraps[possibleItemTrapsAmount++]   = ICETRAP_CURSE_SLOW;
    }
    if (gSettingsContext.screenTraps) {
        possibleChestTraps[possibleChestTrapsAmount++] = ICETRAP_CURSE_CROOKED;
        possibleChestTraps[possibleChestTrapsAmount++] = ICETRAP_CURSE_UNSTABLE;
        possibleItemTraps[possibleItemTrapsAmount++]   = ICETRAP_CURSE_CROOKED;
        possibleItemTraps[possibleItemTrapsAmount++]   = ICETRAP_CURSE_UNSTABLE;
    }
}

u32 IceTrap_IsPending(void) {
    return pendingFreezes > 0;
}

void IceTrap_Push(u32 key) {
    source[pendingFreezes++] = key;
}

void LinkDamageNoKnockback(void) {
    if (PLAYER->invincibilityTimer >= 0) {
        s32 changeHealth = Settings_ApplyDamageMultiplier(gGlobalContext, -(PLAYER->actor.colChkInfo.damage));
        gSaveContext.health += changeHealth / ((gSaveContext.doubleDefense) ? 2 : 1);
    }
    if (gSaveContext.health < 0) {
        gSaveContext.health = 0;
    }
    PLAYER->actor.colChkInfo.damage = 0;
    LinkDamage(gGlobalContext, PLAYER, 0, 0.0f, 0.0f, 0, 20);
}

void IceTrap_Give(void) {
    if (possibleItemTrapsAmount == 0)
        IceTrap_InitTypes();

    if (cooldown == 0 && pendingFreezes) {
        u32 pRandInt = dizzyCurseSeed = Hash(source[0]);

        u8 trapType = ICETRAP_VANILLA; // Default to ice trap
        if (gSettingsContext.randomTrapDmg != RANDOMTRAPS_OFF) {
            trapType = possibleItemTraps[pRandInt % possibleItemTrapsAmount];
        }

        pendingFreezes--;
        for (int i = 0; i < 15; i++) {
            source[i] = source[i + 1];
        }

        if (trapType >= ICETRAP_CURSE_SHIELD) {
            if (IceTrap_ActivateCurseTrap(trapType))
                return;
            else
                trapType = ICETRAP_SCALE; // if the curse can't trigger, use a scale trap
        }

        modifyScale = (trapType == ICETRAP_SCALE);

        PLAYER->stateFlags1 &= ~0xC00;
        if (trapType == ICETRAP_VANILLA || trapType == ICETRAP_FIRE) {
            PLAYER->actor.colChkInfo.damage = 0;
        } else {
            PLAYER->actor.colChkInfo.damage =
                (gSaveContext.masterQuestFlag) ? 16 : 8; // Damage Multiplier is accounted for by the patch
        }

        if (PLAYER->invincibilityTimer > 0) {
            PLAYER->invincibilityTimer = 0;
        }

        if (trapType == ICETRAP_FIRE) {
            FireDamage(&(PLAYER->actor), gGlobalContext, gRandInt % 2);
        }
        if (trapType == ICETRAP_SCALE) {
            LinkDamageNoKnockback();
        } else if (trapType == ICETRAP_RUPPY) {
            // Spawn 4 explosive rupees around the player
            Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, 0x131, PLAYER->actor.world.pos.x + 30,
                        PLAYER->actor.world.pos.y + 30, PLAYER->actor.world.pos.z + 30, 0, 0, 0, 0x2, FALSE);
            Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, 0x131, PLAYER->actor.world.pos.x + 30,
                        PLAYER->actor.world.pos.y + 30, PLAYER->actor.world.pos.z - 30, 0, 0, 0, 0x2, FALSE);
            Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, 0x131, PLAYER->actor.world.pos.x - 30,
                        PLAYER->actor.world.pos.y + 30, PLAYER->actor.world.pos.z + 30, 0, 0, 0, 0x2, FALSE);
            Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, 0x131, PLAYER->actor.world.pos.x - 30,
                        PLAYER->actor.world.pos.y + 30, PLAYER->actor.world.pos.z - 30, 0, 0, 0, 0x2, FALSE);
        } else {
            // From testing 0-4 are all the unique damage types and 0 is boring (lava/spikes damage), so it's used for
            // the Fire Trap
            LinkDamage(gGlobalContext, PLAYER, trapType, 0.0f, 0.0f, 0, 20);
        }
        cooldown = 30;
    }
}

u8 IceTrap_ActivateCurseTrap(u8 curseType) {
    if (IceTrap_ActiveCurse >= 0 || gSaveContext.timer2State != 0)
        return 0;

    do {
        switch (curseType) {
            case ICETRAP_CURSE_SHIELD:
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
            case ICETRAP_CURSE_SWORD:
                if (!(gSaveContext.equips.equipment & 0x07)) { // no sword equipped
                    curseType++;
                    continue;
                }
                break;
            case ICETRAP_CURSE_DIZZY:
                break;
            case ICETRAP_CURSE_BLIND:
                gStaticContext.dekuNutFlash          = -1;
                gStaticContext.renderGeometryDisable = 1;
                break;
            case ICETRAP_CURSE_SLOW:
                break;
            case ICETRAP_CURSE_CROOKED:
                targetOffset = dizzyCurseSeed % 0xC001 + 0x2000;
                break;
            case ICETRAP_CURSE_UNSTABLE:
                targetOffset = dizzyCurseSeed % 0x4001 - 0x2000;
                break;
            default:
                return 0;
        }
        break;
    } while (1);

    gSaveContext.timer2State = 4; // "active"
    gSaveContext.timer2Value = 60;
    TimerFrameCounter        = 30;
    DisplayTextbox(gGlobalContext, CURSETRAP_TEXT_BASE_INDEX + curseType - ICETRAP_CURSE_SHIELD, 0);
    PlaySound(0x100035C); // Poe laugh SFX
    IceTrap_ActiveCurse = (s8)curseType;
    return 1;
}

void IceTrap_DispelCurses(void) {
    if (IceTrap_ActiveCurse >= 0) {
        gGearUsabilityTable[GearSlot(ITEM_SHIELD_DEKU)]   = gSettingsContext.dekuShieldAsAdult ? 0x09 : 0x01;
        gGearUsabilityTable[GearSlot(ITEM_SHIELD_HYLIAN)] = 0x09;
        gGearUsabilityTable[GearSlot(ITEM_SHIELD_MIRROR)] = gSettingsContext.mirrorShieldAsChild ? 0x09 : 0x00;
        gStaticContext.renderGeometryDisable              = 0;
        previousTimer2Value                               = 60;
        gSaveContext.timer2State                          = 0;
        IceTrap_ActiveCurse                               = -1;
    }
}

u16 lerps(u16 a, u16 b, f32 t) {
    u16 tmp;
    if (a < b) {
        tmp = a;
        a   = b;
        b   = tmp;
        t   = 1 - t;
    }

    if (a - b < 0x8000) {
        return a + t * (b - a);
    }
    // Use overflow to lerp in other direction
    return a + t * (u16)(b - a);
}

void IceTrap_HandleCurses(void) {
    if (IceTrap_ActiveCurse == ICETRAP_CURSE_CROOKED || IceTrap_ActiveCurse == ICETRAP_CURSE_UNSTABLE) {
        rollOffset = lerps(rollOffset, targetOffset, 0.1);
    } else {
        rollOffset = lerps(rollOffset, 0, 0.1);
    }

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
            gStaticContext.dekuNutFlash          = -1;
            gStaticContext.renderGeometryDisable = 0;
        } else if (gSaveContext.timer2Value != previousTimer2Value && gSaveContext.timer2Value % 20 == 19 &&
                   gSaveContext.timer2Value < 59) {
            gStaticContext.dekuNutFlash          = -1;
            gStaticContext.renderGeometryDisable = 1;
        }
        previousTimer2Value = gSaveContext.timer2Value;
    }

    if (IceTrap_ActiveCurse == ICETRAP_CURSE_UNSTABLE && gSaveContext.timer2Value != previousTimer2Value) {
        targetOffset += Hash(targetOffset) % 0x4001 - 0x2000;
        previousTimer2Value = gSaveContext.timer2Value;
    }

    // Dispel curses if the timer is reset or runs out, or if the scene is Tower Collapse Exterior
    if ((!IsInGame() || gSaveContext.timer2State <= 1 || gSaveContext.timer2Value == 0 ||
         gGlobalContext->sceneNum == 0x1A)) {
        IceTrap_DispelCurses();
        return;
    }
}

void IceTrap_Update(void) {
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
           ((PLAYER->heldItemActionParam >= 3 && PLAYER->heldItemActionParam <= 5) ||
            PLAYER->heldItemActionParam == 35);
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

    uint32_t arr[4] = { in.a, in.b, in.r, in.l };
    for (u32 i = 3; i > 0; i--) {
        u32 j    = dizzyCurseSeed % i;
        u32 temp = arr[j];
        arr[j]   = arr[i];
        arr[i]   = temp;
    }

    btn_t out = in;
    out.a     = arr[0];
    out.b     = arr[1];
    out.r     = arr[2];
    out.l     = arr[3];
    return out;
}

u16 IceTrap_CamRoll(u16 roll) {
    return roll + rollOffset;
}
