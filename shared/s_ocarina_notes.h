#pragma once
#include "s_types.h"

typedef enum OcarinaNoteButton {
    OCARINA_BUTTON_L,
    OCARINA_BUTTON_R,
    OCARINA_BUTTON_Y,
    OCARINA_BUTTON_X,
    OCARINA_BUTTON_A,
    OCARINA_BUTTON_MAX,
} OcarinaNoteButton;

typedef enum OcarinaSongId {
    OCARINA_SONG_MINUET,
    OCARINA_SONG_BOLERO,
    OCARINA_SONG_SERENADE,
    OCARINA_SONG_REQUIEM,
    OCARINA_SONG_NOCTURNE,
    OCARINA_SONG_PRELUDE,
    OCARINA_SONG_SARIAS,
    OCARINA_SONG_EPONAS,
    OCARINA_SONG_LULLABY,
    OCARINA_SONG_SUNS,
    OCARINA_SONG_TIME,
    OCARINA_SONG_STORMS,
    OCARINA_SONG_MAX,
} OcarinaSongId;

typedef struct OcarinaSongButtonSequence {
    /* 0x0 */ u8 length;
    /* 0x1 */ u8 buttons[8];
} OcarinaSongButtonSequence;
