#include "z3D/z3D.h"
#include "objects.h"
#include "custom_models.h"
#include "settings.h"
#include "player.h"
#include "settings.h"
#include "fairy.h"
#include "icetrap.h"
#include "arrow.h"
#include "grotto.h"
#include "item_override.h"
#include "colors.h"
#include "common.h"
#include "gloom.h"

#define PlayerActor_Init ((ActorFunc)GAME_ADDR(0x191844))

#define PlayerActor_Update ((ActorFunc)GAME_ADDR(0x1E1B54))

#define PlayerActor_Destroy ((ActorFunc)GAME_ADDR(0x19262C))

#define PlayerActor_Draw ((ActorFunc)GAME_ADDR(0x4BF618))

#define Hookshot_ActorInit ((ActorInit*)GAME_ADDR(0x5108E8))

#define PlayerDListGroup_EmptySheathAdult ((void*)GAME_ADDR(0x53C4D8))
#define PlayerDListGroup_EmptySheathChildWithHylianShield ((void*)GAME_ADDR(0x53C4DC))

#define OBJECT_LINK_OPENING 0x19F

u16 healthDecrement = 0;
u8 storedMask       = 0;

static u32 sLastHitFrame = 0;
static s16 sPrevHealth   = INT16_MAX;

void** Player_EditAndRetrieveCMB(ZARInfo* zarInfo, u32 objModelIdx) {
    void** cmbMan = ZAR_GetCMBByIndex(zarInfo, objModelIdx);
    void* cmb     = *cmbMan;

    if (gSettingsContext.customTunicColors == ON) {
        if (gSaveContext.linkAge == AGE_ADULT) {
            CustomModel_EditLinkToCustomTunic(cmb);
        } else {
            CustomModel_EditChildLinkToCustomTunic(cmb);
        }
    }

    if (gSettingsContext.stickAsAdult) {
        // The unused deku stick will use the same materialIndex as the bow, to make it appear brown.
        // This also avoids issues with its combiners being repurposed by the custom tunic patches.
        ((char*)cmb)[0x4C52] = 5;
    }

    return cmbMan;
}

void* Player_GetCustomTunicCMAB(ZARInfo* originalZarInfo, u32 originalIndex) {
    if (gSettingsContext.customTunicColors == OFF || gActorOverlayTable[0].initInfo->objectId == OBJECT_LINK_OPENING) {
        return ZAR_GetCMABByIndex(originalZarInfo, originalIndex);
    }
    return Object_GetCMABByIndex(OBJECT_CUSTOM_GENERAL_ASSETS,
                                 (gSaveContext.linkAge == 0) ? TEXANIM_LINK_BODY : TEXANIM_CHILD_LINK_BODY);
}

void Player_SetChildCustomTunicCMAB(void) {
    if (gSettingsContext.customTunicColors == OFF) {
        return;
    }
    void* cmabMan = Object_GetCMABByIndex(OBJECT_CUSTOM_GENERAL_ASSETS, TEXANIM_CHILD_LINK_BODY);
    TexAnim_Spawn(PLAYER->skelAnime.unk_28->unk_0C, cmabMan);
}

void PlayerActor_rInit(Actor* thisx, GlobalContext* globalCtx) {
    if (IceTrap_ActiveCurse == ICETRAP_CURSE_SHIELD) {
        gSaveContext.equips.equipment &= ~0xF0; // unequip shield
    }

    Grotto_SanitizeEntranceType();
    // If the player has started with 0 hearts, some entrances that knock Link down will cause a Game Over.
    // When respawning after the Game Over, change the entrance type to avoid softlocks.
    u8 playerEntranceType = (thisx->params & 0xF00) >> 8;
    if (gSaveContext.healthCapacity == 0 && gSaveContext.respawnFlag == -2 && playerEntranceType == 7) {
        thisx->params = (thisx->params & ~0xF00) | 0xD00; // Link will spawn standing in place
    }

    PlayerActor_Init(thisx, globalCtx);

    if (gSettingsContext.fastBunnyHood) {
        PLAYER->currentMask = storedMask;
    }
    if (gSettingsContext.hookshotAsChild) {
        Hookshot_ActorInit->objectId = (gSaveContext.linkAge == 1 ? 0x1 : 0x14);
    }

    sPrevHealth = gSaveContext.health;
}

void PlayerActor_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    Player* this = (Player*)thisx;
    PlayerActor_Update(thisx, globalCtx);

    // Restore Randomizer draw function in case something (like Farore's Wind) overwrote it
    if (thisx->draw == PlayerActor_Draw) {
        thisx->draw = PlayerActor_rDraw;
    }

    Arrow_HandleSwap(this, globalCtx);

    if (this->naviActor != 0) {
        Fairy_UpdateRainbowNaviColors((EnElf*)this->naviActor);
    }

    if (IceTrap_ActiveCurse == ICETRAP_CURSE_SWORD && PLAYER->meleeWeaponState != 0 &&
        ((PLAYER->itemActionParam >= 3 && PLAYER->itemActionParam <= 5) ||
         PLAYER->itemActionParam == 35)) { // sword items
        PLAYER->meleeWeaponState = -1;     // slash effect with no hitbox (same as "damageless death ISG")
    }
    if (PLAYER->itemActionParam == 38) { // Blue Potion
        if (IceTrap_ActiveCurse == ICETRAP_CURSE_BLIND)
            gStaticContext.dekuNutFlash = -1;

        IceTrap_DispelCurses();
    }

    if (healthDecrement > 0) {
        if (gSaveContext.health > 4) {
            gSaveContext.health--;
            healthDecrement--;
        } else {
            healthDecrement = 0;
        }
    }

    // Handle hit stuff
    // Ignore single units of elemental damage
    if (gSaveContext.health < sPrevHealth - 1) {
        Player_OnHit();
    }
    sPrevHealth = gSaveContext.health;
}

void PlayerActor_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    if (gSettingsContext.fastBunnyHood) {
        storedMask = PLAYER->currentMask;
    }
    Fairy_ResetRainbowCMABs();
    PlayerActor_Destroy(thisx, globalCtx);
}

void PlayerActor_rDraw(Actor* thisx, GlobalContext* globalCtx) {
    // Draw empty scabbard if no sword is equipped.
    // For child, do this only with certain shields, because the game already handles the other cases.
    if (!(gSaveContext.equips.equipment & 0x000F)) {
        if (gSaveContext.linkAge == AGE_ADULT) {
            PLAYER->sheathDLists = PlayerDListGroup_EmptySheathAdult;
        } else if ((gSaveContext.equips.equipment & 0x00F0) >= 0x0020) { // Hylian or Mirror shield
            PLAYER->sheathDLists = PlayerDListGroup_EmptySheathChildWithHylianShield;
        }
    }

    Player_UpdateRainbowTunic();

    PlayerActor_Draw(thisx, globalCtx);
}

f32 Player_GetSpeedMultiplier(void) {
    f32 speedMultiplier = 1;

    if (gSettingsContext.fastBunnyHood && PLAYER->currentMask == 4 &&
        PLAYER->stateFuncPtr == (void*)GAME_ADDR(0x4BA378)) {
        speedMultiplier *= 1.5;
    }

    if (IceTrap_ActiveCurse == ICETRAP_CURSE_SLOW) {
        speedMultiplier *= 0.75;
    }

    return speedMultiplier;
}

s32 Player_IsAdult() {
    return gSaveContext.linkAge == AGE_ADULT;
}

s32 Player_ShouldApplyAdultItemsCMABs() {
    return gSaveContext.linkAge == AGE_ADULT || gSettingsContext.hoverbootsAsChild || gSettingsContext.hookshotAsChild;
}

s32 Player_ShouldUseSlingshot() {

    if (PLAYER->heldItemActionParam == 0xF) { // Slingshot
        return gSaveContext.linkAge == 1 || gSettingsContext.slingshotAsAdult;
    } else {
        return gSaveContext.linkAge == 1 && !gSettingsContext.bowAsChild;
    }
}

s32 Player_CanPickUpThisActor(Actor* interactedActor) {
    switch (interactedActor->id) {
        case 0xA: // Chest, can never be picked up
            return 0;
        case 0x6C: // Pedestal of Time, prevent interaction while waiting to get item
            return !ItemOverride_IsAPendingOverride();
        default:
            return 1;
    }
}

#define TUNIC_CYCLE_FRAMES 30
void Player_UpdateRainbowTunic(void) {
    u8 currentTunic = (gSaveContext.equips.equipment >> 8) & 3;
    void* cmabManager;
    char* cmabChunk;
    u8 redOffset, greenOffset, blueOffset;

    if (gSaveContext.linkAge == AGE_CHILD) {
        if (gSettingsContext.rainbowChildTunic == OFF) {
            return;
        }
        cmabManager = PLAYER->skelAnime.unk_28->unk_0C->cmabManager;
        redOffset   = 0x70;
        greenOffset = 0x88;
        blueOffset  = 0xA0;
    } else { // AGE_ADULT
        if ((currentTunic == 1 && gSettingsContext.rainbowKokiriTunic == OFF) ||
            (currentTunic == 2 && gSettingsContext.rainbowGoronTunic == OFF) ||
            (currentTunic == 3 && gSettingsContext.rainbowZoraTunic == OFF)) {
            return;
        }
        cmabManager = PLAYER->tunicTexAnim.cmabManager;
        redOffset   = 0x70 + 8 * (currentTunic - 1);
        greenOffset = 0x98 + 8 * (currentTunic - 1);
        blueOffset  = 0xC0 + 8 * (currentTunic - 1);
    }

    cmabChunk = *((char**)cmabManager);

    Color_RGBA8 color = Colors_GetRainbowColor(rGameplayFrames, TUNIC_CYCLE_FRAMES);

    *(f32*)(cmabChunk + redOffset)   = color.r / 255.0f;
    *(f32*)(cmabChunk + greenOffset) = color.g / 255.0f;
    *(f32*)(cmabChunk + blueOffset)  = color.b / 255.0f;
}

void Player_OnHit(void) {
    if (rGameplayFrames - sLastHitFrame > 5) {
        Gloom_OnHit();
    }

    sLastHitFrame = rGameplayFrames;
}
