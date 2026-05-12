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
    DLYOVR_MASTER_SWORD,
    DLYOVR_LACS,
    DLYOVR_SARIA_GIFT,
    DLYOVR_ZELDA_LETTER,
    DLYOVR_FAIRY_ZF,
    DLYOVR_FAIRY_HC,
    DLYOVR_FAIRY_DC,
    DLYOVR_FAIRY_DMT,
    DLYOVR_FAIRY_DMC,
    DLYOVR_FAIRY_OGC,
    DLYOVR_SONG_MINUET,
    DLYOVR_SONG_BOLERO,
    DLYOVR_SONG_SERENADE,
    DLYOVR_SONG_REQUIEM,
    DLYOVR_SONG_NOCTURNE,
    DLYOVR_SONG_PRELUDE,
    DLYOVR_SONG_LULLABY,
    DLYOVR_SONG_EPONA,
    DLYOVR_SONG_SARIA,
    DLYOVR_SONG_SUN,
    DLYOVR_SONG_TIME,
    DLYOVR_SONG_STORMS,
} DelayedOverride;
