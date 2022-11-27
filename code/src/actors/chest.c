#include "chest.h"
#include "z3D/z3D.h"
#include "item_override.h"
#include "item_table.h"
#include "settings.h"
#include "player.h"
#include "common.h"
#include "fairy.h"
#include "icetrap.h"

#define EnBox_Init_addr 0x1899EC
#define EnBox_Init ((ActorFunc)EnBox_Init_addr)

#define EnBox_Update_addr 0x1D5B70
#define EnBox_Update ((ActorFunc)EnBox_Update_addr)

// This variable is updated in rInit and used in Chest_OverrideDecoration,
// which runs inside a patch for the Init function. So it's only ever used
// by one chest at a time.
static u8 type = 0;

static u8 checkedForBombchus = 0;
Actor* lastTrapChest         = 0;
Actor* bomb                  = 0;
EnElf* fairy                 = 0;

void EnBox_rInit(Actor* thisx, GlobalContext* globalCtx) {
    lastTrapChest = 0;
    // treasure box shop chests
    u8 vanilla = (gSettingsContext.chestSize == CHESTSIZE_VANILLA) || (globalCtx->sceneNum == 16 && thisx->room != 6);

    if (!checkedForBombchus && gSettingsContext.bombchusInLogic && gSaveContext.items[8] == 0xFF) {
        ItemTable_SetBombchusChestType(0);
        checkedForBombchus = 1;
    }
    if (checkedForBombchus && gSaveContext.items[8] != 0xFF) {
        ItemTable_SetBombchusChestType(1);
        checkedForBombchus = 0;
    }

    ItemOverride thisOverride = ItemOverride_Lookup(thisx, globalCtx->sceneNum, 0);
    ItemRow* thisItemRow;
    if (vanilla || thisOverride.key.all == 0) {
        thisItemRow = ItemTable_GetItemRowFromIndex((thisx->params & 0x0FE0) >> 5); // get type from vanilla item table
    } else {
        thisItemRow = ItemTable_GetItemRow(ItemTable_ResolveUpgrades(thisOverride.value.itemId));
    }
    type = thisItemRow->chestType;

    EnBox_Init(thisx, globalCtx);

    if (vanilla) {
        type = 0;
        return;
    }

    if (type == WOODEN_BIG || type == DECORATED_BIG) {
        // Make chest BIG
        thisx->scale.x = 0.01f;
        thisx->scale.y = 0.01f;
        thisx->scale.z = 0.01f;
        // Move Ganon's Castle Zelda's Lullaby Chest back so it is reachable
        if ((thisx->params & 0xF000) == 0x8000 && globalCtx->sceneNum == 13 && thisx->room == 9) {
            thisx->world.pos.z = -962.0f;
        }
        // Move MQ Deku Tree SoT chest so it is reachable
        if (thisx->params == 0x5AA0 && globalCtx->sceneNum == 0 && thisx->room == 5) {
            thisx->world.pos.x = -1380.0f;
        }
    } else {
        // Make chest small
        thisx->scale.x = 0.005f;
        thisx->scale.y = 0.005f;
        thisx->scale.z = 0.005f;
        // Move Ganon's Castle Gold Gauntlets chest so it is reachable with hookshot from the switch platform
        if (thisx->params == 0x36C5 && globalCtx->sceneNum == 13 && thisx->room == 12) {
            thisx->world.pos.x = 1777.0f;
            thisx->world.pos.z = -3626.0f;
        }
        // Move Spirit Temple Compass Chest so it is reachable with hookshot
        else if (thisx->params == 0x3804 && globalCtx->sceneNum == 6 && thisx->room == 14) {
            thisx->world.pos.x = 400.0f;
        }
    }
    type = 0;
}

void EnBox_rUpdate(Actor* thisx, GlobalContext* globalCtx) {

    if (bomb != 0 && thisx == lastTrapChest) {
        *(((u8*)(bomb)) + 0x26C) = 2; // bomb timer
        bomb                     = 0;
    }

    if (fairy != 0 && thisx == lastTrapChest) {
        fairy->innerColor.r = 0; // evil dark fairy
        fairy->innerColor.g = 0;
        fairy->innerColor.b = 0;

        if (gSaveContext.health <= 16 || gSettingsContext.damageMultiplier == DAMAGEMULTIPLIER_OHKO) {
            gSaveContext.health = 0;
        } else if (gSettingsContext.damageMultiplier == DAMAGEMULTIPLIER_HALF) {
            healthDecrement = 64; // 4 Hearts
        } else if (gSettingsContext.damageMultiplier == DAMAGEMULTIPLIER_DEFAULT) {
            healthDecrement = 128; // 8 Hearts
        } else if (gSettingsContext.damageMultiplier == DAMAGEMULTIPLIER_DOUBLE) {
            healthDecrement = 256; // 16 Hearts
        } else if (gSettingsContext.damageMultiplier == DAMAGEMULTIPLIER_QUADRUPLE) {
            healthDecrement = 512; // 32 Hearts
        } else {
            healthDecrement = 640; // 40 Hearts
        }

        if (gSaveContext.doubleDefense) {
            healthDecrement /= 2;
        }
        PlaySound(0x100035C); // Poe laugh SFX
        fairy = 0;
    }

    EnBox_Update(thisx, globalCtx);
}

u8 Chest_OverrideAnimation() {

    if ((gSettingsContext.chestAnimations == CHESTANIMATIONS_ALWAYSFAST) ||
        (rActiveItemActionId == 0)) // The animation is always fast for unused chests that aren't randomized
        return 0;

    if (!rActiveItemFastChest) {
        PlaySound(0x1000599); // Play chest opening fanfare
    }
    return !rActiveItemFastChest;
}

u8 Chest_OverrideDecoration() {

    if (type == DECORATED_BIG ||
        ((gSettingsContext.chestSize == CHESTSIZE_MATCHCONTENT) && (type == DECORATED_SMALL))) {
        return 1;
    }
    return 0;
}

u8 vanillaIceTrap() {
    // Ice Traps from chests softlock when max health is 0, so just kill Link immediately
    if (gSaveContext.healthCapacity == 0) {
        PLAYER->stateFlags1 &= ~0x20000C00;
        gSaveContext.health = 0;
        return 1;
    }
    return 0;
}

u8 Chest_OverrideIceSmoke(Actor* thisx) {
    if (gSettingsContext.randomTrapDmg == RANDOMTRAPS_OFF) {
        return vanillaIceTrap();
    }

    if (possibleChestTrapsAmount == 0)
        IceTrap_InitTypes();

    if (thisx != lastTrapChest && thisx->xzDistToPlayer < 50.0f) {
        lastTrapChest = thisx;
        u32 pRandInt = dizzyCurseSeed = Hash(thisx->params);

        u8 trapType = possibleChestTraps[pRandInt % possibleChestTrapsAmount];

        // Curses
        if (trapType >= ICETRAP_CURSE_SHIELD) {
            if (IceTrap_ActivateCurseTrap(trapType)) {
                PLAYER->getItemId = 0;
                PLAYER->stateFlags1 &= ~0x20000C00;
                PLAYER->actor.home.pos.y = -5000; // Make Link airborne for a frame to cancel the get item event
                return 1;
            } else {
                trapType = ICETRAP_BOMB_KNOCKDOWN; // if the curse can't trigger, use a bomb trap
            }
        }

        if (trapType == ICETRAP_VANILLA) {
            return vanillaIceTrap();
        }
        PLAYER->getItemId = 0;
        PLAYER->stateFlags1 &= ~0x20000C00;
        PLAYER->actor.colChkInfo.damage = (gSettingsContext.mirrorWorld) ? 16 : 8;
        if (trapType == ICETRAP_KNOCKDOWN || trapType == ICETRAP_BOMB_KNOCKDOWN) { // For knockback
            PLAYER->stateFlags1 |= 0x4000;                                         // Ledge Cancel
        }
        if (PLAYER->invincibilityTimer > 0) {
            PLAYER->invincibilityTimer = 0;
        }

        switch (trapType) {
            case ICETRAP_KNOCKDOWN:
            case ICETRAP_ZELDA2_KNOCKBACK:
            case ICETRAP_SHOCK:
                LinkDamage(gGlobalContext, PLAYER, trapType, 0.0f, 0.0f, 0, 20);
                break;
            case ICETRAP_BOMB_SIMPLE:
            case ICETRAP_BOMB_KNOCKDOWN:
                bomb = Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, 0x10, thisx->world.pos.x,
                                   thisx->world.pos.y, thisx->world.pos.z, 0, 0, 0, 0);
                break;
            case ICETRAP_ANTIFAIRY:
                fairy = (EnElf*)Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, 0x18, thisx->world.pos.x,
                                            thisx->world.pos.y, thisx->world.pos.z, 0, 0, 0, 0x5);
                PLAYER->actor.home.pos.y = -5000; // Make Link airborne for a frame to cancel the get item event
                break;
            case ICETRAP_RUPPY:
                Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, 0x131, thisx->world.pos.x,
                            thisx->world.pos.y + 30, thisx->world.pos.z, 0, 0, 0, 0x2);
                PLAYER->actor.home.pos.y = -5000; // Make Link airborne for a frame to cancel the get item event
                break;
            case ICETRAP_FIRE:
                FireDamage(&(PLAYER->actor), gGlobalContext, gRandInt % 2);
                LinkDamage(gGlobalContext, PLAYER, 0, 0.0f, 0.0f, 0, 20);
                break;
        }
    }

    return 1;
}
