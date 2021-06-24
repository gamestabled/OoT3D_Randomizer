#include "z3D/z3D.h"
#include "z3D/actors/z_en_dns.h"
#include "z3D/actors/z_en_shopnuts.h"
#include "settings.h"

#define EnShopnuts_Init_addr 0x22ED2C
#define EnShopnuts_Init ((ActorFunc)EnShopnuts_Init_addr)

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

#define Vanilla_DnsItemEntries_addr 0x522384
#define VanillaScrubTable ((DnsItemEntry**)Vanilla_DnsItemEntries_addr)

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
    u32 bitMask = (0x1 << (scrub->actor.params + 1));

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
    u32 bitMask = (0x1 << (scrub->actor.params + 1));

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
