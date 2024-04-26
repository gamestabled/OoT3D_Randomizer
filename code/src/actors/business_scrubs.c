#include "business_scrubs.h"
#include "settings.h"
#include "multiplayer.h"

#define EnDns_Update ((ActorFunc)GAME_ADDR(0x1D67CC))

#define EnShopnuts_Init ((ActorFunc)GAME_ADDR(0x22ED2C))

u32 EnDns_rPurchaseableCheck(EnDns* scrub);
void EnDns_rSetRupeesAndFlags(EnDns* scrub);
void EnDns_rSetRupeesAndFlagsIfScrubsanity(EnDns* scrub);

static const DnsItemEntry Scrub_0 = { 20, 5, 0x30, EnDns_rPurchaseableCheck, EnDns_rSetRupeesAndFlagsIfScrubsanity };
static const DnsItemEntry Scrub_1 = { 15, 1, 0x31, EnDns_rPurchaseableCheck, EnDns_rSetRupeesAndFlagsIfScrubsanity };
static const DnsItemEntry Scrub_2 = { 10, 1, 0x3E, EnDns_rPurchaseableCheck, EnDns_rSetRupeesAndFlags };
static const DnsItemEntry Scrub_3 = { 40, 30, 0x33, EnDns_rPurchaseableCheck, EnDns_rSetRupeesAndFlagsIfScrubsanity };
static const DnsItemEntry Scrub_4 = { 50, 1, 0x34, EnDns_rPurchaseableCheck, EnDns_rSetRupeesAndFlagsIfScrubsanity };
static const DnsItemEntry Scrub_5 = { 40, 5, 0x37, EnDns_rPurchaseableCheck, EnDns_rSetRupeesAndFlagsIfScrubsanity };
static const DnsItemEntry Scrub_6 = { 70, 20, 0x38, EnDns_rPurchaseableCheck, EnDns_rSetRupeesAndFlagsIfScrubsanity };
static const DnsItemEntry Scrub_7 = { 40, 1, 0x39, EnDns_rPurchaseableCheck, EnDns_rSetRupeesAndFlagsIfScrubsanity };
static const DnsItemEntry Scrub_8 = { 40, 1, 0x3A, EnDns_rPurchaseableCheck, EnDns_rSetRupeesAndFlagsIfScrubsanity };
static const DnsItemEntry Scrub_9 = { 40, 1, 0x77, EnDns_rPurchaseableCheck, EnDns_rSetRupeesAndFlags };
static const DnsItemEntry Scrub_A = { 40, 1, 0x79, EnDns_rPurchaseableCheck, EnDns_rSetRupeesAndFlags };

const DnsItemEntry* rScrubTable[] = { &Scrub_0, &Scrub_1, &Scrub_2, &Scrub_3, &Scrub_4, &Scrub_5,
                                      &Scrub_6, &Scrub_7, &Scrub_8, &Scrub_9, &Scrub_A };

#define VanillaScrubTable ((DnsItemEntry**)GAME_ADDR(0x522384))

s16 rScrubRandomItemPrices[11] = { 0 };

u32 EnDns_rPurchaseableCheck(EnDns* scrub) {
    s16 price;

    if (gSettingsContext.scrubsanity == SCRUBSANITY_OFF) {
        return VanillaScrubTable[scrub->actor.params]->purchaseableCheck(scrub);
    } else if (gSettingsContext.scrubsanity == SCRUBSANITY_AFFORDABLE) {
        price = 10;
    } else if (gSettingsContext.scrubsanity == SCRUBSANITY_RANDOM_PRICES) {
        price = rScrubRandomItemPrices[scrub->actor.params];
    } else {
        price = scrub->dnsItemEntry->itemPrice;
    }

    if (gSaveContext.rupees < price) {
        return 0;
    }
    return 4;
}

void EnDns_rSetRupees(EnDns* scrub) {
    if (gSettingsContext.scrubsanity == SCRUBSANITY_AFFORDABLE) {
        Rupees_ChangeBy(-10);
    } else if (gSettingsContext.scrubsanity == SCRUBSANITY_RANDOM_PRICES) {
        Rupees_ChangeBy(-rScrubRandomItemPrices[scrub->actor.params]);
    } else {
        Rupees_ChangeBy(-scrub->dnsItemEntry->itemPrice);
    }
}

void EnDns_rSetRupeesAndFlags(EnDns* scrub) {
    u32 sceneNum = gGlobalContext->sceneNum;
    u32 bitMask  = (0x1 << (scrub->actor.params + 1));

    // Grotto scene
    if (sceneNum == 0x3E) {
        // Use an otherwise irrelevant scene
        sceneNum = (gSaveContext.respawn[RESPAWN_MODE_RETURN].data - 0xD6);
    }

    gSaveContext.sceneFlags[sceneNum].unk |= bitMask;
    EnDns_rSetRupees(scrub);
}

void EnDns_rSetRupeesAndFlagsIfScrubsanity(EnDns* scrub) {
    if (gSettingsContext.scrubsanity == SCRUBSANITY_OFF) {
        EnDns_rSetRupees(scrub);
    } else {
        EnDns_rSetRupeesAndFlags(scrub);
    }
}

u32 EnShopnnuts_rCheckFlags(EnShopnuts* scrub) {
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

#define EnDns_Talk (void*)GAME_ADDR(0x161960)
#define FUN_00161828 (void*)GAME_ADDR(0x161828)
#define FUN_003CE92C (void*)GAME_ADDR(0x3CE92C)
#define FUN_00100434 (void*)GAME_ADDR(0x100434)
#define EnDns_SetupBurrow (void*)GAME_ADDR(0x3C3C04)
#define EnDns_Burrow (void*)GAME_ADDR(0x3CEA64)

typedef u32 (*EnDns_ChangeAnim_proc)(EnDns* globalCtx, u8 arg1);
#define EnDns_ChangeAnim ((EnDns_ChangeAnim_proc)GAME_ADDR(0x37693C))

void EnDns_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnDns* scrub = (EnDns*)thisx;

    void* prev_action_fn = scrub->action_fn;

    EnDns_Update(&scrub->actor, globalCtx);

    // Skip scrubs with repeatable purchases
    if (gSettingsContext.scrubsanity == SCRUBSANITY_OFF && scrub->actor.params != 0x2 && scrub->actor.params != 0x9 &&
        scrub->actor.params != 0xA) {
        return;
    }

    if (prev_action_fn == EnDns_Talk &&
        (scrub->action_fn == FUN_00161828 || scrub->action_fn == FUN_003CE92C || scrub->action_fn == FUN_00100434)) {
        Multiplayer_Send_ActorUpdate(thisx, NULL, 0);
    }
}

void EnDns_StartBurrow(EnDns* thisx) {
    if (thisx->action_fn == FUN_00161828 || thisx->action_fn == FUN_003CE92C || thisx->action_fn == FUN_00100434 ||
        thisx->action_fn == EnDns_SetupBurrow || thisx->action_fn == EnDns_Burrow) {
        return;
    }
    thisx->drop_collectible  = 0;
    thisx->maintain_collider = 0;
    thisx->actor.flags &= ~(0x1);
    EnDns_ChangeAnim(thisx, 1);
    thisx->action_fn = EnDns_SetupBurrow;
}
