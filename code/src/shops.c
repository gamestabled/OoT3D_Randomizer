#include "z3D/z3D.h"
#include "settings.h"
#include "shops.h"
#include "objects.h"
#include "item_override.h"
#include "item_table.h"
#include "models.h"
#include <stddef.h>

static s32 rShopsanityPrices[32] = { 0 };

s32 Shop_CheckCanBuyBombchus(void) {
    const u32 slot = ItemSlots[ITEM_BOMBCHU];

    if (gSettingsContext.bombchusInLogic) {
        if (gSaveContext.items[slot] != ITEM_NONE) {
            return CANBUY_RESULT_0;
        } else {
            return CANBUY_RESULT_CANT_GET_NOW;
        }
    } else {
        if (((gSaveContext.upgrades >> 3) & 0x7) != 0) {
            return CANBUY_RESULT_0;
        } else {
            return CANBUY_RESULT_CANT_GET_NOW;
        }
    }
}

s32 numShopItemsLoaded = 0; // Used to determine params. Reset this to 0 in ossan_destroy or smth

#define EnGirlA_Init ((ActorFunc)0x1D7F20)
#define EnGirlA_Draw ((ActorFunc)0x210188)

#define EnGirlA_InitializeItemAction ((EnGirlAActionFunc)0x14D5C8)

void ShopsanityItem_BuyEventFunc(GlobalContext* globalCtx, EnGirlA* item) {
    ShopsanityItem* shopItem = (ShopsanityItem*)item;

    u32 itemBit = 1 << shopItem->shopItemPosition;

    if (gSaveContext.entranceIndex == 0x00B7) {
        gSaveContext.sceneFlags[SCENE_BAZAAR + SHOP_KAKARIKO_BAZAAR].unk |= itemBit;
    } else {
        gSaveContext.sceneFlags[gGlobalContext->sceneNum].unk |= itemBit;
    }

    Rupees_ChangeBy(-item->basePrice);
}

//Action IDs for respective items defined in item_table.c

u8 ShopsanityItem_IsBombs(u8 id) {
    return id == 0x8E || id == 0x02 || id == 0x8F || id == 0x90 || id == 0x91;
}

u8 ShopsanityItem_IsArrows(u8 id) {
    return id == 0x92 || id == 0x93 || id == 0x94;
}

u8 ShopsanityItem_IsSeeds(u8 id) {
    return id == 0x58 || id == 0x95;
}

u8 ShopsanityItem_IsBombchus(u8 id) {
    return id == 0x09 || id == 0x96 || id == 0x97;
}


s32 ShopsanityItem_CanBuy(GlobalContext* globalCtx, EnGirlA* item) {
    if (item->basePrice <= gSaveContext.rupees) { //Has enough rupees
        u8 id = ((ShopsanityItem*)item)->itemRow->actionId;
        if (ShopsanityItem_IsBombs(id)) {
            if ((gSaveContext.upgrades >> 3) & 0x7) { //Has bomb bag
                return CANBUY_RESULT_0;
            }
            return CANBUY_RESULT_CANT_GET_NOW;
        }
        else if (ShopsanityItem_IsArrows(id)) {
            if (gSaveContext.upgrades & 0x7) { //Has bow
                return CANBUY_RESULT_0;
            }
            return CANBUY_RESULT_CANT_GET_NOW;
        }
        else if (ShopsanityItem_IsSeeds(id)) {
            if ((gSaveContext.upgrades >> 14) & 0x7) { //Has slingshot
                return CANBUY_RESULT_0;
            }
            return CANBUY_RESULT_CANT_GET_NOW;
        }
        else if (ShopsanityItem_IsBombchus(id)) {
            return Shop_CheckCanBuyBombchus();
        }
        return CANBUY_RESULT_0;
    } else { //Not enough rupees
        return CANBUY_RESULT_NEED_RUPEES;
    }
}

//Transfer order of scene indices to order of indices defined elsewhere in the code
const u16 shopNumToIndex[8] = {4, 0, 7, 6, 1, 3, 2, 5};
u16 ShopsanityItem_GetIndex(ShopsanityItem* item) {
    //Get scene index
    u16 shopNum = gGlobalContext->sceneNum - SCENE_BAZAAR;
    if (gSaveContext.entranceIndex == 0x00B7) {
        shopNum = SHOP_KAKARIKO_BAZAAR;
    }
    shopNum = shopNumToIndex[shopNum]; //Transfer to the proper shop index
    u16 index = shopNum*8 + item->shopItemPosition; //Index first by shop num then by item within shop
    return 4*((index / 4) / 2) + index % 4; //Transform index- For more explanation see shops.cpp TransformShopIndex
}

s16 ShopsanityItem_GetPrice(ShopsanityItem* item) {
    return rShopsanityPrices[ShopsanityItem_GetIndex(item)]; //Get price from table 
}

s32 Shopsanity_CheckAlreadySold(ShopsanityItem* item) {
    u32 itemBit = 1 << item->shopItemPosition;

    if ((gSaveContext.entranceIndex == 0x00B7) && (gSaveContext.sceneFlags[SCENE_BAZAAR + SHOP_KAKARIKO_BAZAAR].unk & itemBit)) {
        item->super.actor.params = SI_SOLD_OUT;
        return 1;
    } else if (gSaveContext.sceneFlags[gGlobalContext->sceneNum].unk & itemBit) {
        item->super.actor.params = SI_SOLD_OUT;
        return 1;
    } else {
        return 0;
    }
}

void ShopsanityItem_1C4Func(GlobalContext* globalCtx, EnGirlA* item) {
    ShopsanityItem* shopItem = (ShopsanityItem*)item;

    if (Shopsanity_CheckAlreadySold(shopItem)) {
        item->actionFunc2 = EnGirlA_InitializeItemAction;
        item->actor.textId = EnGirlA_ShopItemEntries[item->actor.params].itemDescTextId;
    } else {
        item->isInvisible = 0;
        item->actor.draw = EnGirlA_Draw;
    }
}

void ShopsanityItem_InitializeItem(EnGirlA* item, GlobalContext* globalCtx) {
    ShopsanityItem* shopItem = (ShopsanityItem*)item;

    if (Object_IsLoaded(&globalCtx->objectCtx, item->objBankIndex) && ExtendedObject_IsLoaded(&globalCtx->objectCtx, shopItem->rObjBankIndex)) {
        EnGirlA_InitializeItemAction(item, globalCtx);
        DeleteModel_At(&item->model);
        DeleteModel_At(&item->model2);
        item->model = SkeletonAnimationModel_Spawn(&item->actor, globalCtx, shopItem->itemRow->objectId, shopItem->itemRow->objectModelIdx);
        item->unk_1C4 = ShopsanityItem_1C4Func;
        item->getItemId = shopItem->getItemId;
        item->canBuyFunc = ShopsanityItem_CanBuy;
        item->itemGiveFunc = NULL;
        item->buyEventFunc = ShopsanityItem_BuyEventFunc;
        item->basePrice = ShopsanityItem_GetPrice(shopItem);
        item->itemCount = 1;
        u16 index = ShopsanityItem_GetIndex(shopItem);
        item->actor.textId = 0x9200 + index*2;
        item->itemBuyPromptTextId = 0x9200 + index*2+1;
    }
}

void ShopsanityItem_InitializeRegularShopItem(EnGirlA* item, GlobalContext* globalCtx) {
    ShopsanityItem* shopItem = (ShopsanityItem*)item;
    ShopItemEntry* shopItemEntry = &EnGirlA_ShopItemEntries[shopItem->getItemId];

    if (Object_IsLoaded(&globalCtx->objectCtx, item->objBankIndex) && ExtendedObject_IsLoaded(&globalCtx->objectCtx, shopItem->rObjBankIndex)) {
        EnGirlA_InitializeItemAction(item, globalCtx);
        DeleteModel_At(&item->model);
        DeleteModel_At(&item->model2);
        item->model = SkeletonAnimationModel_Spawn(&item->actor, globalCtx, shopItemEntry->objId, shopItemEntry->objModelIdx);
        if (shopItemEntry->objModelIdx2 >= 0) {
            item->model2 = SkeletonAnimationModel_Spawn(&item->actor, globalCtx, shopItemEntry->objId, shopItemEntry->objModelIdx2);
        }
        item->getItemId = shopItemEntry->getItemId;
        item->canBuyFunc = shopItemEntry->canBuyFunc;
        item->itemGiveFunc = shopItemEntry->itemGiveFunc;
        item->buyEventFunc = shopItemEntry->buyEventFunc;
        if (item->getItemId == GI_TUNIC_GORON || item->getItemId == GI_TUNIC_ZORA) { //Override buyable functions for tunics
            item->canBuyFunc = ShopsanityItem_CanBuy;
        }
        item->basePrice = shopItemEntry->price;
        item->itemCount = shopItemEntry->count;
        item->actor.textId = shopItemEntry->itemDescTextId;
        item->itemBuyPromptTextId = shopItemEntry->itemBuyPromptTextId;
    }
}

void ShopsanityItem_Init(Actor* itemx, GlobalContext* globalCtx) {
    ShopsanityItem* item = (ShopsanityItem*)itemx;
    ItemOverride override;
    s32 objBankIndex;

    if (Object_GetIndex(&globalCtx->objectCtx, 0x148) < 0) {
        Object_Spawn(&globalCtx->objectCtx, 0x148);
    }

    item->shopItemPosition = numShopItemsLoaded;
    numShopItemsLoaded++;
    item->getItemId = 0x30 + item->shopItemPosition;
    if (gSaveContext.entranceIndex == 0x00B7) {
        item->getItemId += 8;
    }

    override = ItemOverride_Lookup(&item->super.actor, globalCtx->sceneNum, item->getItemId);
    if ((override.value.all == 0) || Shopsanity_CheckAlreadySold(item)) {
        EnGirlA_Init(itemx, globalCtx);
    } else if (override.value.player == 0xFF) { //Special way to detect regular shop items
        EnGirlA_Init(itemx, globalCtx);

        item->super.actionFunc2 = ShopsanityItem_InitializeRegularShopItem;
        item->getItemId = override.value.itemId;

        objBankIndex = ExtendedObject_GetIndex(&globalCtx->objectCtx, EnGirlA_ShopItemEntries[override.value.itemId].objId);
        if (objBankIndex < 0) {
            objBankIndex = ExtendedObject_Spawn(&globalCtx->objectCtx, EnGirlA_ShopItemEntries[override.value.itemId].objId);
        }
        item->rObjBankIndex = objBankIndex;
    } else {
        item->super.objBankIndex = Object_GetIndex(&globalCtx->objectCtx, EnGirlA_ShopItemEntries[item->super.actor.params].objId);
        item->super.unk_1FC = 1.0f;

        item->super.actionFunc2 = ShopsanityItem_InitializeItem;
        u16 id = override.value.itemId;
        //For shop ammo items, we don't want to make them turn into blupees without the appropriate capacity, instead just disallow purchase in the canbuy check
        if (!(id == GI_BOMBS_5 || id == GI_BOMBS_10 || id == GI_BOMBS_20 || id == GI_ARROWS_SMALL || id == GI_ARROWS_MEDIUM || id == GI_ARROWS_LARGE || id == GI_SEEDS_5 || id == GI_SEEDS_30)) {
            id = ItemTable_ResolveUpgrades(override.value.itemId);
        }
        item->itemRow = ItemTable_GetItemRow(id);
        
        objBankIndex = ExtendedObject_GetIndex(&globalCtx->objectCtx, item->itemRow->objectId);
        if (objBankIndex < 0) {
            objBankIndex = ExtendedObject_Spawn(&globalCtx->objectCtx, item->itemRow->objectId);
        }
        item->rObjBankIndex = objBankIndex;
    }
}

void EnOssan_rDestroy(Actor* shopkeeperx, GlobalContext* globalCtx) {
    numShopItemsLoaded = 0;
}
