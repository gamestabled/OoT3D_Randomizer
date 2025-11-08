#include "z3D/z3D.h"
#include "z3D/actors/z_en_item00.h"
#include "models.h"
#include "actors/obj_mure3.h"
#include "settings.h"
#include "common.h"

#define EnItem00_Init ((ActorFunc)GAME_ADDR(0x1F69B4))

#define EnItem00_Destroy ((ActorFunc)GAME_ADDR(0x1F706C))

#define EnItem00_Update ((ActorFunc)GAME_ADDR(0x22B71C))

#define EnItem00_Draw ((ActorFunc)GAME_ADDR(0x22B6C0))

#define THIS ((EnItem00*)thisx)

#define FUN_002B175C (void*)GAME_ADDR(0x2B175C)

void EnItem00_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnItem00* item = THIS;
    s16 DropType   = item->actor.params & 0x00FF;
    // If no ammo drops is chosen as an option, overrides the incoming ammo or magic drop with a blue rupee
    if (gSettingsContext.ammoDrops == AMMODROPS_NONE) {
        switch (DropType) {
            case ITEM00_BOMBS_A:
            case ITEM00_ARROWS_SINGLE:
            case ITEM00_ARROWS_SMALL:
            case ITEM00_ARROWS_MEDIUM:
            case ITEM00_ARROWS_LARGE:
            case ITEM00_BOMBS_B:
            case ITEM00_NUTS:
            case ITEM00_MAGIC_LARGE:
            case ITEM00_MAGIC_SMALL:
            case ITEM00_SEEDS:
            case ITEM00_FLEXIBLE:
            case ITEM00_BOMBS_SPECIAL:
                item->actor.params = (item->actor.params & 0xFF00) | 0x01;
                break;
        }
    }
    // If no health drops is chosen as an option, overrides the incoming health drop with a green rupee
    if ((gSettingsContext.heartDropRefill == HEARTDROPREFILL_NODROP) ||
        (gSettingsContext.heartDropRefill == HEARTDROPREFILL_NODROPREFILL)) {
        if (DropType == ITEM00_RECOVERY_HEART) {
            item->actor.params = (item->actor.params & 0xFF00) | 0x00;
        }
    }
    EnItem00_Init(&item->actor, globalCtx);

    // For rupees spawned by Rupee Circles (ObjMure3) We store the "collectibleFlag" in actor.home.rot.z since that is
    // not really used for them. Since collectibleFlag normally gets truncated to 0x3F we can use any value at or above
    // 0x40. We've reserved 0x40-0x46 for Rupee circle rupees.
    if (item->collectibleFlag == 0x00 && isObjMure3Updating && item->actor.home.rot.z == 0) {
        item->actor.home.rot.z = extraCollectibleFlag;
        extraCollectibleFlag += 1;
        if (extraCollectibleFlag > 0x46) {
            extraCollectibleFlag = 0x40;
        }
    }
    Model_SpawnByActor(&item->actor, globalCtx, 0);
}

void EnItem00_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    EnItem00* item = THIS;

    Model_DestroyByActor(&item->actor);
    EnItem00_Destroy(&item->actor, globalCtx);
}

void EnItem00_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnItem00* item = THIS;

    if (Flags_GetCollectible(globalCtx, item->collectibleFlag) && item->action_fn != FUN_002B175C) {
        Actor_Kill(&item->actor);
        return;
    }

    EnItem00_Update(&item->actor, globalCtx);
}

void EnItem00_rDraw(Actor* thisx, GlobalContext* globalCtX) {
    EnItem00* item = THIS;

    if ((item->unk_1B0 & item->unk_1AE) == 0) {
        if (!Model_DrawByActor(&item->actor)) {
            EnItem00_Draw(&item->actor, globalCtX);
        }
    }
}

// overrides the incoming dropId to either a bombchu drop (5)
// or no drop (-1) as appropriate
u32 Item_ConvertBombDrop(u32 dropId) {
    u8 hasBombs  = (gSaveContext.items[ItemSlots[ITEM_BOMB]] != ITEM_NONE);
    u8 hasChus   = (gSaveContext.items[ItemSlots[ITEM_BOMBCHU]] != ITEM_NONE);
    u8 bombCount = gSaveContext.ammo[ItemSlots[ITEM_BOMB]];
    u8 chuCount  = gSaveContext.ammo[ItemSlots[ITEM_BOMBCHU]];

    if (gSettingsContext.ammoDrops != AMMODROPS_BOMBCHU) {
        if (hasBombs) {
            return dropId;
        } else {
            return -1;
        }
    }

    if (!hasBombs && !hasChus) {
        return -1;
    } else if (hasBombs && !hasChus) {
        return dropId;
    } else if (!hasBombs && hasChus) {
        return 5;
    } else {
        if (bombCount <= 15) {
            if (chuCount < bombCount) {
                return 5;
            } else {
                return dropId;
            }
        } else if (chuCount <= 15) {
            return 5;
        } else {
            if (gRandInt % 2) {
                return 5;
            } else {
                return dropId;
            }
        }
    }
}
