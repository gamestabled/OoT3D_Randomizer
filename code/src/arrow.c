#include "z3D/z3D.h"
#include "arrow.h"
#include "input.h"
#include "settings.h"

typedef s32 (*NockArrowFunc)(Player* player, GlobalContext* globalCtx);
#define NockArrow ((NockArrowFunc)GAME_ADDR(0x33603C))
typedef void (*PlayAnimFunc)(void* p1, void* p2, s32 anim); // I'm not quite sure what these params are
#define LinkAnimation_PlayOnce ((PlayAnimFunc)GAME_ADDR(0x3604F0))
typedef void (*MagicResetFunc)(GlobalContext* globalCtx);
#define Magic_Reset ((MagicResetFunc)GAME_ADDR(0x34708C))

static const u8 arrowsSlots[]       = { SLOT_BOW, SLOT_ARROW_FIRE, SLOT_ARROW_ICE, SLOT_ARROW_LIGHT };
static const u8 arrowsItems[]       = { ITEM_BOW, ITEM_ARROW_FIRE, ITEM_ARROW_ICE, ITEM_ARROW_LIGHT };
static const u8 arrowsMagicPoints[] = { 0, 4, 4, 8 };

static u8 arrowPending = 0;

u8 CheckSwitchButton(void) {
    if (gSettingsContext.arrowSwitchButton == ARROWSWITCH_TOUCH)
        return rInputCtx.touchPressed && (rInputCtx.touchX > 0x40 && rInputCtx.touchX < 0x100) &&
               (rInputCtx.touchY > 0x25 && rInputCtx.touchY < 0xC8);
    else
        return (rInputCtx.pressed.val & (1 << (gSettingsContext.arrowSwitchButton + 4)));
}

void RestoreConsumedMagic(Actor* arrow, GlobalContext* globalCtx) {
    s16 type = arrow->params - 2;
    // If magic is being consumed, complete the consumption instantly
    if (gSaveContext.magicState == 1 || gSaveContext.magicState == 2) {
        gSaveContext.magic      = gSaveContext.magicTarget;
        gSaveContext.magicState = 3;
    }
    // Restore the magic used by the arrow
    gSaveContext.magic += arrowsMagicPoints[type];
    // Bound check on the magic capacity
    if (gSaveContext.magic > gSaveContext.magicMeterSize) {
        gSaveContext.magic = gSaveContext.magicMeterSize;
    }
    // If the magic arrow has never updated (because it's been swapped very quickly), it won't have spawned
    // the child actor for the magic effect, which is normally responsible for clearing the magic state.
    // So in this case we call the Magic_Reset function manually.
    if (arrow->params >= 3 && arrow->child == 0) {
        Magic_Reset(globalCtx);
    }
}

void ChangeArrow(Player* player, GlobalContext* globalCtx) {
    s8 currentType = player->heldItemActionParam - 8; // 0 normal, 1-2-3 magic
    s8 newType     = currentType;
    // Get the next arrow type that the player owns
    while (1) {
        if (++newType > 3) {
            newType = 0;
            break;
        }
        if (gSaveContext.items[arrowsSlots[newType]] == arrowsItems[newType])
            break;
    }

    // If the player only has one arrow type, swapping is useless
    if (newType == currentType)
        return;

    // If there is something in the bow slot, equip the new arrow type
    if (gSaveContext.items[SLOT_BOW] != 0xFF) {
        if (newType == 0) {
            gSaveContext.items[SLOT_BOW] = player->heldItemId = ITEM_BOW;
        } else {
            gSaveContext.items[SLOT_BOW] = player->heldItemId = ITEM_BOW_ARROW_FIRE + newType - 1;
        }

        player->itemActionParam = player->heldItemActionParam = newType + 8;
    }

    // If an arrow is currently nocked, it must be replaced
    Actor* held = player->heldActor;
    if (held != 0 && held->id == 0x16 && held->params >= 2 && held->params <= 5) {
        RestoreConsumedMagic(held, globalCtx);
        Actor_Kill(held);
        arrowPending = 1; // the arrow will spawn on the next global update cycle
        LinkAnimation_PlayOnce(((u8*)player) + 0x1764, globalCtx, 0x1B1); // Link raising the bow
    }
}

void Arrow_HandleSwap(Player* player, GlobalContext* globalCtx) {
    // Do nothing if Link is not holding a bow item or he's riding Epona
    if (player->heldItemActionParam < 8 || player->heldItemActionParam > 11 || (PLAYER->stateFlags1 & (1 << 23))) {
        arrowPending = 0;
        return;
    }

    if (arrowPending && (gSaveContext.magicState == 0)) {
        NockArrow(player, globalCtx);
        arrowPending = 0;
        return;
    }

    if (CheckSwitchButton()) {
        ChangeArrow(player, globalCtx);
    }
}
