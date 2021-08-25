#include "z3D/z3D.h"
#include "settings.h"

#include "gorons.h"

#define EnGo2_SetGetItem ((EnGo2_ActionFunc)0x133EBC)

void EnGo2_rBiggoronSetTextId(EnGo2* self) {
    Player* player = PLAYER;
    if (player->exchangeItemId == EXCH_ITEM_CLAIM_CHECK) {
        if (gSaveContext.biggoronTrades & BIGGORON_TRADED_CLAIM_CHECK) {
            self->actor.textId = 0x3003; // "I giiiive thissss to yoooou forrr a souvenirrrrr."
        } else {
            self->actor.textId = 0x305E; // "Yourrrr sworrrrd is my finest worrrrk!"
        }
    } else if (player->exchangeItemId == EXCH_ITEM_EYEDROPS) {
        self->actor.textId = 0x3059; // "Rrrrreally? You brrrrought the eye drops?"
    } else if (player->exchangeItemId == EXCH_ITEM_SWORD_BROKEN) {
        self->actor.textId = 0x3055; // "Please go get the eyedrrrrrrops..."
    } else {
        self->actor.textId = 0x3053; // "My Brotherrrr... Opened a new storrrre..."
    }
    player->actor.textId = self->actor.textId;
}

u16 EnGo2_rGetTextIdGoronDmtBiggoron(GlobalContext* globalCtx, EnGo2* self) {
    Player* player = PLAYER;

    switch (gSaveContext.items[SLOT_TRADE_ADULT]) {
        case ITEM_SWORD_BROKEN:
            player->exchangeItemId = EXCH_ITEM_SWORD_BROKEN;
            return 0x3053;
        case ITEM_EYEDROPS:
            player->exchangeItemId = EXCH_ITEM_EYEDROPS;
            return 0x3058;
        case ITEM_CLAIM_CHECK:
            player->exchangeItemId = EXCH_ITEM_CLAIM_CHECK;
            return (gSaveContext.biggoronTrades & BIGGORON_TRADED_CLAIM_CHECK) ? 0x3053 : 0x305E;
        default:
            player->exchangeItemId = EXCH_ITEM_NONE;
            return 0x3053;
    }
}

void EnGo2_AfterGiveItem(EnGo2* self, GlobalContext* globaCtx) {
    switch (self->getItemId) {
        case GI_CLAIM_CHECK:
            gSaveContext.biggoronTrades |= BIGGORON_TRADED_EYEDROPS;
            break;
        case GI_SWORD_BGS:
            gSaveContext.biggoronTrades |= BIGGORON_TRADED_CLAIM_CHECK;
            break;
        case GI_PERSCRIPTION:
            gSaveContext.biggoronTrades |= BIGGORON_TRADED_BROKEN_SWORD;
            break;
    }
    self->actionFunc = EnGo2_SetGetItem;
    EnGo2_SetGetItem(self, globaCtx);
}
