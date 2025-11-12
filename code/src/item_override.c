#include "item_override.h"
#include "rHeap.h"
#include "item_table.h"
#include "icetrap.h"
#include "settings.h"
#include "custom_models.h"
#include "objects.h"
#include "entrance.h"
#include "savefile.h"
#include "common.h"
#include "actors/obj_mure3.h"

#include <stddef.h>
#include "chest.h"

#include "z3D/z3D.h"
#include "z3D/actors/z_en_box.h"
#include "z3D/actors/z_en_item00.h"
#include "z3D/actors/z_obj_mure3.h"

#define READY_ON_LAND 1
#define READY_IN_WATER 2

static ItemOverride rItemOverrides[640] = { 0 };
static s32 rItemOverrides_Count         = 0;

static ItemOverride rPendingOverrideQueue[3] = { 0 };
static Actor* rDummyActor                    = NULL;

static ItemOverride rActiveItemOverride = { 0 };
DrawItemTableEntry rActiveDrawItem      = { 0 };
ItemRow* rActiveItemRow                 = NULL;
u32 isItemOverrideActive                = FALSE;
// Split active_item_row into variables for convenience in ASM
u32 rActiveItemActionId  = 0;
u32 rActiveItemTextId    = 0;
u32 rActiveItemObjectId  = 0;
u32 rActiveItemChestType = 0;

static u8 rSatisfiedPendingFrames      = 0;
static u8 rSatisfiedPendingFramesWater = 0;

void ItemOverride_Init(void) {
    while (rItemOverrides[rItemOverrides_Count].key.all != 0) {
        rItemOverrides_Count++;
    }

    // Create an actor satisfying the minimum requirements to give the player an item
    rDummyActor         = rHeap_Alloc(sizeof(Actor));
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
    if (gSettingsContext.slingshotAsAdult) {
        gItemUsabilityTable[ITEM_SLINGSHOT] = 0x09;
    }
    if (gSettingsContext.bowAsChild) {
        gItemUsabilityTable[ITEM_BOW]             = 0x09;
        gItemUsabilityTable[ITEM_ARROW_FIRE]      = 0x09;
        gItemUsabilityTable[ITEM_ARROW_ICE]       = 0x09;
        gItemUsabilityTable[ITEM_ARROW_LIGHT]     = 0x09;
        gItemUsabilityTable[ITEM_BOW_ARROW_FIRE]  = 0x09;
        gItemUsabilityTable[ITEM_BOW_ARROW_ICE]   = 0x09;
        gItemUsabilityTable[ITEM_BOW_ARROW_LIGHT] = 0x09;
    }
    if (gSettingsContext.ironbootsAsChild) {
        gItemUsabilityTable[ITEM_BOOTS_IRON] = 0x09;
    }
    if (gSettingsContext.hoverbootsAsChild) {
        gItemUsabilityTable[ITEM_BOOTS_HOVER] = 0x09;
    }
    if (gSettingsContext.masksAsAdult) {
        gItemUsabilityTable[ITEM_MASK_KEATON] = 0x09;
        gItemUsabilityTable[ITEM_MASK_SKULL]  = 0x09;
        gItemUsabilityTable[ITEM_MASK_SPOOKY] = 0x09;
        gItemUsabilityTable[ITEM_MASK_BUNNY]  = 0x09;
        gItemUsabilityTable[ITEM_MASK_GORON]  = 0x09;
        gItemUsabilityTable[ITEM_MASK_ZORA]   = 0x09;
        gItemUsabilityTable[ITEM_MASK_GERUDO] = 0x09;
        gItemUsabilityTable[ITEM_MASK_TRUTH]  = 0x09;
    }
    if (gSettingsContext.hookshotAsChild) {
        gItemUsabilityTable[ITEM_HOOKSHOT] = 0x09;
        gItemUsabilityTable[ITEM_LONGSHOT] = 0x09;
    }
    if (gSettingsContext.kokiriSwordAsAdult) {
        gGearUsabilityTable[GearSlot(ITEM_SWORD_KOKIRI)] = 0x09;
    }
    if (gSettingsContext.masterSwordAsChild) {
        gGearUsabilityTable[GearSlot(ITEM_SWORD_MASTER)] = 0x09;
    }
    if (gSettingsContext.biggoronSwordAsChild) {
        gGearUsabilityTable[GearSlot(ITEM_SWORD_BGS)] = 0x09;
    }
    if (gSettingsContext.dekuShieldAsAdult) {
        gGearUsabilityTable[GearSlot(ITEM_SHIELD_DEKU)] = 0x09;
    }
    if (gSettingsContext.mirrorShieldAsChild) {
        gGearUsabilityTable[GearSlot(ITEM_SHIELD_MIRROR)] = 0x09;
    }
    if (gSettingsContext.goronTunicAsChild) {
        gGearUsabilityTable[GearSlot(ITEM_TUNIC_GORON)] = 0x09;
    }
    if (gSettingsContext.zoraTunicAsChild) {
        gGearUsabilityTable[GearSlot(ITEM_TUNIC_ZORA)] = 0x09;
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
            .type  = OVR_CHEST,
            .flag  = actor->params & 0x1F,
        };
    } else if (actor->id == 0x15) { // Collectible
        // Only override heart pieces and keys blue rupees
        EnItem00* currentItem = ((EnItem00*)actor);
        u32 collectibleType   = actor->params & 0xFF;
        u16 collectibleFlag   = ((EnItem00*)actor)->collectibleFlag;
        if (collectibleFlag == 0x00 && currentItem->actor.home.rot.z >= 0x40) {
            // For rupees spawned by Rupee Circles (ObjMure3) We store the "collectibleFlag" in actor.home.rot.z since
            // that is not really used for them. Since collectibleFlag normally gets truncated to 0x3F we can use any
            // value at or above 0x40. We've reserved 0x40-0x46 for Rupee circle rupees.
            collectibleFlag = currentItem->actor.home.rot.z;
        }
        s32 respawningCollected = collectibleFlag >= 0x20 && SaveFile_GetCollectedRandomizedRespawningCollectibleFlag(
                                                                 gGlobalContext->sceneNum, collectibleFlag);

        if ((collectibleType > 0x02 && collectibleType != 0x06 && collectibleType != 0x11) || respawningCollected) {
            return (ItemOverride_Key){ .all = 0 };
        }

        return (ItemOverride_Key){
            .scene = scene,
            .type  = OVR_COLLECTABLE,
            .flag  = collectibleFlag,
        };
    } else if (actor->id == 0x19C) { // Gold Skulltula Token
        return (ItemOverride_Key){
            .scene = (actor->params >> 8) & 0x1F,
            .type  = OVR_SKULL,
            .flag  = actor->params & 0xFF,
        };
    } else if (scene == 0x3E && actor->id == 0x11A) { // Grotto Salesman
        return (ItemOverride_Key){
            .scene = gSaveContext.respawn[RESPAWN_MODE_RETURN].data,
            .type  = OVR_GROTTO_SCRUB,
            .flag  = itemId,
        };
    } else {
        return (ItemOverride_Key){
            .scene = scene,
            .type  = OVR_BASE_ITEM,
            .flag  = itemId,
        };
    }
}

ItemOverride ItemOverride_LookupByKey(ItemOverride_Key key) {
    s32 start = 0;
    s32 end   = rItemOverrides_Count - 1;
    while (start <= end) {
        s32 midIdx          = (start + end) / 2;
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
    ItemRow* itemRow   = ItemTable_GetItemRow(resolvedItemId);
    u8 looksLikeItemId = override.value.looksLikeItemId;

    if (override.value.itemId == GI_ICE_TRAP) {
        looksLikeItemId = 0;
    }

    isItemOverrideActive = TRUE;
    rActiveItemOverride  = override;
    rActiveItemRow       = itemRow;
    rActiveItemActionId  = itemRow->actionId;
    rActiveItemTextId    = itemRow->textId;
    rActiveItemChestType = itemRow->chestType;

    ItemRow* drawItemRow = looksLikeItemId ? ItemTable_GetItemRow(looksLikeItemId) : itemRow;
    rActiveDrawItem      = (DrawItemTableEntry){
             .objectId        = drawItemRow->objectId,
             .objectModelIdx  = drawItemRow->objectModelIdx,
             .cmabIndex       = drawItemRow->cmabIndex,
             .objectModelIdx2 = drawItemRow->objectModelIdx2,
             .cmabIndex2      = drawItemRow->cmabIndex2,
    };
    rActiveItemObjectId = rActiveDrawItem.objectId;
}

static void ItemOverride_Clear(void) {
    isItemOverrideActive = FALSE;
    rActiveItemOverride  = (ItemOverride){ 0 };
    rActiveDrawItem      = (DrawItemTableEntry){ 0 };
    rActiveItemRow       = NULL;
    rActiveItemActionId  = 0;
    rActiveItemTextId    = 0;
    rActiveItemObjectId  = 0;
    rActiveItemChestType = 0;
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

s32 ItemOverride_IsAPendingOverride(void) {
    return (rPendingOverrideQueue[0].key.all != 0);
}

void ItemOverride_PushDelayedOverride(u8 flag) {
    ItemOverride_Key key  = { .all = 0 };
    key.scene             = 0xFF;
    key.type              = OVR_DELAYED;
    key.flag              = flag;
    ItemOverride override = ItemOverride_LookupByKey(key);
    if (override.key.all != 0) {
        ItemOverride_PushPendingOverride(override);
    }
}

static void ItemOverride_PopPendingOverride(void) {
    rPendingOverrideQueue[0]           = rPendingOverrideQueue[1];
    rPendingOverrideQueue[1]           = rPendingOverrideQueue[2];
    rPendingOverrideQueue[2].key.all   = 0;
    rPendingOverrideQueue[2].value.all = 0;
}

static void ItemOverride_AfterKeyReceived(ItemOverride_Key key) {
    ItemOverride_Key fireArrowKey = {
        .scene = 0x57, // Lake Hylia
        .type  = OVR_BASE_ITEM,
        .flag  = 0x58, // Fire arrows item ID
    };
    if (key.all == fireArrowKey.all) {
        gGlobalContext->actorCtx.flags.chest |= 0x1;
    }

    // If we override an adult trade item, we should remove the previous item from being owned
    if ((key.type == OVR_BASE_ITEM) &&
        ((key.flag == GI_COJIRO) || ((key.flag > GI_POCKET_EGG) && (key.flag <= GI_CLAIM_CHECK)))) {
        u8 itemId;
        switch (key.flag) {
            case GI_COJIRO:
                itemId = 46;
                break;
            case GI_POCKET_CUCCO:
                itemId = 45;
                break;
            case GI_ODD_MUSHROOM:
                itemId = 47;
                break;
            case GI_ODD_POTION:
                itemId = 48;
                break;
            case GI_SAW:
                itemId = 49;
                break;
            case GI_SWORD_BROKEN:
                itemId = 50;
                break;
            case GI_PERSCRIPTION:
                itemId = 51;
                break;
            case GI_FROG:
                itemId = 52;
                break;
            case GI_EYEDROPS:
                itemId = 53;
                break;
            case GI_CLAIM_CHECK:
                itemId = 54;
                break;
        }
        SaveFile_UnsetTradeItemAsOwned(itemId);
        SaveFile_SetOwnedTradeItemEquipped();
    }
}

static void ItemOverride_PopIceTrap(void) {
    ItemOverride_Key key     = rPendingOverrideQueue[0].key;
    ItemOverride_Value value = rPendingOverrideQueue[0].value;
    if (value.itemId == 0x7C) {
        IceTrap_Push(key.all);
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
}

static u32 ItemOverride_PlayerIsReadyOnLand(void) {
    if ((PLAYER->stateFlags1 & 0xFCAC2485) == 0 && (PLAYER->actor.bgCheckFlags & 0x0001) &&
        (PLAYER->stateFlags2 & 0x000C0000) == 0 && PLAYER->actor.draw != NULL &&
        gGlobalContext->actorCtx.titleCtx.delayTimer == 0 && gGlobalContext->actorCtx.titleCtx.durationTimer == 0 &&
        gGlobalContext->actorCtx.titleCtx.alpha == 0
        // && (z64_event_state_1 & 0x20) == 0 //TODO
        // && (z64_game.camera_2 == 0) //TODO
    ) {
        rSatisfiedPendingFrames++;
    } else {
        rSatisfiedPendingFrames = 0;
    }
    if (rSatisfiedPendingFrames >= 2) {
        rSatisfiedPendingFrames = 0;
        return 1;
    }
    return 0;
}

static u32 ItemOverride_PlayerIsReadyInWater(void) {
    if ((PLAYER->stateFlags1 & 0xF4AC2085) == 0 /*&& (PLAYER->actor.bgCheckFlags & 0x0001)*/ &&
        (PLAYER->stateFlags2 & 0x000C0000) == 0 && PLAYER->actor.draw != NULL &&
        gGlobalContext->actorCtx.titleCtx.delayTimer == 0 && gGlobalContext->actorCtx.titleCtx.durationTimer == 0 &&
        gGlobalContext->actorCtx.titleCtx.alpha == 0 && (PLAYER->stateFlags1 & 0x08000000) != 0 && // Player is Swimming
        (PLAYER->stateFlags1 & 0x400) == 0 && // Player is not already receiving an item when surfacing
        gGlobalContext->sceneLoadFlag == 0 && // Another scene isn't about to be loaded
        ItemOverride_IsAPendingOverride()
        // && Multiworld is off
        // && (z64_event_state_1 & 0x20) == 0 //TODO
        // && (z64_game.camera_2 == 0) //TODO
    ) {
        rSatisfiedPendingFramesWater++;
    } else {
        rSatisfiedPendingFramesWater = 0;
    }
    if (rSatisfiedPendingFramesWater >= 2) {
        rSatisfiedPendingFramesWater = 0;
        return 1;
    }
    return 0;
}

static u32 ItemOverride_PlayerIsReady(void) {
    if (ItemOverride_PlayerIsReadyOnLand()) {
        return READY_ON_LAND;
    }
    if (ItemOverride_PlayerIsReadyInWater()) {
        return READY_IN_WATER;
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
        PLAYER->getItemId          = rActiveItemRow->baseItemId;
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
    u8 readyStatus = ItemOverride_PlayerIsReady();
    if (readyStatus) {
        if (readyStatus == READY_ON_LAND) { // Ice traps effects only work on land
            ItemOverride_PopIceTrap();
        }

        if (IceTrap_IsPending()) {
            IceTrap_Give();
        } else {
            ItemOverride_TryPendingItem();
            if (readyStatus == READY_IN_WATER) {
                // Force underwater player flag in order to play the correct get-item
                // animation even if Link is at the water's surface.
                PLAYER->stateFlags2 |= 0x400;
                SetupItemInWater(PLAYER, gGlobalContext);
                rDummyActor->parent = NULL;
                ItemOverride_PopPendingOverride();
            }
        }
    }

    // Clear the active override once the GetItem process has finished,
    // or when walking away from a chest without opening it or a collectible without collecting it.
    // This will also keep the override if the player is doing a GIM-like glitch.
    if (rActiveItemRow != NULL &&
        (PLAYER->getItemId == 0 || (PLAYER->interactRangeActor == NULL && (PLAYER->stateFlags1 & 0x400) == 0))) {
        ItemOverride_Clear();
    }
}

void ItemOverride_GetItem(Actor* fromActor, Player* player, s8 incomingItemId) {
    ItemOverride override = { 0 };
    s32 incomingNegative  = incomingItemId < 0;

    if (fromActor != NULL && incomingItemId != 0) {
        s8 itemId = incomingNegative ? -incomingItemId : incomingItemId;
        override  = ItemOverride_Lookup(fromActor, gGlobalContext->sceneNum, itemId);
    }

    if (override.key.all == 0) {
        // Hack for Scrubsanity Off
        // The game will spawn different scrub actors in grottos depending on if
        // Link is child or adult (one for deku seeds and another for arrows
        // respectively). Since we only override the child deku scrubs when
        // scrubsanity is off, the adult ones will return the Gold Scale getItemID
        // and not find an override in the overrid table. This is where we fix that
        // so adult Link will receive arrows properly.
        if (incomingItemId == GI_SCALE_GOLD && gSettingsContext.scrubsanity == SCRUBSANITY_OFF) {
            override.value.itemId = GI_ARROWS_LARGE;
        } else {
            // No override, use base game's item code
            ItemOverride_Clear();
            player->getItemId = incomingItemId;
            return;
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
    } else if (override.value.itemId == 0x7C) {
        rActiveItemRow->effectArg1 = override.key.all >> 16;
        rActiveItemRow->effectArg2 = override.key.all & 0xFFFF;
    }

    player->getItemId = incomingNegative ? -baseItemId : baseItemId;
}

void ItemOverride_GetItemTextAndItemID(Actor* actor) {
    if (rActiveItemRow != NULL) {
        u16 textId  = rActiveItemRow->textId;
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
    ItemRow* itemRow   = ItemTable_GetItemRow(resolvedItemId);
    if (override.value.itemId == 0x7C) {
        itemRow->effectArg1 = override.key.all >> 16;
        itemRow->effectArg2 = override.key.all & 0xFFFF;
    }

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

u8 ItemOverride_GetItemDrop(EnItem00* this) {
    // Override items that always behave as drops and never trigger a Get Item event.
    switch (this->actor.params) {
        case ITEM00_RUPEE_GREEN:
        case ITEM00_RUPEE_BLUE:
        case ITEM00_RUPEE_RED:
        case ITEM00_RUPEE_PURPLE:
        case ITEM00_RUPEE_ORANGE:
        case ITEM00_RECOVERY_HEART:
        case ITEM00_FLEXIBLE:
        case ITEM00_BOMBS_A:
        case ITEM00_BOMBS_B:
        case ITEM00_ARROWS_SINGLE:
        case ITEM00_ARROWS_SMALL:
        case ITEM00_ARROWS_MEDIUM:
        case ITEM00_ARROWS_LARGE:
            break;
        default:
            return FALSE; // Proceed normally with the Get Item event.
    }

    ItemOverride override = ItemOverride_Lookup(&this->actor, gGlobalContext->sceneNum, GI_INVALID);
    if (override.key.all == 0) {
        return FALSE; // No override, proceed with Item_Give.
    }

    u16 resolvedItemId = ItemTable_ResolveUpgrades(override.value.itemId);
    ItemRow* itemRow   = ItemTable_GetItemRow(resolvedItemId);

    if ((itemRow->chestType != CHEST_JUNK && itemRow->chestType != CHEST_HEART) ||
        itemRow->baseItemId == GI_HEART_PIECE || itemRow->baseItemId == GI_HEART_CONTAINER) {
        ItemOverride_PushPendingOverride(override);
        Actor_Kill(&this->actor);
    } else {
        // Minor item, behave as item drop.
        this->actor.params = ITEM00_RECOVERY_HEART;
        ItemTable_CallEffect(itemRow);
        Item_Give(gGlobalContext, itemRow->actionId);
    }
    if (this->collectibleFlag == 0 && this->actor.home.rot.z >= 0x40 && this->actor.home.rot.z < 0x47) {
        SaveFile_SetCollectedRandomizedRespawningCollectibleFlag(gGlobalContext->sceneNum, this->actor.home.rot.z);
    } else if (this->collectibleFlag >= 0x20) {
        // collectibles with a collectibleFlag >= 0x20 respawn so we need to keep track of them in the gExtSaveData
        SaveFile_SetCollectedRandomizedRespawningCollectibleFlag(gGlobalContext->sceneNum, this->collectibleFlag);
    }

    return TRUE; // Item overridden, skip Item_Give.
}

static s32 ItemOverride_IsDrawItemVanilla(void) {
    return rActiveItemRow == NULL ||          // No item override
           PLAYER->itemActionParam >= 0x2B || // Using trade item
           PauseContext_GetState() != 0;      // On pause screen
}

void ItemOverride_EditDrawGetItemBeforeModelSpawn(void) {
    if (ItemOverride_IsDrawItemVanilla()) {
        return;
    }

    CustomModels_EditItemCMB(PLAYER->giDrawSpace, rActiveItemObjectId, rActiveItemRow->special);
}

void ItemOverride_EditDrawGetItemAfterModelSpawn(SkeletonAnimationModel* model) {
    if (ItemOverride_IsDrawItemVanilla()) {
        return;
    }

    CustomModels_ApplyItemCMAB(model, rActiveItemObjectId, rActiveItemRow->special);
}

// Called every frame while the GetItem is drawn
void ItemOverride_EditDrawGetItemAfterMatrixUpdate(SkeletonAnimationModel* model) {
    if (ItemOverride_IsDrawItemVanilla()) {
        return;
    }

    CustomModels_UpdateMatrix(&model->mtx, rActiveItemObjectId);
}

s32 ItemOverride_GiveSariasGift(void) {
    u32 receivedGift = EventCheck(0xC1);
    if (receivedGift == 0 &&
        Entrance_SceneAndSpawnAre(0x5B, 0x09)) { // Kokiri Forest -> LW Bridge, index 05E0 in the entrance table
        ItemOverride_PushDelayedOverride(0x02);
        EventSet(0xC1);
    }

    // return 1 to skip the cutscene
    return 1;
}

// If we haven't obtained Zelda's Letter and are in the castle courtyard, push it
void ItemOverride_CheckZeldasLetter() {
    if (EventCheck(0x40) == 0 && gGlobalContext->sceneNum == 0x4A) {
        ItemOverride_Key key  = { .all = 0 };
        key.scene             = 0x4A;
        key.type              = OVR_BASE_ITEM;
        key.flag              = 0x0B;
        ItemOverride override = ItemOverride_LookupByKey(key);
        ItemOverride_PushPendingOverride(override);
        EventSet(0x40);
    }
}

void ItemOverride_PushDungeonReward(u8 dungeon) {
    ItemOverride_Key key  = { .all = 0 };
    key.scene             = 0xFF;
    key.type              = OVR_TEMPLE;
    key.flag              = dungeon;
    ItemOverride override = ItemOverride_LookupByKey(key);
    ItemOverride_PushPendingOverride(override);
}

void ItemOverride_CheckStartingItem() {
    // use eventChkInf[0] |= 0x0001 as the check for this
    if (EventCheck(0x00) == 0) {
        if (gSettingsContext.linksPocketItem != LINKSPOCKETITEM_DUNGEON_REWARD) {
            ItemOverride_PushDungeonReward(0xFF); // Push Link's Pocket Reward
        }
        EventSet(0x00);
    }
}

DrawItemTableEntry* ItemOverride_GetDrawItem(DrawItemTableEntry* original) {
    if (ItemOverride_IsDrawItemVanilla()) {
        return original;
    }
    return &rActiveDrawItem;
}

// Overrides setting PLAYER->giDrawIdPlusOne, which is used to set the mesh for rupee models.
s16 ItemOverride_OverrideGiDrawIdPlusOne(s16 originalDrawItemID) {
    if (ItemOverride_IsDrawItemVanilla()) {
        return originalDrawItemID;
    }

    if (rActiveItemObjectId == 0x017F) { // Set the mesh for rupees
        return rActiveItemRow->special + 1;
    }

    return 1; // Default value that won't change the mesh.
}

void ItemOverride_PushHardcodedItem(s16 getItemId) {
    ItemOverride override = {
        .key =  {
            .type = OVR_DELAYED, // random value to have non-zero key
        },
        .value = {
            .itemId = getItemId,
            .player = 0xFF,
        }
    };
    ItemOverride_PushPendingOverride(override);
}
