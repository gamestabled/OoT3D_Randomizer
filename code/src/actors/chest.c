#include "chest.h"
#include "z3D/z3D.h"
#include "item_override.h"
#include "item_table.h"
#include "settings.h"
#include "player.h"
#include "common.h"
#include "fairy.h"
#include "icetrap.h"
#include "objects.h"
#include "custom_models.h"

#define EnBox_Init_addr 0x1899EC
#define EnBox_Init ((ActorFunc)EnBox_Init_addr)

#define EnBox_Update_addr 0x1D5B70
#define EnBox_Update ((ActorFunc)EnBox_Update_addr)

static Actor* sLastTrapChest = 0;
static Actor* sBomb          = 0;
static EnElf* sFairy         = 0;

// Bombchus are a major item if they're in logic and haven't been obtained yet
u32 isBombchuMajor(void) {
    return gSettingsContext.bombchusInLogic && gSaveContext.items[8] == 0xFF;
}

void EnBox_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnBox* this    = (EnBox*)thisx;
    sLastTrapChest = 0;

    u8 vanilla = (gSettingsContext.chestAppearance == CHESTAPPEARANCE_VANILLA) ||
                 (globalCtx->sceneNum == 16 && thisx->room != 6); // treasure chest shop, final room

    ItemOverride thisOverride = ItemOverride_Lookup(thisx, globalCtx->sceneNum, 0);
    ItemRow* thisItemRow;
    if (vanilla || thisOverride.key.all == 0) {
        thisItemRow = ItemTable_GetItemRowFromIndex((thisx->params & 0x0FE0) >> 5); // get type from vanilla item table
    } else {
        thisItemRow = ItemTable_GetItemRow(ItemTable_ResolveUpgrades(thisOverride.value.itemId));
    }
    u8 type = thisItemRow->chestType;
    if (type == CHEST_BOMBCHUS) {
        type = isBombchuMajor() ? CHEST_MAJOR : CHEST_JUNK;
    }

    EnBox_Init(thisx, globalCtx);

    // Change Chest Model
    if (type == CHEST_BOSS_KEY ||
        ((gSettingsContext.chestAppearance != CHESTAPPEARANCE_VANILLA) && (type == CHEST_SMALL_KEY))) {
        // 0: Fancy Chest   1: Wooden Chest   2: Fancy Lid   3: Wooden Lid
        Model_EnableMeshGroupByIndex(this->skelAnime.unk_28, 0);
        Model_EnableMeshGroupByIndex(this->skelAnime.unk_28, 2);
        Model_DisableMeshGroupByIndex(this->skelAnime.unk_28, 1);
        Model_DisableMeshGroupByIndex(this->skelAnime.unk_28, 3);
    } else {
        Model_EnableMeshGroupByIndex(this->skelAnime.unk_28, 1);
        Model_EnableMeshGroupByIndex(this->skelAnime.unk_28, 3);
        Model_DisableMeshGroupByIndex(this->skelAnime.unk_28, 0);
        Model_DisableMeshGroupByIndex(this->skelAnime.unk_28, 2);
    }

    // Stop here for vanilla settings
    if (vanilla) {
        return;
    }

    // Change Chest Texture
    if (gSettingsContext.chestAppearance == CHESTAPPEARANCE_TEXTURE ||
        gSettingsContext.chestAppearance == CHESTAPPEARANCE_SIZE_AND_TEXTURE) {
        s16 exObjectBankIdx = Object_GetIndex(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
        void* cmabMan;
        if (exObjectBankIdx < 0) {
            exObjectBankIdx = Object_Spawn(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
        }

        void** cmbMan = ZAR_GetCMBByIndex(this->zarInfo, 1);
        // Set mipmap count to 1 for both chest models
        *((u8*)(*cmbMan) + 0x59C) = 1;
        *((u8*)(*cmbMan) + 0x530) = 1;

        static const u32 chestType_to_assetIndex[CHESTTYPE_MAX] = { TEXANIM_GOLD_CHEST, 0, 0,
                                                                    TEXANIM_KEY_CHEST,  0, TEXANIM_HEART_CHEST,
                                                                    TEXANIM_SKULL_CHEST };

        u32 assetIndex = chestType_to_assetIndex[type];
        if (assetIndex != 0) {
            cmabMan = ZAR_GetCMABByIndex(&rExtendedObjectCtx.status[exObjectBankIdx].zarInfo, assetIndex);
            TexAnim_Spawn(this->skelAnime.unk_28->unk_0C, cmabMan);
        }
    }

    // Change Chest Size
    if (gSettingsContext.chestAppearance == CHESTAPPEARANCE_CLASSIC ||
        gSettingsContext.chestAppearance == CHESTAPPEARANCE_SIZE_AND_TEXTURE) {
        if (type == CHEST_MAJOR || type == CHEST_BOSS_KEY) {
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
    }
}

void EnBox_rUpdate(Actor* thisx, GlobalContext* globalCtx) {

    if (sBomb != 0 && thisx == sLastTrapChest) {
        *(((u8*)(sBomb)) + 0x26C) = 2; // bomb timer
        sBomb                     = 0;
    }

    if (sFairy != 0 && thisx == sLastTrapChest) {
        sFairy->innerColor.r = 0; // evil dark fairy
        sFairy->innerColor.g = 0;
        sFairy->innerColor.b = 0;

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
        sFairy = 0;
    }

    EnBox_Update(thisx, globalCtx);

    // Use correct size for the light effect if it appears
    if (thisx->child != 0) {
        thisx->child->scale = thisx->scale;
    }
}

u8 Chest_OverrideAnimation() {

    if ((gSettingsContext.chestAnimations == CHESTANIMATIONS_ALWAYSFAST) ||
        (rActiveItemActionId == 0)) // The animation is always fast for unused chests that aren't randomized
        return FALSE;

    switch (rActiveItemChestType) {
        case CHEST_BOMBCHUS:
            if (!isBombchuMajor())
                break;
        case CHEST_MAJOR:
        case CHEST_BOSS_KEY:
            return TRUE;
    }

    return FALSE;
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

    if (thisx != sLastTrapChest && thisx->xzDistToPlayer < 50.0f) {
        sLastTrapChest = thisx;
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
        PLAYER->actor.colChkInfo.damage = (gSaveContext.masterQuestFlag) ? 16 : 8;
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
                sBomb = Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, 0x10, thisx->world.pos.x,
                                    thisx->world.pos.y, thisx->world.pos.z, 0, 0, 0, 0);
                break;
            case ICETRAP_ANTIFAIRY:
                sFairy = (EnElf*)Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, 0x18, thisx->world.pos.x,
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
