#pragma once
#include "s_types.h"

typedef union ItemOverride_Key {
    u32 all;
    struct {
        char pad_;
        u8 scene;
        u8 type;
        u8 flag;
    };
} ItemOverride_Key;

typedef union ItemOverride_Value {
    u32 all;
    struct {
        u16 itemId;
        u8 player;
        u8 looksLikeItemId;
    };
} ItemOverride_Value;

typedef struct ItemOverride {
    ItemOverride_Key key;
    ItemOverride_Value value;
} ItemOverride;
