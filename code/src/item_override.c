#include "item_override.h"
#include "rHeap.h"
#include "item_table.h"
#include "icetrap.h"
#include "settings.h"
#include "custom_models.h"
#include "objects.h"
#include <stddef.h>
void svcBreak(u32 breakReason); //TODO: remove

#include "z3D/z3D.h"
#include "z3D/actors/z_en_box.h"
#include "z3D/actors/z_en_item00.h"

static ItemOverride rItemOverrides[512] = { 0 };
static s32 rItemOverrides_Count = 0;

static ItemOverride rPendingOverrideQueue[3] = { 0 };
static Actor* rDummyActor = NULL;

static ItemOverride rActiveItemOverride = { 0 };
ItemRow* rActiveItemRow = NULL;
// Split active_item_row into variables for convenience in ASM
u32 rActiveItemActionId = 0;
u32 rActiveItemTextId = 0;
u32 rActiveItemObjectId = 0;
u32 rActiveItemGraphicId = 0;
u32 rActiveItemFastChest = 0;

static u8 rSatisfiedPendingFrames = 0;

void ItemOverride_Init(void) {
    while(rItemOverrides[rItemOverrides_Count].key.all != 0) {
        rItemOverrides_Count++;
    }

    // Create an actor satisfying the minimum requirements to give the player an item
    rDummyActor = rHeap_Alloc(sizeof(Actor));
    rDummyActor->update = (void*)1;
    rDummyActor->parent = NULL;

    // Enable items by age as determined by settings
    if (gSettingsContext.stickAsAdult) {
        gItemUsabilityTable[ITEM_STICK] = 0x09;
    }
    if (gSettingsContext.boomerangAsAdult) {
        gItemUsabilityTable[ITEM_BOOMERANG] = 0x09;
    }
    if (gSettingsContext.hammerAsChild) {
        gItemUsabilityTable[ITEM_HAMMER] = 0x09;
    }
}

static ItemOverride_Key ItemOverride_GetSearchKey(Actor* actor, u8 scene, u8 itemId) {
    if (actor->id == 0x0A) { // Chest
        // Don't override WINNER purple rupee in the chest minigame scene
        if (scene == 0x10) {
            u32 chestItemId = (actor->params >> 5) & 0x7F;
            if (chestItemId == 0x75) {
                return (ItemOverride_Key){ .all = 0 };
            }
        }

        return (ItemOverride_Key){
            .scene = scene,
            .type = OVR_CHEST,
            .flag = actor->params & 0x1F,
        };
    } else if (actor->id == 0x15) { // Collectible
        // Only override heart pieces and keys
        u32 collectibleType = actor->params & 0xFF;
        if (collectibleType != 0x06 && collectibleType != 0x11) {
            return (ItemOverride_Key){ .all = 0 };
        }

        return (ItemOverride_Key){
            .scene = scene,
            .type = OVR_COLLECTABLE,
            .flag = ((EnItem00*)actor)->collectibleFlag,
        };
    } else if (actor->id == 0x19C) { // Gold Skulltula Token
        return (ItemOverride_Key){
            .scene = (actor->params >> 8) & 0x1F,
            .type = OVR_SKULL,
            .flag = actor->params & 0xFF,
        };
    } else if (scene == 0x3E && actor->id == 0x11A) { // Grotto Salesman
        return (ItemOverride_Key){
            .scene = gSaveContext.respawn[RESPAWN_MODE_RETURN].data,
            .type = OVR_GROTTO_SCRUB,
            .flag = itemId,
        };
    } else {
        return (ItemOverride_Key){
            .scene = scene,
            .type = OVR_BASE_ITEM,
            .flag = itemId,
        };
    }
}

ItemOverride ItemOverride_LookupByKey(ItemOverride_Key key) {
    s32 start = 0;
    s32 end = rItemOverrides_Count - 1;
    while (start <= end) {
        s32 midIdx = (start + end) / 2;
        ItemOverride midOvr = rItemOverrides[midIdx];
        if (key.all < midOvr.key.all) {
            end = midIdx - 1;
        } else if (key.all > midOvr.key.all) {
            start = midIdx + 1;
        } else {
            return midOvr;
        }
    }
    return (ItemOverride){ 0 };
}

ItemOverride ItemOverride_Lookup(Actor* actor, u8 scene, u8 itemId) {
    ItemOverride_Key key = ItemOverride_GetSearchKey(actor, scene, itemId);
    if (key.all == 0) {
        return (ItemOverride){ 0 };
    }

    return ItemOverride_LookupByKey(key);
}

static void ItemOverride_Activate(ItemOverride override) {
    u16 resolvedItemId = ItemTable_ResolveUpgrades(override.value.itemId);
    ItemRow* itemRow = ItemTable_GetItemRow(resolvedItemId);

    rActiveItemOverride = override;
    rActiveItemRow = itemRow;
    rActiveItemActionId = itemRow->actionId;
    rActiveItemTextId = itemRow->textId;
    rActiveItemObjectId = itemRow->objectId;
    rActiveItemGraphicId = itemRow->graphicId;
    rActiveItemFastChest = itemRow->chestType & 0x01;
}

static void ItemOverride_Clear(void) {
    rActiveItemOverride = (ItemOverride){ 0 };
    rActiveItemRow = NULL;
    rActiveItemActionId = 0;
    rActiveItemTextId = 0;
    rActiveItemObjectId = 0;
    rActiveItemGraphicId = 0;
    rActiveItemFastChest = 0;
}

static void ItemOverride_PushPendingOverride(ItemOverride override) {
    for (u32 i = 0; i < ARR_SIZE(rPendingOverrideQueue); ++i) {
        if (rPendingOverrideQueue[i].key.all == 0) {
            rPendingOverrideQueue[i] = override;
            break;
        }
        if (rPendingOverrideQueue[i].key.all == override.key.all) {
            // Prevent duplicate entries
            break;
        }
    }
}

void ItemOverride_PushDelayedOverride(u8 flag) {
    ItemOverride_Key key = { .all = 0 };
    key.scene = 0xFF;
    key.type = OVR_DELAYED;
    key.flag = flag;
    ItemOverride override = ItemOverride_LookupByKey(key);
    if (override.key.all != 0) {
        ItemOverride_PushPendingOverride(override);
    }
}

static void ItemOverride_PopPendingOverride(void) {
    rPendingOverrideQueue[0] = rPendingOverrideQueue[1];
    rPendingOverrideQueue[1] = rPendingOverrideQueue[2];
    rPendingOverrideQueue[2].key.all = 0;
    rPendingOverrideQueue[2].value.all = 0;
}

static void ItemOverride_AfterKeyReceived(ItemOverride_Key key) {
    ItemOverride_Key fireArrowKey = {
        .scene = 0x57, // Lake Hylia
        .type = OVR_BASE_ITEM,
        .flag = 0x58, // Fire arrows item ID
    };
    if (key.all == fireArrowKey.all) {
        gGlobalContext->actorCtx.flags.chest |= 0x1;
    }
}

static void ItemOverride_PopIceTrap(void) {
    ItemOverride_Key key = rPendingOverrideQueue[0].key;
    ItemOverride_Value value = rPendingOverrideQueue[0].value;
    if (value.itemId == 0x7C) {
        IceTrap_Push();
        ItemOverride_PopPendingOverride();
        ItemOverride_AfterKeyReceived(key);
    }
}

void ItemOverride_AfterItemReceived(void) {
    ItemOverride_Key key = rActiveItemOverride.key;
    if (key.all == 0) {
        return;
    }
    ItemOverride_AfterKeyReceived(key);
    ItemOverride_Clear();
}

static u32 ItemOverride_PlayerIsReady(void) {
    if ((PLAYER->stateFlags1 & 0xFCAC2485) == 0 &&
        (PLAYER->actor.bgCheckFlags & 0x0001) &&
        (PLAYER->stateFlags2 & 0x000C0000) == 0 &&
        PLAYER->actor.draw != NULL &&
        gGlobalContext->actorCtx.titleCtx.delayB == 0 &&
        gGlobalContext->actorCtx.titleCtx.delayA == 0 &&
        gGlobalContext->actorCtx.titleCtx.unk_12 == 0
        // && (z64_event_state_1 & 0x20) == 0 //TODO
        // && (z64_game.camera_2 == 0) //TODO
        ) {
        rSatisfiedPendingFrames++;
    }
    else {
        rSatisfiedPendingFrames = 0;
    }
    if (rSatisfiedPendingFrames >= 2) {
        rSatisfiedPendingFrames = 0;
        return 1;
    }
    return 0;
}

static void ItemOverride_TryPendingItem(void) {
    ItemOverride override = rPendingOverrideQueue[0];

    if (override.key.all == 0) {
        return;
    }

    if (rDummyActor->parent == NULL) {
        ItemOverride_Activate(override);
        PLAYER->interactRangeActor = rDummyActor;
        PLAYER->getItemId = rActiveItemRow->baseItemId;
    } else {
        rDummyActor->parent = NULL;
        ItemOverride_PopPendingOverride();
    }
}

void ItemOverride_Update(void) {
    ItemOverride_CheckStartingItem();
    ItemOverride_CheckZeldasLetter();
    IceTrap_Update();
    CustomModel_Update();
    if (ItemOverride_PlayerIsReady()) {
        ItemOverride_PopIceTrap();
        if (IceTrap_IsPending()) {
            IceTrap_Give();
        } else {
            ItemOverride_TryPendingItem();
        }
    }
}

void ItemOverride_GetItem(Actor* fromActor, Player* player, s8 incomingItemId) {
    ItemOverride override = { 0 };
    s32 incomingNegative = incomingItemId < 0;

    if (fromActor != NULL && incomingItemId != 0) {
        s8 itemId = incomingNegative ? -incomingItemId : incomingItemId;
        override = ItemOverride_Lookup(fromActor, gGlobalContext->sceneNum, itemId);
    }

    if (override.key.all == 0) {
        // No override, use base game's item code
        ItemOverride_Clear();
        player->getItemId = incomingItemId;
        return;
    }

    // Hack for scrubsanity off
    if ((gSettingsContext.scrubsanity == SCRUBSANITY_OFF) && (override.key.type == OVR_GROTTO_SCRUB)) {
        if (override.value.itemId == GI_ARROWS_LARGE) {
            override.value.itemId = GI_SEEDS_30;
        }
    }

    ItemOverride_Activate(override);
    s8 baseItemId = rActiveItemRow->baseItemId;

    if (fromActor->id == 0x0A) {
        // Update chest contents
        if (override.value.itemId == 0x7C) {
            // Use ice trap base item ID
            baseItemId = 0x7C;
        }
        fromActor->params = (fromActor->params & 0xF01F) | (baseItemId << 5);
    }

    player->getItemId = incomingNegative ? -baseItemId : baseItemId;
}

void ItemOverride_GetItemTextAndItemID(Actor* actor) {
    if (rActiveItemRow != NULL) {
        u16 textId = rActiveItemRow->textId;
        u8 actionId = rActiveItemRow->actionId;

        ItemTable_CallEffect(rActiveItemRow);
        if (actionId == ITEM_SKULL_TOKEN) {
            Item_Give(gGlobalContext, actionId);
            DisplayTextbox(gGlobalContext, textId, actor);
        } else {
            DisplayTextbox(gGlobalContext, textId, actor);
            Item_Give(gGlobalContext, actionId);
        }
        ItemOverride_AfterItemReceived();
    }
}

void ItemOverride_GetSkulltulaToken(Actor* tokenActor) {
    ItemOverride override = ItemOverride_Lookup(tokenActor, 0, 0);
    u16 itemId;
    if (override.key.all == 0) {
        // Give a skulltula token if there is no override
        itemId = 0x5B;
    } else {
        itemId = override.value.itemId;
    }

    u16 resolvedItemId = ItemTable_ResolveUpgrades(itemId);
    ItemRow* itemRow = ItemTable_GetItemRow(resolvedItemId);

    ItemTable_CallEffect(itemRow);

    tokenActor->draw = NULL;
    if (resolvedItemId == GI_SKULL_TOKEN) {
        Item_Give(gGlobalContext, itemRow->actionId);
        DisplayTextbox(gGlobalContext, itemRow->textId, 0);
    } else {
        DisplayTextbox(gGlobalContext, itemRow->textId, 0);
        Item_Give(gGlobalContext, itemRow->actionId);
    }
}

void ItemOverride_EditDrawGetItemBeforeModelSpawn(void) {
    void* cmb;

    switch (rActiveItemGraphicId) {
        case GID_CUSTOM_DOUBLE_DEFENSE:
            cmb = (void*)(((char*)PLAYER->giDrawSpace) + 0xA4);
            CustomModel_EditHeartContainerToDoubleDefense(cmb);
            break;
        case GID_CUSTOM_CHILD_SONGS:
            cmb = (void*)(((char*)PLAYER->giDrawSpace) + 0x2E60);
            CustomModel_SetOcarinaToRGBA565(cmb);
            break;
        case GID_CUSTOM_ADULT_SONGS:
            cmb = (void*)(((char*)PLAYER->giDrawSpace) + 0xE8);
            CustomModel_SetOcarinaToRGBA565(cmb);
            break;
    }
}

void ItemOverride_EditDrawGetItemAfterModelSpawn(SkeletonAnimationModel* model) {
    void* cmabMan;

    switch (rActiveItemGraphicId) {
        case GID_CUSTOM_CHILD_SONGS:
            cmabMan = ExtendedObject_GetCMABByIndex(OBJECT_CUSTOM_GENERAL_ASSETS, TEXANIM_CHILD_SONG);
            TexAnim_Spawn(model->unk_0C, cmabMan);
            model->unk_0C->animSpeed = 0.0f;
            model->unk_0C->animMode = 0;
            model->unk_0C->curFrame = rActiveItemRow->objectMeshId;
            break;
        case GID_CUSTOM_ADULT_SONGS:
            cmabMan = ExtendedObject_GetCMABByIndex(OBJECT_CUSTOM_GENERAL_ASSETS, TEXANIM_ADULT_SONG);
            TexAnim_Spawn(model->unk_0C, cmabMan);
            model->unk_0C->animSpeed = 0.0f;
            model->unk_0C->animMode = 0;
            model->unk_0C->curFrame = rActiveItemRow->objectMeshId;
            break;
    }
}

s32 ItemOverride_GiveSariasGift(void) {
    u32 receivedGift = EventCheck(0xC1);
    if (receivedGift == 0) {
        ItemOverride_PushDelayedOverride(0x02);
        EventSet(0xC1);
    }

    // return 1 to skip the cutscene
    return 1;
}

//If we haven't obtained Zelda's Letter and are in the castle courtyard, push it
void ItemOverride_CheckZeldasLetter() {
  if (EventCheck(0x40) == 0 && gGlobalContext->sceneNum == 0x4A) {
      ItemOverride_Key key = { .all = 0 };
      key.scene = 0x4A;
      key.type = OVR_BASE_ITEM;
      key.flag = 0x0B;
      ItemOverride override = ItemOverride_LookupByKey(key);
      ItemOverride_PushPendingOverride(override);
      EventSet(0x40);
  }
}

void ItemOverride_PushDungeonReward(u8 dungeon) {
    ItemOverride_Key key = { .all = 0 };
    key.scene = 0xFF;
    key.type = OVR_TEMPLE;
    key.flag = dungeon;
    ItemOverride override = ItemOverride_LookupByKey(key);
    ItemOverride_PushPendingOverride(override);
}

void ItemOverride_CheckStartingItem() {
    //use eventChkInf[0] |= 0x0001 as the check for this
    if (EventCheck(0x00) == 0) {
        if (gSettingsContext.linksPocketItem != LINKSPOCKETITEM_DUNGEON_REWARD) {
            ItemOverride_PushDungeonReward(0xFF); //Push Link's Pocket Reward
        }
        EventSet(0x00);
    }
}
