#ifndef _ITEM_OVERRIDES_H_
#define _ITEM_OVERRIDES_H_

#include "s_item_override.h"

#include "z3D/z3D.h"

enum ItemOverride_Type {
    OVR_BASE_ITEM    = 0,
    OVR_CHEST        = 1,
    OVR_COLLECTABLE  = 2,
    OVR_SKULL        = 3,
    OVR_GROTTO_SCRUB = 4,
    OVR_DELAYED      = 5,
    OVR_TEMPLE       = 6,
};

extern u8 isItemOverrideActive;
extern u8 rActiveItemChestType;

void ItemOverride_Init(void);
void ItemOverride_Update(void);
ItemOverride ItemOverride_LookupByKey(ItemOverride_Key key);
ItemOverride ItemOverride_Lookup(Actor* actor, u8 scene, u8 item_id);
s32 ItemOverride_IsAPendingOverride(void);
void ItemOverride_PushDelayedOverride(u8 flag);
void ItemOverride_CheckZeldasLetter();
void ItemOverride_PushDungeonReward(u8 dungeon);
void ItemOverride_CheckStartingItem();
void ItemOverride_PushHardcodedItem(s16 getItemId);

#endif //_ITEM_OVERRIDES_H_
