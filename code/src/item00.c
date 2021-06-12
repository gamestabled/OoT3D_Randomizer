#include "z3D/z3D.h"
#include "z3D/actors/z_en_item00.h"
#include "models.h"
#include "settings.h"

#define EnItem00_Init_addr 0x1F69B4
#define EnItem00_Init ((ActorFunc)EnItem00_Init_addr)

#define EnItem00_Destroy_addr 0x1F706C
#define EnItem00_Destroy ((ActorFunc)EnItem00_Destroy_addr)

#define EnItem00_Draw_addr 0x22B6C0
#define EnItem00_Draw ((ActorFunc)EnItem00_Draw_addr)

#define THIS ((EnItem00*)thisx)

void EnItem00_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnItem00* item = THIS;
        s16 item00Type = item->actor.params & 0x00FF;
        //overrides the incoming ammo or magic drop with a blue rupee
    if(gSettingsContext.noDrops == NODROPS_NOAMMO || gSettingsContext.noDrops == NODROPS_NOAMMOORHEALTH){		
        if (item00Type == 0x04 ||
        item00Type == 0x05 ||
        item00Type == 0x08 ||
        item00Type == 0x09 ||
        item00Type == 0x0A ||
        item00Type == 0x0B ||
        item00Type == 0x0C ||
        item00Type == 0x0E ||
        item00Type == 0x0F ||
        item00Type == 0x10 ||
        item00Type == 0x12 ||
        item00Type == 0x19) {
            item->actor.params = (item->actor.params & 0xFF00) | 0x01;
        }
    }
    //overrides the incoming health drop with a green rupee
    if(gSettingsContext.noDrops == NODROPS_NOHEALTH || gSettingsContext.noDrops == NODROPS_NOAMMOORHEALTH){	
        if (item00Type == 0x03){
            item->actor.params = (item->actor.params & 0xFF00) | 0x00;
        }
    }
    EnItem00_Init(&item->actor, globalCtx);
    Model_SpawnByActor(&item->actor, globalCtx, 0);
}

void EnItem00_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    EnItem00* item = THIS;

    Model_DestroyByActor(&item->actor);
    EnItem00_Destroy(&item->actor, globalCtx);
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
    u8 hasBombs = (gSaveContext.items[ItemSlots[ITEM_BOMB]] != ITEM_NONE);
    u8 hasChus = (gSaveContext.items[ItemSlots[ITEM_BOMBCHU]] != ITEM_NONE);
    u8 bombCount = gSaveContext.ammo[ItemSlots[ITEM_BOMB]];
    u8 chuCount = gSaveContext.ammo[ItemSlots[ITEM_BOMBCHU]];

    if (!gSettingsContext.bombchuDrops) {
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
