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

typedef enum DelayedOverride {
    DELOVR_MASTER_SWORD,
    DELOVR_LACS,
    DELOVR_SARIA_GIFT,
    DELOVR_ZELDA_LETTER,
    DELOVR_FAIRY_ZF,
    DELOVR_FAIRY_HC,
    DELOVR_FAIRY_DC,
    DELOVR_FAIRY_DMT,
    DELOVR_FAIRY_DMC,
    DELOVR_FAIRY_OGC,
    DELOVR_SONG_MINUET,
    DELOVR_SONG_BOLERO,
    DELOVR_SONG_SERENADE,
    DELOVR_SONG_REQUIEM,
    DELOVR_SONG_NOCTURNE,
    DELOVR_SONG_PRELUDE,
    DELOVR_SONG_LULLABY,
    DELOVR_SONG_EPONA,
    DELOVR_SONG_SARIA,
    DELOVR_SONG_SUN,
    DELOVR_SONG_TIME,
    DELOVR_SONG_STORMS,
} DelayedOverride;
