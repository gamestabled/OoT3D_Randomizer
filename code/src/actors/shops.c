#include "z3D/z3D.h"
#include "settings.h"
#include "shops.h"
#include "objects.h"
#include "custom_models.h"
#include "item_override.h"
#include "item_table.h"
#include "models.h"
#include "entrance.h"
#include "multiplayer.h"
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

#define EnGirlA_Init ((ActorFunc)GAME_ADDR(0x1D7F20))
#define EnGirlA_Draw ((ActorFunc)GAME_ADDR(0x210188))

#define EnGirlA_InitializeItemAction ((EnGirlAActionFunc)GAME_ADDR(0x14D5C8))

void ShopsanityItem_Draw(Actor* itemx, GlobalContext* globalCtx);

// Checks for if item is of a certain type

u8 ShopsanityItem_IsBombs(u8 id) {
    return id == ITEM_BOMB || id == ITEM_BOMBS_5 || id == ITEM_BOMBS_10 || id == ITEM_BOMBS_20 || id == ITEM_BOMBS_30;
}

u8 ShopsanityItem_IsArrows(u8 id) {
    return id == ITEM_ARROWS_SMALL || id == ITEM_ARROWS_MEDIUM || id == ITEM_ARROWS_LARGE;
}

u8 ShopsanityItem_IsSeeds(u8 id) {
    return id == ITEM_SEEDS || id == ITEM_SEEDS_30;
}

u8 ShopsanityItem_IsBombchus(u8 id) {
    return id == ITEM_BOMBCHU || id == ITEM_BOMBCHUS_5 || id == ITEM_BOMBCHUS_20;
}

u8 ShopsanityItem_IsNuts(u8 id) {
    return id == ITEM_NUT || id == ITEM_NUTS_5 || id == ITEM_NUTS_10;
}

u8 ShopsanityItem_IsSticks(u8 id) {
    return id == ITEM_STICK || id == ITEM_STICKS_5 || id == ITEM_STICKS_10;
}

// Transfer order of scene indices to order of indices defined elsewhere in the code
const u16 shopNumToIndex[8] = { 4, 0, 7, 6, 1, 3, 2, 5 };
u16 ShopsanityItem_GetIndex(ShopsanityItem* item) {
    // Get scene index
    u16 shopNum = gGlobalContext->sceneNum - SCENE_BAZAAR;
    if (Entrance_SceneAndSpawnAre(0x2C, 0x00)) { // kak bazaar, index 00B7 in the entrance table
        shopNum = SHOP_KAKARIKO_BAZAAR;
    }
    shopNum   = shopNumToIndex[shopNum];              // Transfer to the proper shop index
    u16 index = shopNum * 8 + item->shopItemPosition; // Index first by shop num then by item within shop
    return 4 * ((index / 4) / 2) + index % 4; // Transform index- For more explanation see shops.cpp TransformShopIndex
}

void ShopsanityItem_BuyEventFunc(GlobalContext* globalCtx, EnGirlA* item) {
    ShopsanityItem* shopItem = (ShopsanityItem*)item;

    u32 itemBit = 1 << shopItem->shopItemPosition;

    u8 id = shopItem->itemRow->actionId;
    // Make it so ammo does not sell out
    if (!(ShopsanityItem_IsBombs(id) || ShopsanityItem_IsArrows(id) || ShopsanityItem_IsSeeds(id) ||
          ShopsanityItem_IsBombchus(id) || ShopsanityItem_IsNuts(id) || ShopsanityItem_IsSticks(id))) {
        if (Entrance_SceneAndSpawnAre(0x2C, 0x00)) { // kak bazaar, index 00B7 in the entrance table
            gSaveContext.sceneFlags[SCENE_BAZAAR + SHOP_KAKARIKO_BAZAAR].unk |= itemBit;
        } else {
            gSaveContext.sceneFlags[gGlobalContext->sceneNum].unk |= itemBit;
        }
        u16 index = ShopsanityItem_GetIndex(shopItem);
        Multiplayer_Send_ActorUpdate((Actor*)shopItem, &index, sizeof(u16));
    }

    Rupees_ChangeBy(-item->basePrice);
}

s32 ShopsanityItem_CanBuy(GlobalContext* globalCtx, EnGirlA* item) {
    if (item->basePrice <= gSaveContext.rupees) { // Has enough rupees
        // Tunics are non-ShopsanityItem objects passed to this function, so don't check those
        if (!(item->getItemId == GI_TUNIC_GORON || item->getItemId == GI_TUNIC_ZORA)) {
            u8 id = ((ShopsanityItem*)item)->itemRow->actionId;
            if (ShopsanityItem_IsBombs(id)) {
                if ((gSaveContext.upgrades >> 3) & 0x7) { // Has bomb bag
                    return CANBUY_RESULT_0;
                }
                return CANBUY_RESULT_CANT_GET_NOW;
            } else if (ShopsanityItem_IsArrows(id)) {
                if (gSaveContext.upgrades & 0x7) { // Has bow
                    return CANBUY_RESULT_0;
                }
                return CANBUY_RESULT_CANT_GET_NOW;
            } else if (ShopsanityItem_IsSeeds(id)) {
                if ((gSaveContext.upgrades >> 14) & 0x7) { // Has slingshot
                    return CANBUY_RESULT_0;
                }
                return CANBUY_RESULT_CANT_GET_NOW;
            }
        }
        // If it is a non-shopsanity tunic, check that it is not already owned
        else if (item->getItemId == GI_TUNIC_GORON && gSaveContext.equipment & 0x0200) {
            return CANBUY_RESULT_CANT_GET_NOW;
        } else if (item->getItemId == GI_TUNIC_ZORA && gSaveContext.equipment & 0x0400) {
            return CANBUY_RESULT_CANT_GET_NOW;
        }
        return CANBUY_RESULT_0;
    } else { // Not enough rupees
        return CANBUY_RESULT_NEED_RUPEES;
    }
}

s16 ShopsanityItem_GetPrice(ShopsanityItem* item) {
    return rShopsanityPrices[ShopsanityItem_GetIndex(item)]; // Get price from table
}

s32 Shopsanity_CheckAlreadySold(ShopsanityItem* item) {
    u32 itemBit = 1 << item->shopItemPosition;

    // For Bombchu Shop with vanilla logic, check the base game flags.
    u32 vanillaSoldOut = (gSettingsContext.logic == LOGIC_VANILLA) && Entrance_SceneAndSpawnAre(0x32, 0x00) &&
                         (gSaveContext.itemGetInf[0] & (1 << (3 + item->super.actor.params - SI_BOMBCHU_10_1)));

    if (vanillaSoldOut ||
        (Entrance_SceneAndSpawnAre(0x2C, 0x00) &&
         gSaveContext.sceneFlags[SCENE_BAZAAR + SHOP_KAKARIKO_BAZAAR].unk & itemBit) ||
        (!Entrance_SceneAndSpawnAre(0x2C, 0x00) && gSaveContext.sceneFlags[gGlobalContext->sceneNum].unk & itemBit)) {
        item->super.actor.params = SI_SOLD_OUT;
        return 1;
    } else {
        return 0;
    }
}

void ShopsanityItem_1C4Func(GlobalContext* globalCtx, EnGirlA* item) {
    ShopsanityItem* shopItem = (ShopsanityItem*)item;

    if (Shopsanity_CheckAlreadySold(shopItem)) {
        item->actionFunc2  = EnGirlA_InitializeItemAction;
        item->actor.textId = EnGirlA_ShopItemEntries[item->actor.params].itemDescTextId;
    } else {
        item->isInvisible = 0;
        item->actor.draw  = EnGirlA_Draw;
    }
}

void ShopsanityItem_ResetModels(ShopsanityItem* shopItem, GlobalContext* globalCtx, s16 objectId, s16 objModelIdx,
                                s16 objModelIdx2, s16 cmabIdx, s16 cmabIdx2, s16 special) {
    EnGirlA* item = &shopItem->super;

    DeleteModel_At(&item->model);
    DeleteModel_At(&item->model2);

    // edit the cmbs for custom models
    ObjectEntry* obj = Object_FindEntryOrSpawn(objectId);
    CustomModels_EditItemCMB(obj->zarInfo.buf, objectId, special);

    item->model = SkeletonAnimationModel_Spawn(&item->actor, globalCtx, objectId, objModelIdx);
    if (objectId == 0x017F) { // Set the mesh for rupees
        SkeletonAnimationModel_SetMesh(item->model, special);
    }

    CustomModels_ApplyItemCMAB(item->model, objectId, special);

    if (cmabIdx >= 0) {
        void* cmabMan = Object_GetCMABByIndex(objectId, cmabIdx);
        TexAnim_Spawn(item->model->unk_0C, cmabMan);
        item->model->unk_0C->animSpeed = 2.0f;
        item->model->unk_0C->animMode  = 1;
    }

    if (objModelIdx2 >= 0) {
        item->model2 = SkeletonAnimationModel_Spawn(&item->actor, globalCtx, objectId, objModelIdx2);
        if (cmabIdx2 >= 0) {
            void* cmabMan = Object_GetCMABByIndex(objectId, cmabIdx2);
            TexAnim_Spawn(item->model2->unk_0C, cmabMan);
            item->model2->unk_0C->animSpeed = 2.0f;
            item->model2->unk_0C->animMode  = 1;
        }
    }
}

void ShopsanityItem_InitializeItem(EnGirlA* item, GlobalContext* globalCtx) {
    ShopsanityItem* shopItem = (ShopsanityItem*)item;

    if (Object_IsLoaded(&globalCtx->objectCtx, item->objectSlot) &&
        Object_IsLoaded(&globalCtx->objectCtx, shopItem->rObjectSlot)) {
        EnGirlA_InitializeItemAction(item, globalCtx);
        ShopsanityItem_ResetModels(shopItem, globalCtx, shopItem->itemRow->objectId, shopItem->itemRow->objectModelIdx,
                                   shopItem->itemRow->objectModelIdx2, shopItem->itemRow->cmabIndex,
                                   shopItem->itemRow->cmabIndex2, shopItem->itemRow->special);
        item->unk_1C4             = ShopsanityItem_1C4Func;
        item->getItemId           = shopItem->getItemId;
        item->canBuyFunc          = ShopsanityItem_CanBuy;
        item->itemGiveFunc        = NULL;
        item->buyEventFunc        = ShopsanityItem_BuyEventFunc;
        item->basePrice           = ShopsanityItem_GetPrice(shopItem);
        item->itemCount           = 1;
        u16 index                 = ShopsanityItem_GetIndex(shopItem);
        item->actor.textId        = 0x9200 + index * 2;
        item->itemBuyPromptTextId = 0x9200 + index * 2 + 1;
        item->actor.draw          = ShopsanityItem_Draw;
    }
}

void ShopsanityItem_InitializeRegularShopItem(EnGirlA* item, GlobalContext* globalCtx) {
    ShopsanityItem* shopItem     = (ShopsanityItem*)item;
    ShopItemEntry* shopItemEntry = &EnGirlA_ShopItemEntries[shopItem->getItemId];

    if (Object_IsLoaded(&globalCtx->objectCtx, item->objectSlot) &&
        Object_IsLoaded(&globalCtx->objectCtx, shopItem->rObjectSlot)) {
        EnGirlA_InitializeItemAction(item, globalCtx);
        ShopsanityItem_ResetModels(shopItem, globalCtx, shopItemEntry->objId, shopItemEntry->objModelIdx,
                                   shopItemEntry->objModelIdx2, shopItemEntry->cmabIndex, shopItemEntry->cmabIndex2,
                                   0xFF);
        item->getItemId  = shopItemEntry->getItemId;
        item->canBuyFunc = shopItemEntry->canBuyFunc;
        if (item->getItemId == GI_TUNIC_GORON ||
            item->getItemId == GI_TUNIC_ZORA) { // Override buyable functions for tunics
            item->canBuyFunc = ShopsanityItem_CanBuy;
        }
        item->itemGiveFunc        = shopItemEntry->itemGiveFunc;
        item->buyEventFunc        = shopItemEntry->buyEventFunc;
        item->basePrice           = shopItemEntry->price;
        item->itemCount           = shopItemEntry->count;
        item->actor.textId        = shopItemEntry->itemDescTextId;
        item->itemBuyPromptTextId = shopItemEntry->itemBuyPromptTextId;

        // EnGirlA_Draw checks the params to make the blue flame rotate
        if (item->getItemId == GI_BLUE_FIRE) {
            item->actor.params = SI_BLUE_FIRE;
        } else if (item->actor.params == SI_BLUE_FIRE) {
            item->actor.params = 0;
        }
    }
}

void ShopsanityItem_Init(Actor* itemx, GlobalContext* globalCtx) {
    ShopsanityItem* item = (ShopsanityItem*)itemx;
    ItemOverride override;

    Object_FindEntryOrSpawn(0x148);
    CustomModel_Update();

    item->shopItemPosition = numShopItemsLoaded;
    numShopItemsLoaded++;
    item->getItemId = 0x30 + item->shopItemPosition;
    if (Entrance_SceneAndSpawnAre(0x2C, 0x00)) {
        item->getItemId += 8;
    }

    override = ItemOverride_Lookup(&item->super.actor, globalCtx->sceneNum, item->getItemId);
    if ((override.value.all == 0) || Shopsanity_CheckAlreadySold(item)) {
        EnGirlA_Init(itemx, globalCtx);
    } else if (override.value.player == 0xFF) { // Special way to detect regular shop items
        EnGirlA_Init(itemx, globalCtx);

        item->super.actionFunc2 = ShopsanityItem_InitializeRegularShopItem;
        item->getItemId         = override.value.itemId;
        item->rObjectSlot       = Object_FindSlotOrSpawn(EnGirlA_ShopItemEntries[override.value.itemId].objId);
    } else {
        item->super.objectSlot =
            Object_GetSlot(&globalCtx->objectCtx, EnGirlA_ShopItemEntries[item->super.actor.params].objId);
        item->super.unk_1FC = 1.0f;

        item->super.actionFunc2 = ShopsanityItem_InitializeItem;
        u16 id                  = override.value.itemId;
        // Ice trap models
        if (override.value.looksLikeItemId) {
            id = override.value.looksLikeItemId;
        }
        // For shop ammo items, we don't want to make them turn into blupees without the appropriate capacity,
        // instead just disallow purchase in the canbuy check
        if (!(id == GI_BOMBS_5 || id == GI_BOMBS_10 || id == GI_BOMBS_20 || id == GI_ARROWS_SMALL ||
              id == GI_ARROWS_MEDIUM || id == GI_ARROWS_LARGE || id == GI_SEEDS_5 || id == GI_SEEDS_30)) {
            id = ItemTable_ResolveUpgrades(id);
        }
        item->itemRow     = ItemTable_GetItemRow(id);
        item->rObjectSlot = Object_FindSlotOrSpawn(item->itemRow->objectId);
    }
}

void ShopsanityItem_Draw(Actor* itemx, GlobalContext* globalCtx) {
    ShopsanityItem* item  = (ShopsanityItem*)itemx;
    ItemOverride override = ItemOverride_Lookup(&item->super.actor, globalCtx->sceneNum, item->getItemId);

    u16 itemId = override.value.looksLikeItemId ? override.value.looksLikeItemId : override.value.itemId;
    CustomModels_UpdateMatrix(&item->super.actor.modelMtx, ItemTable_GetItemRow(itemId)->objectId);

    EnGirlA_Draw(itemx, globalCtx);
}

void ShopsanityItem_SellOut(Actor* itemx, u16 index) {
    ShopsanityItem* item = (ShopsanityItem*)itemx;

    if (ShopsanityItem_GetIndex(item) != index) {
        return;
    }

    item->super.actor.params = SI_SOLD_OUT;
    item->super.actionFunc2  = EnGirlA_InitializeItemAction;
    item->super.actor.textId = EnGirlA_ShopItemEntries[SI_SOLD_OUT].itemDescTextId;
}

void EnOssan_rDestroy(Actor* shopkeeperx, GlobalContext* globalCtx) {
    numShopItemsLoaded = 0;
}
