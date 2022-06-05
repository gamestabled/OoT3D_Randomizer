#include "z3D/z3D.h"
#include "objects.h"
#include "custom_models.h"
#include "settings.h"
#include "player.h"
#include "settings.h"
#include "fairy.h"
#include "icetrap.h"

#define PlayerActor_Init_addr 0x191844
#define PlayerActor_Init ((ActorFunc)PlayerActor_Init_addr)

#define PlayerActor_Update_addr 0x1E1B54
#define PlayerActor_Update ((ActorFunc)PlayerActor_Update_addr)

#define PlayerActor_Destroy_addr 0x19262C
#define PlayerActor_Destroy ((ActorFunc)PlayerActor_Destroy_addr)

#define Hookshot_ActorInit ((ActorInit*)0x5108E8)

u16 healthDecrement = 0;
u8  storedMask = 0;

void* Player_EditAndRetrieveCMB(ZARInfo* zarInfo, u32 objModelIdx) {
    void* cmbMan = ZAR_GetCMBByIndex(zarInfo, objModelIdx);

    if (gSaveContext.linkAge == 0) {
        void* cmb = (void*)(((char*)zarInfo->buf) + 0xDAE8);
        CustomModel_EditLinkToCustomTunic(cmb);
    } else {
        void* cmb = (void*)(((char*)zarInfo->buf) + 0xDACC);
        CustomModel_EditChildLinkToCustomTunic(cmb);
    }

    return cmbMan;
}

void* Player_GetCustomTunicCMAB(void) {
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
    s16 exObjectBankIdx = Object_GetIndex(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
    void* cmabMan;
    if (exObjectBankIdx < 0) {
        exObjectBankIdx = Object_Spawn(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
    }
    cmabMan = ZAR_GetCMABByIndex(&rExtendedObjectCtx.status[exObjectBankIdx].zarInfo, TEXANIM_CHILD_LINK_BODY);
    TexAnim_Spawn(PLAYER->skelAnime.unk_28->unk_0C, cmabMan);
}

void PlayerActor_rInit(Actor* thisx, GlobalContext* globalCtx) {
    PlayerActor_Init(thisx, globalCtx);
    if (gSettingsContext.fastBunnyHood) {
        PLAYER->currentMask = storedMask;
    }
    if (gSettingsContext.hookshotAsChild) {
        Hookshot_ActorInit->objectId = (gSaveContext.linkAge == 1 ? 0x1 : 0x14);
    }
}

void PlayerActor_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    Player* this = (Player*) thisx;
    PlayerActor_Update(thisx, globalCtx);

    if (this->naviActor != 0) {
        updateNaviColors((EnElf*)this->naviActor);
    }

    if (IceTrap_ActiveCurse == ICETRAP_CURSE_SWORD && PLAYER->meleeWeaponState != 0 &&
            ((PLAYER->itemActionParam >= 3 && PLAYER->itemActionParam <= 5) || PLAYER->itemActionParam == 35)) { //sword items
        PLAYER->meleeWeaponState = -1; // slash effect with no hitbox (same as "damageless death ISG")
    }
    if (PLAYER->itemActionParam == 38) { // Blue Potion
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
    }
    else {
        return gSaveContext.linkAge == 1 && !gSettingsContext.bowAsChild;
    }
}

s32 Player_ShouldDrawHookshotParts() {
    return gSaveContext.linkAge == 0 || !gSettingsContext.hookshotAsChild;
}
