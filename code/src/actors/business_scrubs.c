#include "business_scrubs.h"
#include "settings.h"
#include "multiplayer.h"
#include "actor.h"

void EnDns_Update(Actor* thisx, GlobalContext* globalCtx);
void EnShopnuts_Init(Actor* thisx, GlobalContext* globalCtx);

static u32 EnDns_rCanBuy(EnDns* scrub);
static void EnDns_rPay(EnDns* scrub);
static u32 EnDns_rCanBuyExtraShield(EnDns* scrub);

extern DnsItemEntry* EnDns_ItemEntries[];

s16 rScrubRandomItemPrices[11] = { 0 };

void BusinessScrubs_Init(void) {
    if (gSettingsContext.scrubsanity != SCRUBSANITY_OFF) {
        for (s32 scrubType = 0; scrubType < DNS_TYPE_MAX; scrubType++) {
            EnDns_ItemEntries[scrubType]->canBuy  = EnDns_rCanBuy;
            EnDns_ItemEntries[scrubType]->payment = EnDns_rPay;
        }
    } else if (gSettingsContext.extraShields == EXTRASHIELDS_ALWAYS) {
        EnDns_ItemEntries[DNS_TYPE_DEKU_SHIELD]->canBuy = EnDns_rCanBuyExtraShield;
    }
}

static u32 EnDns_rCanBuy(EnDns* scrub) {
    s16 price;

    if (gSettingsContext.scrubsanity == SCRUBSANITY_AFFORDABLE) {
        price = 10;
    } else if (gSettingsContext.scrubsanity == SCRUBSANITY_RANDOM_PRICES) {
        price = rScrubRandomItemPrices[scrub->actor.params];
    } else { // SCRUBSANITY_EXPENSIVE
        price = scrub->dnsItemEntry->itemPrice;
    }

    if (gSaveContext.rupees < price) {
        return DNS_CANBUY_RESULT_NEED_RUPEES;
    }
    return DNS_CANBUY_RESULT_SUCCESS;
}

static u32 EnDns_rCanBuyExtraShield(EnDns* scrub) {
    // Allow buying Deku Shield even when already owned.
    if (gSaveContext.rupees < scrub->dnsItemEntry->itemPrice) {
        return DNS_CANBUY_RESULT_NEED_RUPEES;
    }
    return DNS_CANBUY_RESULT_SUCCESS;
}

static void EnDns_rPay(EnDns* scrub) {
    u32 sceneNum = gGlobalContext->sceneNum;
    u32 bitMask  = (0x1 << (scrub->actor.params + 1));

    // Grotto scene
    if (sceneNum == 0x3E) {
        // Use an otherwise irrelevant scene
        sceneNum = (gSaveContext.respawn[RESPAWN_MODE_RETURN].data - 0xD6);
    }

    gSaveContext.sceneFlags[sceneNum].unk |= bitMask;

    if (gSettingsContext.scrubsanity == SCRUBSANITY_AFFORDABLE) {
        Rupees_ChangeBy(-10);
    } else if (gSettingsContext.scrubsanity == SCRUBSANITY_RANDOM_PRICES) {
        Rupees_ChangeBy(-rScrubRandomItemPrices[scrub->actor.params]);
    } else {
        Rupees_ChangeBy(-scrub->dnsItemEntry->itemPrice);
    }
}

s32 EnShopnnuts_rCheckFlags(EnShopnuts* scrub) {
    if (gSettingsContext.scrubsanity == SCRUBSANITY_OFF) {
        return -1; // Use vanilla checks.
    }

    u32 sceneNum = gGlobalContext->sceneNum;
    u32 bitMask  = (0x1 << (scrub->actor.params + 1));

    // Grotto scene
    if (sceneNum == 0x3E) {
        // Use an otherwise irrelevant scene
        sceneNum = (gSaveContext.respawn[RESPAWN_MODE_RETURN].data - 0xD6);
    }

    return ((gSaveContext.sceneFlags[sceneNum].unk & bitMask) != 0);
}

void EnShopnuts_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnShopnuts* scrub = (EnShopnuts*)thisx;

    if ((gSettingsContext.scrubsanity != SCRUBSANITY_OFF) && (scrub->actor.params == 0x6)) {
        scrub->actor.params = 0x03;
    }
    EnShopnuts_Init(&scrub->actor, globalCtx);
}

void EnDns_Talk(EnDns* this, GlobalContext* globalCtx);
void EnDns_SetupSale(EnDns* this, GlobalContext* globalCtx);
void EnDns_Sale(EnDns* this, GlobalContext* globalCtx);
void EnDns_SetupBurrow(EnDns* this, GlobalContext* globalCtx);
void EnDns_Burrow(EnDns* this, GlobalContext* globalCtx);
void EnDns_PostBurrow(EnDns* this, GlobalContext* globalCtx);

u32 EnDns_ChangeAnim(EnDns* globalCtx, u8 arg1);

void EnDns_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnDns* scrub = (EnDns*)thisx;

    EnDnsActionFunc prev_action_fn = scrub->action_fn;

    EnDns_Update(&scrub->actor, globalCtx);

    // Skip scrubs with repeatable purchases
    if (gSettingsContext.scrubsanity == SCRUBSANITY_OFF && scrub->actor.params != DNS_TYPE_HEART_PIECE &&
        scrub->actor.params != DNS_TYPE_DEKU_STICK_UPGRADE && scrub->actor.params != DNS_TYPE_DEKU_NUT_UPGRADE) {
        return;
    }

    if (prev_action_fn == EnDns_Talk && (scrub->action_fn == EnDns_SetupSale || scrub->action_fn == EnDns_Sale ||
                                         scrub->action_fn == EnDns_SetupBurrow)) {
        Multiplayer_Send_ActorUpdate(thisx, NULL, 0);
    }
}

void EnDns_StartBurrow(EnDns* this) {
    if (this->action_fn == EnDns_SetupSale || this->action_fn == EnDns_Sale || this->action_fn == EnDns_SetupBurrow ||
        this->action_fn == EnDns_Burrow || this->action_fn == EnDns_PostBurrow) {
        return;
    }
    this->drop_collectible  = 0;
    this->maintain_collider = 0;
    this->actor.flags &= ~ACTOR_FLAG_ATTENTION_ENABLED;
    EnDns_ChangeAnim(this, 1);
    this->action_fn = EnDns_Burrow;
}

void EnShopnuts_ReinitModels(EnShopnuts* this) {
    Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);
}
