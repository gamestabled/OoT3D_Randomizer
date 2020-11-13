#ifndef _ITEM_OVERRIDES_H_
#define _ITEM_OVERRIDES_H_

#include "../include/z3D/z3D.h"

void ItemOverride_Init(void);
void ItemOverride_Update(void);

enum ItemOverride_Type {
    OVR_BASE_ITEM = 0,
    OVR_CHEST = 1,
    OVR_COLLECTABLE = 2,
    OVR_SKULL = 3,
    OVR_GROTTO_SCRUB = 4,
    OVR_DELAYED = 5,
};

typedef union {
    u32 all;
    struct {
        char    pad_;
        u8 scene;
        u8 type;
        u8 flag;
    };
} ItemOverride_Key;

typedef union {
    u32 all;
    struct {
        u16 itemId;
        u8  player;
        u8  looksLikeItemId;
    };
} ItemOverride_Value;

typedef struct {
    ItemOverride_Key   key;
    ItemOverride_Value value;
} ItemOverride;

ItemOverride ItemOverride_LookupByKey(ItemOverride_Key key);
ItemOverride ItemOverride_Lookup(Actor* actor, u8 scene, u8 item_id);
void ItemOverride_PushDelayedOverride(u8 flag);

#endif
