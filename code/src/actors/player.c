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

#define PlayerActor_Init_addr 0x191844
#define PlayerActor_Init ((ActorFunc)PlayerActor_Init_addr)

#define PlayerActor_Update_addr 0x1E1B54
#define PlayerActor_Update ((ActorFunc)PlayerActor_Update_addr)

#define PlayerActor_Destroy_addr 0x19262C
#define PlayerActor_Destroy ((ActorFunc)PlayerActor_Destroy_addr)

#define PlayerActor_Draw_addr 0x4BF618
#define PlayerActor_Draw ((ActorFunc)PlayerActor_Draw_addr)

#define Hookshot_ActorInit ((ActorInit*)0x5108E8)

#define PlayerDListGroup_EmptySheathAdult ((void*)0x53C4D8)
#define PlayerDListGroup_EmptySheathChildWithHylianShield ((void*)0x53C4DC)

u16 healthDecrement = 0;
u8 storedMask       = 0;

void* Player_EditAndRetrieveCMB(ZARInfo* zarInfo, u32 objModelIdx) {
    void* cmbMan = ZAR_GetCMBByIndex(zarInfo, objModelIdx);

    if (gSettingsContext.customTunicColors == ON) {
        if (gSaveContext.linkAge == 0) {
            void* cmb = (void*)(((char*)zarInfo->buf) + 0xDAE8);
            CustomModel_EditLinkToCustomTunic(cmb);
        } else {
            void* cmb = (void*)(((char*)zarInfo->buf) + 0xDACC);
            CustomModel_EditChildLinkToCustomTunic(cmb);
        }
    }

    return cmbMan;
}

void* Player_GetCustomTunicCMAB(ZARInfo* originalZarInfo, u32 originalIndex) {
    if (gSettingsContext.customTunicColors == OFF) {
        return ZAR_GetCMABByIndex(originalZarInfo, originalIndex);
    }
    s16 exObjectBankIdx = Object_GetIndex(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
    if (exObjectBankIdx < 0) {
        exObjectBankIdx = Object_Spawn(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
    }
    if (gSaveContext.linkAge == 0) {
        return ZAR_GetCMABByIndex(&rExtendedObjectCtx.status[exObjectBankIdx].zarInfo, TEXANIM_LINK_BODY);
    } else {
        return ZAR_GetCMABByIndex(&rExtendedObjectCtx.status[exObjectBankIdx].zarInfo, TEXANIM_CHILD_LINK_BODY);
    }
}

void Player_SetChildCustomTunicCMAB(void) {
    if (gSettingsContext.customTunicColors == OFF) {
        return;
    }
    s16 exObjectBankIdx = Object_GetIndex(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
    void* cmabMan;
    if (exObjectBankIdx < 0) {
        exObjectBankIdx = Object_Spawn(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
    }
    cmabMan = ZAR_GetCMABByIndex(&rExtendedObjectCtx.status[exObjectBankIdx].zarInfo, TEXANIM_CHILD_LINK_BODY);
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
}

void PlayerActor_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    Player* this = (Player*)thisx;
    PlayerActor_Update(thisx, globalCtx);

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

    if (healthDecrement <= 0) {
        return;
    }

    if (gSaveContext.health > 4) {
        gSaveContext.health--;
        healthDecrement--;
    } else {
        healthDecrement = 0;
    }
}

void PlayerActor_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    if (gSettingsContext.fastBunnyHood) {
        storedMask = PLAYER->currentMask;
    }
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
    PlayerActor_Draw(thisx, globalCtx);
}

f32 Player_GetSpeedMultiplier(void) {
    f32 speedMultiplier = 1;

    if (gSettingsContext.fastBunnyHood && PLAYER->currentMask == 4 && PLAYER->stateFuncPtr == (void*)0x4BA378) {
        speedMultiplier *= 1.5;
    }

    return speedMultiplier;
}

s32 Player_ShouldDrawHoverBootsEffect() {
    return gSaveContext.linkAge == 0 || !gSettingsContext.hoverbootsAsChild;
}

s32 Player_ShouldUseSlingshot() {

    if (PLAYER->heldItemActionParam == 0xF) { // Slingshot
        return gSaveContext.linkAge == 1 || gSettingsContext.slingshotAsAdult;
    } else {
        return gSaveContext.linkAge == 1 && !gSettingsContext.bowAsChild;
    }
}

s32 Player_ShouldDrawHookshotParts() {
    return gSaveContext.linkAge == 0 || !gSettingsContext.hookshotAsChild;
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
